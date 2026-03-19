#ifndef MAZE_H
#define MAZE_H

#include <random>
#include <vector>
#include "cell.h"


class Maze {
private:
    int width, height;
    std::vector<std::vector<Cell>> grid;
    std::mt19937 randNum;

    void carveMaze(int width, int height);

public:
    Maze(int width, int height);
    void generateMaze();
    void displayMaze();
    
    std::vector<Cell*> getUnvisitedNeighbors(Cell& cell);
    void removeWall(Cell& curr, Cell& next);
    
    const std::vector<std::vector<Cell>>& getGrid() const;
};

#endif