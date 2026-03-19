#include <cassert>
#include <math.h>
#include <cstdlib>

#include <ncurses.h>
#include "maze_k.h"
#include "player_k.h"
#include "renderer_k.h"

// int main(int argc, char* argv[]) {
//     int width = 32;
//     int height = 32;
    
//     if (argc == 3) {
//         int tmp_w = atoi(argv[1]);
//         int tmp_h = atoi(argv[2]);

//         int lg_width = (int)log2(tmp_w);
//         int lg_height = (int)log2(tmp_h);

//         if (lg_width % 2 == 0) width = tmp_w;
//         else width = 1U << (int)(
//             log2(tmp_w - 1) + 1);
        
//         if (lg_height % 2 == 0) height = tmp_h;
//         else height = 1U << (int)(
//             log2(tmp_h - 1) + 1);
//     }

//     assert(width % 2 == 0 && height % 2 == 0);
//     Maze maze(width, height);
//     maze.generateMaze();
//     return 0;
// }

int main() {
    Maze maze(25, 25);
    maze.generateMaze();
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