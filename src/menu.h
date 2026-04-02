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

inline DifficultyConfig getDifficultyConfig(Difficulty d) {
    switch (d) {
        case Difficulty::EASY:      return {10, 10, 60};
        case Difficulty::MEDIUM:    return {15, 15, 90};
        case Difficulty::HARD:      return {25, 25, 120};
        case Difficulty::NO_ESCAPE: return {30, 30, 180};
    }
    return {10, 10, 60};
}

class Menu {
private:
    void drawTitle(int startRow);
    void drawSeparator(int row, int width);

public:
    void showMain(MenuResult &result);
    void showDifficulty(Difficulty &diff, MenuResult &result);
    void showControls();

};
