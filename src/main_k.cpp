#include <ctime>
#include <functional>
#include <ncurses.h>
#include <iostream>

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

void endScreen(std::string msg, std::string statMsg, int stats) {
    timeout(-1);
    clear();
    int maxX = getmaxx(stdscr);
    int maxY = getmaxy(stdscr);

    int msgRow  = maxY / 2 - 6;
    int statRow = msgRow + 2;
    int exitRow = statRow + 4;

    std::string exitMsg = "--- Press any key ---"; 

    attron(A_BOLD | COLOR_PAIR(6));
    mvprintw(msgRow - 1, (maxX - (int)msg.size()) / 2, "%s", msg.c_str());
    mvprintw(statRow, (maxX - (int)statMsg.size()) / 2, "%s %d" , statMsg.c_str(), stats);
    mvprintw(exitRow, (maxX - (int)exitMsg.size()) / 2, "%s", exitMsg.c_str());
    attroff(A_BOLD | COLOR_PAIR(6));
}

bool runGame(Renderer& renderer, Difficulty diff) {
    DifficultyConfig config = getDifficultyConfig(diff);
    Maze maze(config.rows, config.cols, true);
    maze.wilson(&renderer);
    
    Player player(0, 0, maze.getRows(), maze.getCols());
    int statusRow = maze.getRows() * 2 + 2;
    // Draw everything once before loop
    renderer.drawMaze(maze);
    renderer.drawStatus(statusRow, player.getMistakes(), config.timeLimit);
    renderer.drawStart(0, 0);
    renderer.drawEnd(maze.getExitRow(), maze.getExitCol());
    renderer.drawPlayer(player.getRow(), player.getCol());
    renderer.mazeRefresh();

    time_t startTime = time(nullptr);
    timeout(100);
    flushinp();
    int ch;
    while ((ch = getch()) != 'q') {
        int elapsed  = (int)(time(nullptr) - startTime);
        int timeLeft = config.timeLimit - elapsed;
        renderer.drawStatus(statusRow, player.getMistakes(), timeLeft);

        if (timeLeft <= 0) {
            // Redraw clean maze then animate escape path
            renderer.mazeRefresh();
            renderer.drawMaze(maze);
            renderer.drawStart(0, 0);
            renderer.drawEnd(maze.getExitRow(), maze.getExitCol());
            renderer.mazeRefresh();
            renderer.drawEscapePath(maze);

            std::string msg     = "Time's up! The Maze claims another victim...";
            std::string statMsg = "Mistakes Made:"; 
            endScreen(msg, statMsg, player.getMistakes());  
            renderer.mazeRefresh();
            flushinp(); 
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
                    renderer.drawBreadcrumbs(oldRow, oldCol);
 
                    if (oldRow == 0 && oldCol == 0)
                        renderer.drawStart(0, 0);
                    if (oldRow == maze.getExitRow() && oldCol == maze.getExitCol())
                        renderer.drawEnd(maze.getExitRow(), maze.getExitCol());
 
                    renderer.drawPlayer(player.getRow(), player.getCol());
                }
            }
        }
 
        renderer.mazeRefresh();
 
        if (player.getRow() == maze.getExitRow() &&
            player.getCol() == maze.getExitCol()) {
                int finalScore = calculateScore(diff, config.timeLimit, 
                    config.timeLimit - timeLeft, player.getMistakes());
                
                std::string msg     = "Congratulations, you escaped the Maze!";
                std::string statMsg = "Final Score:"; 
                endScreen(msg, statMsg, finalScore);
                renderer.mazeRefresh();
                flushinp();
                getch();
                return true;
        }
    }
    return false;
}

int main() {
    Renderer renderer;
    Menu menu;
 
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
 
    while (true) {
        MenuResult result; 
        menu.showMain(result);
 
        if (result == MenuResult::QUIT) break;
 
        if (result == MenuResult::CONTROLS) {
            menu.showControls();
            continue;
        }
 
        if (result == MenuResult::PLAY) {
            Difficulty diff;
            menu.showDifficulty(diff, result);
            if (result == MenuResult::BACK) continue;
            if (result == MenuResult::QUIT) break;;
            clear();
            runGame(renderer, diff);
        }
    }
 
    return 0;
}