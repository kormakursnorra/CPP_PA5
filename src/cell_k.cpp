#include "cell_k.h"
#include <cassert>

Cell::Cell(int x, int y) : x(x), y(y), visited(false) {
    walls.north = walls.south = walls.east = walls.west = true;
}

int Cell::getX() const { return x; }
int Cell::getY() const { return y; }