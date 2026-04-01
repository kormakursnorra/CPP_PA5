#include "maze.h"
#include "player_k.h"

Player::Player(int startRow, int startCol, int mazeRows, int mazeCols) 
    : row(startRow), col(startCol), mistakes(0),
    visited(mazeRows * mazeCols, false) {
        visited[startCol + (startRow * mazeCols)] = true;
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
    visited[col + (row * maze.getCols())] = true;
    return true;
}