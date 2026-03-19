#pragma once
#include "maze.h"

class Player {
public:
    Player(int startRow, int startCol);
    bool move(int dr, int dc, const Maze& maze); // return true if move valid
    int getRow() const;
    int getCol() const;
    int getMistakes() const;

private:
    int row, col;
    int mistakes;
};