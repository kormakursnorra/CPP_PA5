#include "player.h"
#include "maze.h"

Player::Player(int startRow, int startCol) {
    row = startRow;
    col = startCol;
    mistakes = 0;
}

bool Player::move(int dr, int dc, const Maze& maze) {
    const Cell& cell = maze.getCell(row, col);
    if (dr == -1 && cell.north) {
        mistakes++;
        return false;
    } else if (dr == 1 && cell.south) {
        mistakes++;
        return false;
    } else if (dc == 1 && cell.east) {
        mistakes++;
        return false;
    } else if (dc == -1 && cell.west) {
        mistakes++;
        return false;
    }
    row += dr;
    col += dc;
    return true;
}

int Player::getRow() const {
    return row;
}

int Player::getCol() const {
    return col;
}

int Player::getMistakes() const {
    return mistakes;
}