#include "maze_k.h"
#include <cassert>
#include <math.h>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int width = 32;
    int height = 32;
    
    if (argc == 3) {
        int tmp_w = atoi(argv[1]);
        int tmp_h = atoi(argv[2]);

        int lg_width = (int)log2(tmp_w);
        int lg_height = (int)log2(tmp_h);

        if (lg_width % 2 == 0) width = tmp_w;
        else width = 1U << (int)(
            log2(tmp_w - 1) + 1);
        
        if (lg_height % 2 == 0) height = tmp_h;
        else height = 1U << (int)(
            log2(tmp_h - 1) + 1);
    }

    assert(width % 2 == 0 && height % 2 == 0);
    Maze maze(width, height);
    maze.generateMaze();
    return 0;
}