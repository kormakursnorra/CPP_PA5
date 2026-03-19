#include "maze.h"
#include "cell.h"

#include <random>
#include <vector>
#include <cassert>
#include <sstream>
#include <cstdlib>
#include <iostream>
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
        curr.walls[3] = false;
        next.walls[1] = false;
    } else if (dx == -1) {
        curr.walls[1] = false;
        next.walls[3] = false;
    }
    
    int dy = curr.getY() - next.getY();
    if (dy == 1) {
        curr.walls[0] = false;
        next.walls[2] = false;
    } else if (dy == -1) {
        curr.walls[2] = false;
        next.walls[0] = false;
    }
}

void Maze::displayMaze() {
    std::stringstream strStream;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const Cell c = grid[y][x];
            if (c.walls[0]) strStream << "═";
            else            strStream << " ";

            // if (c.walls[0] && c.walls[1]) strStream << "╔";
            // if (c.walls[0] && c.walls[3]) strStream << "╗";
        }

        strStream << "\n";
        strStream << "║ ";
        
        for (int x = 0; x < width; ++x) {
            // const Cell c = grid[y][x];
            // if (c.walls[1]) strStream << "║ ";
            // else            strStream << " ";
            strStream << " ";
        }

        strStream << " ║\n";

        for (int x = 0; x < width; ++x) {
            const Cell c = grid[y][x];
            if (c.walls[2]) strStream << "═";
            else            strStream << " ";
        }
    }
    std::cout << strStream.str();
}

const std::vector<std::vector<Cell>>& Maze::getGrid() const {
    return grid;
}