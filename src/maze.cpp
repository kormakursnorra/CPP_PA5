#include "maze.h"
#include <algorithm>
#include <random>

Maze::Maze(int rows, int cols) 
    : rows(rows), cols(cols), 
    grid(rows, std::vector<Cell>(cols)) {}

void Maze::generate() {
    carve(0,0);
}

void Maze::carve(int r, int c) {
    grid[r][c].visited = true;
    // Order : North, South, East, West
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    int dirs[] = {0, 1, 2, 3};
    std::shuffle(dirs, dirs + 4, std::mt19937{std::random_device{}()});

    for (int i = 0; i < 4; i++) {
        int d = dirs[i];
        int nr = r + dr[d];
        int nc = c + dc[d];

        // check if neighbor is in bound and make sure it has not been visited
        if (nr >= 0 && nr < rows && nc >= 0 &&
            nc < cols && !grid[nr][nc].visited) {
            if (d == 0) {
                grid[r][c].north = false;
                grid[nr][nc].south = false;
            } else if (d == 1) {
                grid[r][c].south = false;
                grid[nr][nc].north = false;
            } else if (d == 2) {
                grid[r][c].east = false;
                grid[nr][nc].west = false;
            }else if (d == 3) { 
                grid[r][c].west = false;
                grid[nr][nc].east = false;
            }
            carve(nr, nc);
        }
    };
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