#include "menu.h"
#include <vector>
#include <string>


void Menu::drawTitle(int startRow) {
    const std::string title = "MAZE ESCAPE";
    int maxX = getmaxx(stdscr);
    int col = (maxX - (int)title.size()) / 2;
    attron(A_BOLD | COLOR_PAIR(3));
    mvprintw(startRow, col, "%s", title.c_str());
    attroff(A_BOLD | COLOR_PAIR(3));
}

void Menu::drawSeparator(int row, int width) {
    int maxX = getmaxx(stdscr);
    int col  = (maxX - width) / 2;
    attron(COLOR_PAIR(6));
    for (int i = 0; i < width; ++i) {
        mvaddch(row, col + i, ACS_HLINE);
    }
    attroff(COLOR_PAIR(6));
}

void Menu::showMain(MenuResult &result) {
    const std::vector<std::string> options = {"Play", "Controls", "Quit"};
    int maxX = getmaxx(stdscr);
    int maxY = getmaxy(stdscr);
    int sepWidth = 20;

    int titleRow = maxY / 2 - 4;
    int sepRow   = titleRow + 2;
    int menuRow  = sepRow + 2;

    int selected = 0;
    timeout(-1);

    while (true) {
        clear();
        drawTitle(titleRow);
        drawSeparator(sepRow, sepWidth);

        for (int i = 0; i < (int)options.size(); ++i) {
            int col = (maxX - (int)options[i].size()) / 2;
            if (i == selected) {
                attron(A_REVERSE | A_BOLD);
                mvprintw(menuRow + i * 2, col, "%s", options[i].c_str());
                attroff(A_REVERSE | A_BOLD);
            } else {
                mvprintw(menuRow + i * 2, col, "%s", options[i].c_str());
            }
        }

        mvprintw(maxY - 2, 0, "UP/DOWN: Navigate   ENTER: Select");
        refresh();
        flushinp();
        int ch = getch();
        if (ch == KEY_UP)   selected = (selected - 1 + (int)options.size()) % (int)options.size();
        if (ch == KEY_DOWN) selected = (selected + 1) % (int)options.size();
        if (ch == '\n' || ch == KEY_ENTER || ch == ' ') {
            if (selected == 0) { result = MenuResult::PLAY; return; }
            if (selected == 1) { result = MenuResult::CONTROLS; return; }
            if (selected == 2) { result = MenuResult::QUIT; return; } 
        }
        if (ch == 'q') { result = MenuResult::QUIT; return; }
    }
}


void Menu::showDifficulty(Difficulty &diff, MenuResult &result) {
    struct Option { std::string label; std::string desc; Difficulty diff; };
    const std::vector<Option> options = {
        {"Easy",      "10x10  |  1:00",  Difficulty::EASY},
        {"Medium",    "15x15  |  1:30",  Difficulty::MEDIUM},
        {"Hard",      "25x25  |  2:00",  Difficulty::HARD},
        {"No Escape", "30x30  |  3:00",  Difficulty::NO_ESCAPE},
    };

    int maxX = getmaxx(stdscr);
    int maxY = getmaxy(stdscr);
    int sepWidth = 24;

    int titleRow = maxY / 2 - 6;
    int sepRow   = titleRow + 2;
    int menuRow  = sepRow + 2;

    int selected = 0;
    timeout(-1);

    while (true) {
        clear();
        drawTitle(titleRow);
        drawSeparator(sepRow, sepWidth);

        std::string sub = "Select Difficulty";
        mvprintw(sepRow - 1, (maxX - (int)sub.size()) / 2, "%s", sub.c_str());

        for (int i = 0; i < (int)options.size(); ++i) {
            std::string line = options[i].label + "   " + options[i].desc;
            int col = (maxX - (int)line.size()) / 2;
            if (i == selected) {
                attron(A_REVERSE | A_BOLD);
                mvprintw(menuRow + i * 2, col, "%s", line.c_str());
                attroff(A_REVERSE | A_BOLD);
            } else {
                mvprintw(menuRow + i * 2, col, "%s", line.c_str());
            }
        }

        mvprintw(maxY - 2, 0, "UP/DOWN: Navigate   ENTER: Select   b: Back   q: Quit");
        refresh();
        flushinp();
        int ch = getch();
        if (ch == KEY_UP)   selected = (selected - 1 + (int)options.size()) % (int)options.size();
        if (ch == KEY_DOWN) selected = (selected + 1) % (int)options.size();
        if (ch == '\n' || ch == KEY_ENTER || ch == ' ') { diff = options[selected].diff; return; }
        if (ch == 'b') { result = MenuResult::BACK; return; }
        if (ch == 'q') { result = MenuResult::QUIT; return; }
    }
}


void Menu::showControls() {
    int maxX = getmaxx(stdscr);
    int maxY = getmaxy(stdscr);

    clear();
    drawTitle(maxY / 2 - 8);
    drawSeparator(maxY / 2 - 6, 24);

    const std::vector<std::string> lines = {
        "Arrow Keys   Move player",
        "q            Quit game",
        "",
        "Reach the EXIT before time runs out!",
        "Avoid walls to keep mistakes low.",
        "",
        "Difficulty affects maze size and time.",
    };

    int startRow = maxY / 2 - 4;
    for (int i = 0; i < (int)lines.size(); ++i) {
        mvprintw(startRow + i, (maxX - 40) / 2, "%s", lines[i].c_str());
    }

    mvprintw(maxY - 2, 0, "Press any key to go back...");
    refresh();
    timeout(-1);
    flushinp();
    getch();
}