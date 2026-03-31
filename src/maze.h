#pragma once
#include <vector>

class Renderer;
struct Cell {
    bool north = true; // ture = wall exists
    bool south = true;
    bool east = true;
    bool west = true;
    bool visited = false;
    bool inMaze = false; // Used by wilson
};

class Maze {
public:
    Maze(int rows, int cols, bool animate = false);
    void wilson(Renderer* renderer = nullptr);
    const Cell& getCell(int r, int c) const;
    int getRows() const;
    int getCols() const;
    int getExitRow() const;
    int getExitCol() const;

private:
    int rows;
    int cols;
    int exitRow;
    int exitCol;
    bool animate;
    std::vector<std::vector<Cell>> grid;
    void removeWall(int r, int c, int dir);
};