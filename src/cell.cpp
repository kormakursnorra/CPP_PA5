#include "cell.h"
#include <cassert>

Cell::Cell(int x, int y) : x(x), y(y), visited(false) {
    walls[0] = walls[1] = walls[2] = walls[3] = true;
}

int Cell::getX() const { return x; }
int Cell::getY() const { return y; }

void Cell::removeWall(int direction) {
    assert(direction >= 0 && direction < 4);
    walls[direction] = false;
}

bool Cell::hasAllWalls() const {
    return walls[0] && walls[1] && walls[2] && walls[3];
}