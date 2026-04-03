#pragma once

#include <string>
#include <ncurses.h>

enum class MenuResult { PLAY, QUIT, CONTROLS, BACK };

enum class Difficulty { EASY, MEDIUM, HARD, NO_ESCAPE };
struct DifficultyConfig {
    int rows;
    int cols;
    int timeLimit;
};

class Menu {
private:
    void drawTitle(int startRow);
    void drawSeparator(int row, int width);

public:
    void showMain(MenuResult &result);
    void showDifficulty(Difficulty &diff, MenuResult &result);
    void showControls();

};
