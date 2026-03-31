#ifndef CELL_K_H
#define CELL_K_H

struct Walls {
    bool north;
    bool south;
    bool east;
    bool west;

    Walls(bool set) : north(set), south(set), east(set), west(set) {}; 
};

class Cell {
private:
    int x, y, pos;

public:
    Cell(int x, int y, int pos) : x(x), y(y), pos(pos), 
                                walls(true), visited(false) {};
    Walls walls;
    bool visited;

    int getX() const { return x; };
    int getY() const { return y; };
    int getPos() const { return pos; }
};


#endif 