#include <iostream>
#include <ncurses.h>
#include "maze.h"
#include "renderer.h"
#include <algorithm>
#include <random>

Maze::Maze(int rows, int cols, bool animate) 
    : rows(rows), cols(cols), animate(animate),
    grid(rows, std::vector<Cell>(cols)) {}

void Maze::wilson(Renderer* renderer) {
    // Dir offset: N, S, E, W
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    std::mt19937 rng{std::random_device{}()};

    // Pick a random cell
    int startR = rng() % rows;
    int startC = rng() % cols;
    grid[startR][startC].inMaze = true;

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
        } while (grid[r][c].inMaze);

        int walkStartR = r;
        int walkStartC = c;

        while(!grid[r][c].inMaze) {
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
        while (!grid[r][c].inMaze) {
            int dir = direction[r][c];
            removeWall(r, c, dir);
            if (animate) {
                clear();
                renderer->drawMaze(*this);
                refresh();
                napms(50);
            }
            grid[r][c].inMaze = true;
            cellsInMaze++;

            direction[r][c] = -1;

            r = r + dr[dir];
            c = c + dc[dir];
        }

    }

    exitRow = rows - 1;
    exitCol = cols - 1;
}

void Maze::removeWall(int r, int c, int dir) {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    int nr = r + dr[dir];
    int nc = c + dc[dir];

    if (dir == 0) {
        grid[r][c].north = false;
        grid[nr][nc].south = false;
    } 
    if (dir == 1) {
        grid[r][c].south = false; 
        grid[nr][nc].north = false;
    }
    if (dir == 2) {
        grid[r][c].east = false;
        grid[nr][nc].west = false;
    }
    if (dir == 3) {
        grid[r][c].west = false;
        grid[nr][nc].east = false;
    }
}

const Cell& Maze::getCell(int r, int c) const{
    return grid[r][c];
}

int Maze::getRows() const {
    return rows;
}

int Maze::getCols() const {
    return cols;
}

int Maze::getExitRow() const {
    return exitRow;
}

int Maze::getExitCol() const {
    return exitCol;
}