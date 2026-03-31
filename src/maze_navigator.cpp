#include <vector>
#include <algorithm>
#include <functional>

#include "cell_k.h"
#include "maze_k.h"
#include "maze_navigator.h"

// const Cell& start    = maze.getCell(0, 0);
// const Cell& exit     = maze.getCell(maze.getCols() - 1, maze.getRows() -1);
// const MazeGrid& grid = maze.getGrid();

MazeNavigator::MazeNavigator(const Maze& maze) : maze(maze) {}

void MazeNavigator::findEscapePath(const Cell& startCell, const Cell& exitCell) {
    std::queue<std::reference_wrapper<const Cell>> queue;             
    int numCells = maze.getNumCells();
    bool visited[maze.getNumCells()];
    for (int i = 0; i < numCells; ++i) {
        visited[i] = false;
    }
    
    visited[startCell.getPos()] = true;
    escapePath.push_back(startCell);
    queue.push(startCell);
    
    int cols = maze.getCols();
    int rows = maze.getRows();

    while (!queue.empty()) {
        const Cell& currCell = queue.front();
        queue.pop();
        
        if (currCell.getPos() == exitCell.getPos()) return;
       
        for (int i = 0; i < 4; ++i) {
            if (currCell.walls.north && i == 0) continue;
            if (currCell.walls.south && i == 1) continue;
            if (currCell.walls.east && i == 2) continue;                
            if (currCell.walls.west && i == 3) continue;
            
            int nextY = currCell.getY() + directions[i][0];
            int nextX = currCell.getX() + directions[i][1];
            
            if (0 <= nextY && nextY < rows && 0 <= nextX && nextX < cols) {
                int nextPos         = nextX + nextY;
                const Cell nextCell = maze.getCell(nextX, nextY);

                if (!visited[nextPos]) {
                    visited[nextCell.getPos()] = true;
                    escapePath.push_back(nextCell);
                    queue.push(nextCell);
                }
            }
        }
    }
    std::reverse(escapePath.begin(), escapePath.end());
}

void MazeNavigator::findRetracePaths(const Path& escapePath, const ) {
    const MazeGrid& grid = maze.getGrid();
    
    for (int y = maze.getRows() - 1; y > 0; ++y) {
        for (int x = maze.getCols() - 1; x > 0; ++x) {
            const Cell& cell = maze.getCell(x, y);

        }
    }
}