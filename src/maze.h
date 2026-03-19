#ifndef MAZE_H
#define MAZE_H

#include <random>
#include <vector>
#include "cell.h"


using matrix = std::vector<std::vector<Cell>>;

class Maze {
private:
    int width, height;
    matrix grid;
    std::mt19937 randNum;

    void carveMaze(int width, int height);
    void removeWall(Cell& curr, Cell& next);

public:
    Maze(int width, int height);
    void generateMaze();
    void displayMaze();
    
    int getCols() const { return static_cast<int>(width); };
    int getRows() const { return static_cast<int>(height); };
    const matrix& getGrid() const { return grid; };

    std::vector<Cell*> getUnvisitedNeighbors(Cell& cell);
};

#endif