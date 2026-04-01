#pragma once
#include "maze.h"

class Player {
public:
    Player(int startRow, int startCol, int mazeRows, int mazeCols);
    bool move(int dr, int dc, const Maze& maze); // return true if move valid
    
    int getRow() const { return row; };
    int getCol() const { return col; };
    int getMistakes() const { return mistakes; };
    
    bool hasVisited(int r, int c, int cols) const { return visited[c + (r * cols)]; };

private:
    int row, col;
    int mistakes;
    std::vector<bool> visited;
};