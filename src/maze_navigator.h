#ifndef MAZE_NAVIGATOR
#define MAZE_NAVIGATOR

#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <vector>
#include "cell_k.h"
#include "maze_k.h"

using Path = std::vector<std::reference_wrapper<const Cell>>;

class MazeNavigator {
private:
    const Maze maze;
    Path escapePath;
    std::map<Cell*, Path> retracePaths;
    const int directions[4][2] = {
        {0, 1}, {1, 0}, 
        {0, -1}, {-1, 0}
    };

    void findEscapePath(const Cell& startCell, const Cell& exitCell);
    void findRetracePaths(const Path& escapePath, const Maze& maze);
    
public:
    MazeNavigator(const Maze& maze);
    Path getEscapePath() const { return escapePath; }
    Path getRetracePath(Cell& cell) const { return retracePaths.at(&cell); }
};

#endif