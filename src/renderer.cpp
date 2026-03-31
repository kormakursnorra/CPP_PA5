#include "renderer.h"
#include "maze.h"
#include "ncurses.h"

Renderer::Renderer() {
    initscr();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK); // player
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // start marker
    init_pair(3, COLOR_RED, COLOR_BLACK); // exit marker
    init_pair(4, COLOR_YELLOW, COLOR_BLACK); // status bar
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK); // breadcrumbs
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
}

Renderer::~Renderer() {
    endwin();
}

void Renderer::drawMaze(const Maze& maze) {
    for (int r = 0; r < maze.getRows(); r++) {
        for (int c = 0; c < maze.getCols(); c++) {
            const Cell& cell = maze.getCell(r,c);
            int sr = r * 2; // screen row
            int sc = c * 3; // screen col

            mvaddch(sr, sc, '+');

            if (cell.north) {
                mvaddch(sr, sc + 1, '-');
                mvaddch(sr, sc + 2, '-');
            } else {
                mvaddch(sr, sc + 1, ' ');
            }

            if (cell.west) {
                mvaddch(sr + 1, sc, '|');
            } else {
                mvaddch(sr + 1, sc, ' ');
            }

            mvaddch(sr + 1, sc + 1, ' ');
        }   
    }
    // draw right border
    for (int r = 0; r < maze.getRows(); r++) {
        int sr = r * 2;
        int sc = maze.getCols() * 3; // onse step past the last column
        mvaddch(sr, sc, '+');
        mvaddch(sr + 1, sc, '|');
    }

    // draw bottom border
    for (int c = 0; c < maze.getCols(); c++) {
        int sr = maze.getRows() * 2; // one step past the last row
        int sc = c * 3;
        mvaddch(sr, sc, '+');
        mvaddch(sr, sc + 1, '-');
        mvaddch(sr, sc + 2, '-');
    }

    mvaddch(maze.getRows() * 2, maze.getCols() * 3, '+');
}

void Renderer::drawPlayer(int r, int c) {
    mvaddch(r * 2 + 1, c * 3 + 1, '@' | COLOR_PAIR(1));
}

void Renderer::mazeRefresh() {
    refresh();
}