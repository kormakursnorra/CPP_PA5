#include "maze.h"
#include <cassert>
#include <cstdlib>
#include <memory>
#include <random>

#include "renderer.h"

Maze::Maze(int rows, int cols, bool animate) 
    : rows(rows), cols(cols), animate(animate) {
    
    grid.reserve(rows * cols);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            grid.push_back(std::make_unique<Cell>(
                r, c, c + r * cols));
        }
    }
}

void Maze::wilson(Renderer* renderer) {
    // Dir offset: N, S, E, W
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    std::mt19937 rng{std::random_device{}()};

    // Pick a random cell
    int startR = rng() % rows;
    int startC = rng() % cols;
    grid[startC + (startR * cols)]->inMaze = true;

    // track total cells
    int cellsInMaze = 1;
    int totalCells = rows * cols;
    
    // Direction each cell was exited during the current walk
    // -1 means not part of current walk
    std::vector<int> direction(rows * cols, -1);

    while (cellsInMaze < totalCells) {
        // Pick random cell not in maze
        int r, c;
        do {
            r = rng() % rows;
            c = rng() % cols;
        } while (grid.at(c + (r * cols))->inMaze);

        int walkStartR = r;
        int walkStartC = c;

        std::fill(direction.begin(), direction.end(), -1);

        while(!grid.at(c + (r * cols))->inMaze) {
            int dir;
            int nr;
            int nc;
            do {
                dir = rng() % 4;
                nr = r + dr[dir];
                nc = c + dc[dir];
            } while (nr < 0 || nr >= rows || nc < 0 || nc >= cols);

            direction.at(c + (r * cols)) = dir;
            r = nr;
            c = nc;
        }

        r = walkStartR;
        c = walkStartC;
        while (!grid.at(c + (r * cols))->inMaze) {
            int dir = direction.at(c + (r * cols));
            removeWall(r, c, dir);
            if (animate) {
                clear();
                renderer->drawMaze(*this);
                refresh();
                napms(15);
            }
            grid.at(c + (r * cols))->inMaze = true;
            cellsInMaze++;

            direction.at(c + (r * cols)) = -1;

            r = r + dr[dir];
            c = c + dc[dir];
        }

    }

    exitRow = rows - 1;
    exitCol = cols - 1;
    findEscapePath(*grid[0], *grid[exitCol + (exitRow * cols)]);
}

void Maze::removeWall(int r, int c, int dir) {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    int nr = r + dr[dir];
    int nc = c + dc[dir];

    if (dir == 0) {
        grid.at(c + (r * cols))->north = false;
        grid.at(nc + (nr * cols))->south = false;
    } 
    if (dir == 1) {
        grid.at(c + (r * cols))->south = false; 
        grid.at(nc + (nr * cols))->north = false;
    }
    if (dir == 2) {
        grid.at(c + (r * cols))->east = false;
        grid.at(nc + (nr * cols))->west = false;
    }
    if (dir == 3) {
        grid.at(c + (r * cols))->west = false;
        grid.at(nc + (nr * cols))->east = false;
    }
}

void Maze::findEscapePath(const Cell& startCell, const Cell& exitCell) {
    std::queue<std::reference_wrapper<const Cell>> queue;             
    std::vector<int> parent(rows * cols, -1);
    std::vector<bool> visited(rows * cols, false);
    
    parent[startCell.getCellPos()]  = startCell.getCellPos();
    visited[startCell.getCellPos()] = true;
    queue.push(startCell);

    while (!queue.empty()) {
        const Cell& currCell = queue.front();
        queue.pop();
        
        if (currCell.getCellPos() == exitCell.getCellPos()) break;
       
        for (int i = 0; i < 4; ++i) {
            if (currCell.north && i == 0) continue;
            if (currCell.south && i == 1) continue;
            if (currCell.east  && i == 2) continue;                
            if (currCell.west  && i == 3) continue;
            
            int nextRow = currCell.getCellRow() + directions[i][0];
            int nextCol = currCell.getCellCol() + directions[i][1];
            
            if (0 <= nextRow && nextRow < rows && 0 <= nextCol && nextCol < cols) {
                int nextPos = nextCol + (nextRow * cols);
                if (!visited[nextPos]) {
                    visited[nextPos] = true;
                    parent[nextPos] = currCell.getCellPos();
                    queue.push(*grid.at(nextPos));
                }
            }
        }
    }

    int pos = exitCell.getCellPos();
    while (pos != startCell.getCellPos()) {
        if (parent[pos] == -1) {
            escapePath.clear();
            return;
        }
        escapePath.push_back(*grid.at(pos));
        pos = parent[pos];
    }
    escapePath.push_back(startCell);
    std::reverse(escapePath.begin(), escapePath.end());
}