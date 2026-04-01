#pragma once

#include <queue>
#include <vector>
#include <memory>
#include <ncurses.h>
#include <functional>

class Renderer;

struct Cell {
    bool north;
    bool south;
    bool east;
    bool west;
    bool visited;
    bool inMaze;
    int  cellRow;
    int  cellCol;
    int  cellPos;

    Cell(int row, int col, int pos)
        : north(true), south(true), east(true), west(true),
          visited(false), inMaze(false), cellRow(row), cellCol(col), cellPos(pos) {};
    
    int getCellRow() const { return cellRow; };
    int getCellCol() const { return cellCol; };  
    int getCellPos() const { return cellPos; };
};

using MazeGrid = std::vector<std::unique_ptr<Cell>>; 
using Path = std::vector<std::reference_wrapper<const Cell>>;
class Maze {
private:
    int rows;
    int cols;
    int exitRow;
    int exitCol;
    bool animate;
    MazeGrid grid;
    Path escapePath;
    const int directions[4][2] = {
        {0, 1}, {1, 0}, 
        {0, -1}, {-1, 0}
    };
    
    void removeWall(int r, int c, int dir);
    void findEscapePath(const Cell& startCell, const Cell& exitCell);

public:
    Maze(int rows, int cols, bool animate = false);
    void wilson(Renderer* renderer = nullptr);

    
    int getRows() const { return rows; };
    int getCols() const { return cols; };
    int getExitRow() const { return exitRow; };
    int getExitCol() const { return exitCol; };
    
    const Cell&     getCell(int r, int c) const { return *grid.at(c + (r * cols)); };
    const MazeGrid& getGrid() const { return const_cast<MazeGrid&>(grid); };
    const Path      getEscapePath() const { return escapePath; }
};