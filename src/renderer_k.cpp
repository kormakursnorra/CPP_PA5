#include "renderer_k.h"
#include <ncurses.h>

Renderer::Renderer() {
    initscr();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK); // player
    init_pair(2, COLOR_RED, COLOR_BLACK); // start
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // exit
    init_pair(4, COLOR_CYAN, COLOR_BLACK); // breacrumbs
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
}

Renderer::~Renderer() {
    endwin();
}

void Renderer::computeOffsets(const Maze& maze) {
    int screenRows, screenCols;
    getmaxyx(stdscr, screenRows, screenCols);
    int mazeRows = maze.getRows() * 2 + 1;
    int mazeCols = maze.getCols() * 3 + 1;
    rowOffset = std::max(0, (screenRows - mazeRows - 2) / 2);
    colOffset = std::max(0, (screenCols - mazeCols) / 2);
}

void Renderer::drawMaze(const Maze& maze) {
    computeOffsets(maze);
    int rows = maze.getRows();
    int cols = maze.getCols();
    // draw coners
    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j <= cols; j++) {
            bool right = false;
            if (j < cols) {
                if (i == 0 || i == rows) {
                    right = true;
                } else if (maze.getCell(i, j).north) {
                    right = true;
                }
            }
            bool left = false;
            if (j > 0) {
                if (i == 0 || i == rows) {
                    left = true;
                } else if (maze.getCell(i, j - 1).north) {
                    left = true;
                }
            }

            bool down = false;
            if (i < rows) {
                if (j == 0 || j == cols) {
                    down = true;
                } else if (maze.getCell(i, j).west) {
                    down = true;
                }
            }

            bool up = false;
            if (i > 0) {
                if (j == 0 || j == cols) {
                    up = true;
                } else if (maze.getCell(i - 1, j).west) {
                    up = true;
                }
            }
            chtype ch = ' ';
            if (up && down && left && right) { ch = ACS_PLUS; }
            else if (up && down && right) { ch = ACS_LTEE; }
            else if (up && down && left) { ch = ACS_RTEE; }
            else if (up && left && right) { ch = ACS_BTEE; }
            else if (down && left && right) { ch = ACS_TTEE; }
            else if (up && down) { ch = ACS_VLINE; }
            else if (left && right) { ch = ACS_HLINE; }
            else if (down && right) { ch = ACS_ULCORNER; }
            else if (down && left) { ch = ACS_URCORNER; }
            else if (up && right) { ch = ACS_LLCORNER; }
            else if (up && left) { ch = ACS_LRCORNER; }
            else if (up) { ch = ACS_VLINE; }
            else if (down) { ch = ACS_VLINE; }
            else if (left) { ch = ACS_HLINE; }
            else if (right) { ch = ACS_HLINE; }

            mvaddch(rowOffset + i * 2, colOffset + j * 3, ch);
        }
    }
    // Draw north walls of each cell
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int sr = r * 2;
            int sc = c * 3;
            if (maze.getCell(r, c).north) {
                mvaddch(rowOffset + sr, colOffset + sc + 1, ACS_HLINE);
                mvaddch(rowOffset + sr, colOffset + sc + 2, ACS_HLINE);
            }
        }
    }
    // Draw bottom border
    for (int c = 0; c < cols; c++) {
        int sc = c * 3;
        mvaddch(rowOffset + rows * 2, colOffset + sc + 1, ACS_HLINE);
        mvaddch(rowOffset + rows * 2, colOffset + sc + 2, ACS_HLINE);
    }
    // Draw vertical walls
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int sr = r * 2;
            int sc = c * 3;
            if (maze.getCell(r, c).west) {
                mvaddch(rowOffset + sr + 1, colOffset + sc, ACS_VLINE);
            }
        }
    }

    for (int r = 0; r < rows; r++) {
        mvaddch(rowOffset + r * 2 + 1, colOffset + cols * 3, ACS_VLINE);
    }
}

void Renderer::drawPlayer(int r, int c) {
    mvaddch(rowOffset + r * 2 + 1, colOffset + c * 3 + 1, '@' | COLOR_PAIR(1));
}

void Renderer::mazeRefresh() {
    refresh();
}

void Renderer::drawStart(int r, int c) {
    mvaddch(rowOffset + r * 2 + 1, colOffset + c * 3 + 1, 'S' | COLOR_PAIR(2));
}

void Renderer::drawEnd(int r, int c) {
    mvaddch(rowOffset + r * 2 + 1, colOffset + c * 3 + 1, 'E' | COLOR_PAIR(3));
}

void Renderer::drawBreadcrumbs(int r, int c) {
    mvaddch(rowOffset + r * 2 + 1, colOffset + c * 3 + 1, '.' | COLOR_PAIR(4));
}

void Renderer::drawStatus(int row, int mistakes, int timeLeft) {
    mvprintw(rowOffset + row, colOffset, "Mistakes: %d | Time: %02d:%02d",
    mistakes, timeLeft / 60, timeLeft % 60 );
    clrtoeol();
}

void Renderer::drawEscapePath(const Maze& maze) {
    const Path& path = maze.getEscapePath();
    if (path.empty()) return;
 
    init_pair(5, COLOR_BLUE, COLOR_BLUE);
    for (int i = 0; i < (int)path.size(); ++i) {
        const Cell& cell = path[i].get();
        int r = cell.getCellRow();
        int c = cell.getCellCol();
 
        attron(COLOR_PAIR(5));
        mvaddch(rowOffset + r * 2 + 1, colOffset + c * 3 + 1, ' ');
        attroff(COLOR_PAIR(5));
 
        if (i + 1 < (int)path.size()) {
            const Cell& next = path[i + 1].get();
            int nr = next.getCellRow();
            int nc = next.getCellCol();
 
            // Horizontal passage
            if (r == nr) {
                int passCol = (c < nc) ? c * 3 + 2 : nc * 3 + 2;
                attron(COLOR_PAIR(5));
                mvaddch(rowOffset + r * 2 + 1, colOffset + passCol, ' ');
                attroff(COLOR_PAIR(5));
            }
            // Vertical passage
            if (c == nc) {
                int passRow = (r < nr) ? r * 2 + 2 : nr * 2 + 2;
                attron(COLOR_PAIR(5));
                mvaddch(rowOffset + passRow, colOffset + c * 3 + 1, ' ');
                attroff(COLOR_PAIR(5));
            }
        }
 
        refresh();
        napms(50);
    }
    napms(750);
}