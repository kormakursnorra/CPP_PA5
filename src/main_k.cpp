#include <ctime>
#include <ncurses.h>

#include "maze.h"
#include "player_k.h"
#include "renderer_k.h"

int main() {
    Maze maze(15, 15, true);
    Renderer renderer;
    maze.wilson(&renderer);
    Player player(0, 0, maze.getRows(), maze.getCols());
    int statusRow = maze.getRows() * 2 + 2;
    // Draw everything once before loop
    renderer.drawMaze(maze);
    renderer.drawStatus(statusRow, player.getMistakes(), 120);
    renderer.drawStart(0, 0);
    renderer.drawEnd(maze.getExitRow(), maze.getExitCol());
    renderer.drawPlayer(player.getRow(), player.getCol());
    renderer.mazeRefresh();

    int timeLimit = 120;
    time_t startTime = time(nullptr);

    timeout(100);

    int ch;
    while ((ch = getch()) != 'q') {
        int elapsed = (int)(time(nullptr) - startTime);
        int timeLeft = timeLimit - elapsed;

        if (timeLeft <= 0) {
            clear();
            mvprintw(maze.getRows() + 2, 0, "Times up! You loose. Mistakes: %d",
            player.getMistakes());
            renderer.mazeRefresh();
            getch();
            break;
        }
        if (ch != ERR) {
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
        }
        renderer.drawStatus(statusRow, player.getMistakes(), timeLeft);
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