#pragma once

class Maze;
class Player;
class Renderer {
public:
    Renderer();
    ~Renderer();
    void drawMaze(const Maze& maze);
    void drawPlayer(int r, int c);
    void mazeRefresh();
    void drawStart(int r, int c);
    void drawEnd(int r, int c);
    void drawBreadcrumbs(const Player& player, const Maze& maze);
    void drawStatus(int row, int mistakes, int timeLeft);
};