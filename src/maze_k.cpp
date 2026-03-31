#include "maze_k.h"

#include <random>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <algorithm>


Maze::Maze(int width, int height) 
: width(width), height(height), randNum(std::random_device{}()) {
    for (int y = 0; y < height; ++y) {
        std::vector<Cell> row;
        for (int x = 0; x < width; ++x) {
            row.push_back(Cell(x, y));
        }
        grid.push_back(row);
    }
}

// void Maze::carve(int r, int c) {
//     grid[r][c].visited = true;
//     // Order : North, South, East, West
//     int dr[] = {-1, 1, 0, 0};
//     int dc[] = {0, 0, 1, -1};

//     int dirs[] = {0, 1, 2, 3};
//     std::shuffle(dirs, dirs + 4, std::mt19937{std::random_device{}()});

//     for (int i = 0; i < 4; i++) {
//         int d = dirs[i];
//         int nr = r + dr[d];
//         int nc = c + dc[d];

//         // check if neighbor is in bound and make sure it has not been visited
//         if (nr >= 0 && nr < rows && nc >= 0 &&
//             nc < cols && !grid[nr][nc].visited) {
//             if (d == 0) {
//                 grid[r][c].north = false;
//                 grid[nr][nc].south = false;
//             } else if (d == 1) {
//                 grid[r][c].south = false;
//                 grid[nr][nc].north = false;
//             } else if (d == 2) {
//                 grid[r][c].east = false;
//                 grid[nr][nc].west = false;
//             }else if (d == 3) { 
//                 grid[r][c].west = false;
//                 grid[nr][nc].east = false;
//             }
//             carve(nr, nc);
//         }
//     };
// }


void Maze::generateMaze() {
    std::vector<Cell*> stack;
    Cell* current = &grid[0][0];
    current->visited = true;
    
    while (true) {
        std::vector<Cell*> neighbors = getUnvisitedNeighbors(*current);
        if (!neighbors.empty()) {
            std::shuffle(neighbors.begin(), 
                        neighbors.end(), 
                        randNum);

            Cell* next = neighbors.front(); 
            
            stack.push_back(current);
            removeWall(*current, *next);
            
            current = next;
            current->visited = true;
        }
        else if (!stack.empty()) {
            current = stack.back();
            stack.pop_back();
        }
        else {
            break;
        }
    }
}

std::vector<Cell*> Maze::getUnvisitedNeighbors(Cell& cell) {
    std::vector<Cell*> neighbors;   
    int x = cell.getX(); 
    int y = cell.getY();

    if (y > 0 && !grid[y - 1][x].visited) {
        neighbors.push_back(&grid[y - 1][x]);
    }
    if (y < height - 1 && !grid[y + 1][x].visited) {
        neighbors.push_back(&grid[y + 1][x]);
    }
    if (x > 0 && !grid[y][x - 1].visited) {
        neighbors.push_back(&grid[y][x - 1]);
    }
    if (x < width - 1 && !grid[y][x + 1].visited) {
        neighbors.push_back(&grid[y][x + 1]);
    }
    
    return neighbors;
}

void Maze::removeWall(Cell& curr, Cell& next) {
    int dx = curr.getX() - next.getX();
    Walls& currWalls = curr.walls;
    Walls& nextWalls = next.walls;

    if (dx == 1) {
        currWalls.south = false;
        nextWalls.east = false;
    } else if (dx == -1) {
        currWalls.east = false;
        nextWalls.south = false;
    }
    
    int dy = curr.getY() - next.getY();
    if (dy == 1) {
        currWalls.north = false;
        nextWalls.west = false;
    } else if (dy == -1) {
        currWalls.west = false;
        nextWalls.north = false;
    }
}

