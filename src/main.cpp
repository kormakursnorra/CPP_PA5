#include <iostream>
#include <ncurses.h>

#include "maze.h"
#include "renderer.h"
#include "player.h"

int main() {
    Maze maze(25, 25);
    maze.generate();
    Player player(0, 0);
    Renderer renderer;
    renderer.drawMaze(maze);
    renderer.drawPlayer(player.getRow(), player.getCol());
    renderer.mazeRefresh();

    int ch;
    while ((ch = getch()) != 'q') {
        int dr = 0, dc = 0;
        if (ch == KEY_UP) {
            dr = -1;
        }
        if (ch == KEY_DOWN) {
            dr = 1;
        }
        if (ch == KEY_RIGHT) {
            dc = 1;
        }
        if (ch == KEY_LEFT) {
            dc = -1;
        }

        if (dr != 0 || dc != 0) {
            player.move(dr, dc, maze);
        }

        // redraw maze
        clear();
        renderer.drawMaze(maze);
        renderer.drawPlayer(player.getRow(), player.getCol());
        renderer.mazeRefresh();

        if (player.getRow() == maze.getRows() - 1 &&
            player.getCol() == maze.getCols() - 1) {
                clear();
                mvprintw(maze.getRows() + 2, 0, "You Win! Mistakes: %d", player.getMistakes());
                renderer.mazeRefresh();
                getch();
                break;
            }
    }
    renderer.drawMaze(maze);
    return 0;
}