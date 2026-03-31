#pragma once

class Maze;
class Renderer {
public:
    Renderer();
    ~Renderer();
    void drawMaze(const Maze& maze);
    void drawPlayer(int r, int c);
    void mazeRefresh();
};