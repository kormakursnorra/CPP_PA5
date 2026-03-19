#ifndef CELL_H
#define CELL_H

class Cell {
private:
    int x, y;

public:
    Cell(int x, int y);
    bool visited;
    bool walls[4]; // Top: 0, Right: 1, Bottom: 2, Left: 3 

    int getX() const;
    int getY() const;
    void removeWall(int direction);
    bool hasAllWalls() const;
};


#endif 