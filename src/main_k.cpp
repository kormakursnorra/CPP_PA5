#include <ctime>
#include <ncurses.h>

#include "maze.h"
#include "menu.h"
#include "player_k.h"
#include "renderer_k.h"


int calculateScore(Difficulty diff, int timeLimit, int timeTaken, int mistakes) {
    auto getBase = [&](Difficulty diff) -> int {
        switch(diff) {
            case Difficulty::EASY:      return 1000;
            case Difficulty::MEDIUM:    return 2000;
            case Difficulty::HARD:      return 3000;
            case Difficulty::NO_ESCAPE: return 4000;
        } return 1000;

    };

    float timeBonus   = std::max(0.1f, (float)(timeLimit - timeTaken) / timeLimit);
    float mistakePen  = 1.0f / (1.0f + mistakes);
    return (int)(getBase(diff) * timeBonus * mistakePen);
}

bool runGame(Renderer& renderer, Difficulty diff) {
    DifficultyConfig cfg = getDifficultyConfig(diff);
    Maze maze(cfg.rows, cfg.cols, true);
    maze.wilson(&renderer);
 
    Player player(0, 0, maze.getRows(), maze.getCols());
    int statusRow = maze.getRows() * 2 + 2;
    // Draw everything once before loop
    renderer.drawMaze(maze);
    renderer.drawStatus(statusRow, player.getMistakes(), cfg.timeLimit);
    renderer.drawStart(0, 0);
    renderer.drawEnd(maze.getExitRow(), maze.getExitCol());
    renderer.drawPlayer(player.getRow(), player.getCol());
    renderer.mazeRefresh();

    time_t startTime = time(nullptr);
    timeout(100);
 
    int ch;
    while ((ch = getch()) != 'q') {
        int elapsed  = (int)(time(nullptr) - startTime);
        int timeLeft = cfg.timeLimit - elapsed;
 
        if (timeLeft <= 0) {
            // Redraw clean maze then animate escape path
            renderer.drawMaze(maze);
            renderer.drawStart(0, 0);
            renderer.drawEnd(maze.getExitRow(), maze.getExitCol());
            renderer.mazeRefresh();
            renderer.drawEscapePath(maze);
 
            timeout(-1);
            clear();
            mvprintw(cfg.rows + 2, 0,
                "Time's up! You lose. Mistakes: %d -- Press any key...",
                player.getMistakes());
            renderer.mazeRefresh();
            getch();
            return false;
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
 
                    if (oldRow == 0 && oldCol == 0)
                        renderer.drawStart(0, 0);
                    if (oldRow == maze.getExitRow() && oldCol == maze.getExitCol())
                        renderer.drawEnd(maze.getExitRow(), maze.getExitCol());
 
                    renderer.drawPlayer(player.getRow(), player.getCol());
                }
            }
        }
 
        renderer.drawStatus(statusRow, player.getMistakes(), timeLeft);
        renderer.mazeRefresh();
 
        if (player.getRow() == maze.getExitRow() &&
            player.getCol() == maze.getExitCol()) {
                timeout(-1);
                clear();
                int timeTaken = cfg.timeLimit - timeLeft;
                int finalScore = calculateScore(
                    diff, cfg.timeLimit, timeTaken, 
                    player.getMistakes());
                mvprintw(cfg.rows + 2, 0,
                    "You Win! Final Score: %d -- Press any key...",
                    finalScore);
                renderer.mazeRefresh();
                getch();
                return true;
        }
    }
    return false;
}

int main() {
    Renderer renderer;
    Menu menu;
 
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
 
    while (true) {
        MenuResult result = menu.showMain();
 
        if (result == MenuResult::QUIT) break;
 
        if (result == MenuResult::CONTROLS) {
            menu.showControls();
            continue;
        }
 
        if (result == MenuResult::PLAY) {
            Difficulty diff = menu.showDifficulty();
            clear();
            runGame(renderer, diff);
        }
    }
 
    return 0;
}