#pragma once
#include "maze.h"
#include "ncurses.h"
#include "player_k.h"
#include "renderer_k.h"

class Renderer {
private:
    int rowOffset = 0;
    int colOffset = 0;

public:
    Renderer();
    ~Renderer();
    void computeOffsets(const Maze& maze);
    void drawMaze(const Maze& maze);
    void drawPlayer(int r, int c);
    void mazeRefresh();
    void drawStart(int r, int c);
    void drawEnd(int r, int c);
    void drawBreadcrumbs(const Player& player, const Maze& maze);
    void drawStatus(int row, int mistakes, int timeLeft);
    void drawEscapePath(const Maze& maze);
};