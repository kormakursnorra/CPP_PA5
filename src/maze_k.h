#ifndef MAZE_K_H
#define MAZE_K_H

#include <random>
#include <vector>
#include "cell_k.h"

using MazeGrid = std::vector<std::vector<Cell*>>;

class Maze {
private:
    int rows;
    int columns;
    int numCells;
    MazeGrid grid;
    std::mt19937 randNum;

    void carveMaze(int colums, int rows);
    void removeWall(Cell& curr, Cell& next);

public:
    Maze(int colums, int rows);
    void generateMaze();
    void displayMaze();
    
    int getRows() const { return rows; };
    int getCols() const { return columns; };
    int getNumCells() const { return numCells; }
    MazeGrid& getGrid() const { return const_cast<MazeGrid&>(grid); };
    Cell& getCell(int x, int y) const { return *grid[x][y]; }

    std::vector<Cell*> getUnvisitedNeighbors(Cell& cell);
};

#endif