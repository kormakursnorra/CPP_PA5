#include "maze_k.h"

#include <random>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <algorithm>


Maze::Maze(int width, int height) 
: width(width), height(height), randNum(std::random_device()()) {
    for (int y = 0; y < height; ++y) {
        std::vector<Cell> row;
        for (int x = 0; x < width; ++x) {
            row.push_back(Cell(x, y));
        }
        grid.push_back(row);
    }
}

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
    if (dx == 1) {
        curr.walls.south = false;
        next.walls.east = false;
    } else if (dx == -1) {
        curr.walls.east = false;
        next.walls.south = false;
    }
    
    int dy = curr.getY() - next.getY();
    if (dy == 1) {
        curr.walls.north = false;
        next.walls.west = false;
    } else if (dy == -1) {
        curr.walls.west = false;
        next.walls.north = false;
    }
}