#include <iostream>
#include <ncurses.h>

#include "maze.h"
#include "renderer.h"
#include "player.h"

int main() {
    Maze maze(25, 25);
    Renderer renderer;
    maze.wilson(&renderer);
    Player player(0, 0, maze.getRows(), maze.getCols());
    // Draw everything once before loop
    renderer.drawMaze(maze);
    renderer.drawStart(0, 0);
    renderer.drawEnd(maze.getExitRow(), maze.getExitCol());
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
            int oldRow = player.getRow();
            int oldCol = player.getCol();

            if (player.move(dr, dc, maze)) {
                mvaddch(oldRow * 2 + 1, oldCol * 3 + 1, '.' | COLOR_PAIR(4));

                if (oldRow == 0 && oldCol == 0) {
                    renderer.drawStart(0,0);
                } if (oldRow == maze.getExitRow() && oldCol == maze.getExitCol()) {
                    renderer.drawEnd(maze.getExitRow(), maze.getExitCol());
                }

                renderer.drawPlayer(player.getRow(), player.getCol());
            }
        }

        renderer.mazeRefresh();

        if (player.getRow() == maze.getExitRow() &&
            player.getCol() == maze.getExitCol()) {
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