#pragma once

#include <string>
#include <ncurses.h>


enum class MenuResult { PLAY, QUIT, CONTROLS };
 
enum class Difficulty { EASY, MEDIUM, HARD, NO_ESCAPE };
 
struct DifficultyConfig {
    int rows;
    int cols;
    int timeLimit;
};

inline DifficultyConfig getDifficultyConfig(Difficulty d) {
    switch (d) {
        case Difficulty::EASY:      return {10, 10, 5};
        case Difficulty::MEDIUM:    return {15, 10, 90};
        case Difficulty::HARD:      return {25, 10, 120};
        case Difficulty::NO_ESCAPE: return {30, 10, 180};
    }
    return {10, 10, 60};
}

class Menu {
private:
    void drawTitle(int startRow);
    void drawSeparator(int row, int width);

public:
    MenuResult showMain();
    Difficulty showDifficulty();
    void showControls();

};