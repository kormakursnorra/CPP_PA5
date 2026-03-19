#ifndef CELL_H
#define CELL_H

struct Walls {
    bool north;
    bool south;
    bool east;
    bool west;
};

class Cell {
private:
    int x, y;

public:
    Cell(int x, int y);
    Walls walls;
    bool visited;

    int getX() const;
    int getY() const;
    void removeWall(int direction);
    bool hasAllWalls() const;
};


#endif 