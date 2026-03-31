#pragma once
#include "maze.h"

class Player {
public:
    Player(int startRow, int startCol, int mazeRows, int mazeCols);
    bool move(int dr, int dc, const Maze& maze); // return true if move valid
    int getRow() const;
    int getCol() const;
    int getMistakes() const;
    bool hasVisited(int r, int c) const;

private:
    int row, col;
    int mistakes;
    std::vector<std::vector<bool>> visited;
};