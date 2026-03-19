#include "maze_k.h"
#include "player_k.h"

Player::Player(int startRow, int startCol) {
    row = startRow;
    col = startCol;
    mistakes = 0;
}

bool Player::move(int dr, int dc, const Maze& maze) {
    const Cell& cell = maze.getCell(row, col);
    if (dr == -1 && cell.walls.north) {
        mistakes++;
        return false;
    } else if (dr == 1 && cell.walls.south) {
        mistakes++;
        return false;
    } else if (dc == 1 && cell.walls.east) {
        mistakes++;
        return false;
    } else if (dc == -1 && cell.walls.west) {
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