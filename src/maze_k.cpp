#include "maze.h"

#include <random>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <algorithm>


Maze::Maze(int columns, int rows) 
: columns(columns), rows(rows), numCells(columns * rows), randNum(std::random_device{}()) {
    std::vector<Cell*> grid(numCells);
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            int newPos    = x + y * columns;
            Cell *newCell = new Cell(x, y, newPos);
            grid[newPos]  = newCell;
        }
    }
}

void Maze::generateMaze() {
    std::vector<Cell*> stack;
    Cell* current = grid[0];
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
    int cellX   = cell.getX();
    int cellY   = cell.getY();
    int cellPos = cell.getPos();

    if (cellPos > 0 && !grid[x + (y - 1 * columns)]->visited) {
        neighbors.push_back(grid[x][y - 1]);
    }
    if (y < rows - 1 && !grid[x][y + 1]->visited) {
        neighbors.push_back(grid[x][y + 1]);
    }
    if (x > 0 && !grid[x - 1][y]->visited) {
        neighbors.push_back(grid[x - 1][y]);
    }
    if (x < columns - 1 && !grid[x + 1][x]->visited) {
        neighbors.push_back(grid[x + 1][y]);
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

