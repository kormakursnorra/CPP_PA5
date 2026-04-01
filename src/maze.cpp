#include "maze.h"
#include <memory>
#include <random>

#include "renderer_k.h"

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
    grid[startR + (startC * cols)]->inMaze = true;

    // track total cells
    int cellsInMaze = 1;
    int totalCells = rows * cols;
    
    // Direction each cell was exited during the current walk
    // -1 means not part of current walk
    std::vector<std::vector<int>> direction(rows, std::vector<int>(cols, -1));

    while (cellsInMaze < totalCells) {
        // Pick random cell not in maze
        int r, c;
        do {
            r = rng() % rows;
            c = rng() % cols;
        } while (grid[c + (r * cols)]->inMaze);

        int walkStartR = r;
        int walkStartC = c;

        while(!grid[c + (r * cols)]->inMaze) {
            int dir;
            int nr;
            int nc;
            do {
                dir = rng() % 4;
                nr = r + dr[dir];
                nc = c + dc[dir];
            } while (nr < 0 || nr >= rows || nc < 0 || nc >= cols);

            direction[r][c] = dir;
            r = nr;
            c = nc;
        }

        r = walkStartR;
        c = walkStartC;
        while (!grid[c + (r * cols)]->inMaze) {
            int dir = direction[r][c];
            removeWall(r, c, dir);
            if (animate) {
                clear();
                renderer->drawMaze(*this);
                refresh();
                napms(50);
            }
            grid[c + (r * cols)]->inMaze = true;
            cellsInMaze++;

            direction[r][c] = -1;

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
        grid[c + (r * cols)]->north = false;
        grid[nc + (nr * cols)]->south = false;
    } 
    if (dir == 1) {
        grid[c + (r * cols)]->south = false; 
        grid[nc + (nr * cols)]->north = false;
    }
    if (dir == 2) {
        grid[c + (r * cols)]->east = false;
        grid[nc + (nr * cols)]->west = false;
    }
    if (dir == 3) {
        grid[c + (r * cols)]->west = false;
        grid[nc + (nr * cols)]->east = false;
    }
}

void Maze::findEscapePath(const Cell& startCell, const Cell& exitCell) {
    std::queue<std::reference_wrapper<const Cell>> queue;             
    int numCells = rows * cols;
    bool visited[numCells];
    for (int i = 0; i < numCells; ++i) {
        visited[i] = false;
    }
    
    visited[startCell.getCellPos()] = true;
    escapePath.push_back(startCell);
    queue.push(startCell);

    while (!queue.empty()) {
        const Cell& currCell = queue.front();
        queue.pop();
        
        if (currCell.getCellPos() == exitCell.getCellPos()) return;
       
        for (int i = 0; i < 4; ++i) {
            if (currCell.north && i == 0) continue;
            if (currCell.south && i == 1) continue;
            if (currCell.east && i == 2) continue;                
            if (currCell.west && i == 3) continue;
            
            int nextRow = currCell.getCellRow() + directions[i][0];
            int nextCol = currCell.getCellCol() + directions[i][1];
            
            if (0 <= nextRow && nextRow < rows && 0 <= nextCol && nextCol < cols) {
                int nextPos         = nextCol + (nextRow * cols);
                const Cell& nextCell = *grid[nextCol + (nextRow * cols)];

                if (!visited[nextPos]) {
                    visited[nextPos] = true;
                    escapePath.push_back(nextCell);
                    queue.push(nextCell);
                }
            }
        }
    }
    std::reverse(escapePath.begin(), escapePath.end());
}