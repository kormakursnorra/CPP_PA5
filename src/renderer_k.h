// #pragma once
#ifndef RENDERED_K_H
#define RENDERED_K_H

#include "maze_k.h"

class Renderer {
public:
    Renderer();
    ~Renderer();
    void drawMaze(const Maze& maze);
    void drawPlayer(int r, int c);
    void mazeRefresh();
};

#endif