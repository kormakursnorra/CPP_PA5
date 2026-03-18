#pragma once
#include <vector>

struct Cell {
    bool north = true; // ture = wall exists
    bool south = true;
    bool east = true;
    bool west = true;
    bool visited = false;
};

class Maze {
public:
    Maze(int rows, int cols);
    void generate();
    const Cell& getCell(int r, int c) const;
    int getRows() const;
    int getCols() const;

private:
    int rows, cols;
    std::vector<std::vector<Cell>> grid;
    void carve(int r, int c);
};