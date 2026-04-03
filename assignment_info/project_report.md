# PA5 Project Report

## Maze Escape Game

### 1. Project Description

We've developed a terminal-based maze game in C++ where the player has to navigate a randomly generated, perfect maze to reach the exit before the alloted time is up. Before stepping into the maze, the player must choose a difficulty level (Easy, Medium, Hard, No Escape) that determines the size of the maze and the time limit given to him. Throughout the duration of the game, "breadcrumbs" are left behind the player as he navigates through the maze; letting him easily trace back to previous positions.  

Upon completition, regardless if the player managed to escape or not, the game renders the singular escape path to the player. If the player manages to escape the maze, he receives a completition score that is dependant on the time it took for him to reach the exit and the amount of mistaks he made such as hitting a wall or straying of the shortest path.

The game is displayed in the terminal using the ncurses library, which also handles real-time keyboard input (arrow keys) without requiring the player to press enter.

### 2. Fulfilled Proposal Items

#### 2.1 *Make entire new program with similar methods to some previous assignment*

The project is a new standalone C++ program using known concepts such as classes, data structures, file I/O (loading/saving maze configurations), and standard algorithms that are being applied in a new context.
*points: 40-60*

#### 2.2 *Make program take complex decisions*

At the heart of the game is Wilson's Algorithm. Formally, it produces uniform spanning trees using loop-erased random walks. Perfect mazes are in eseence spanning trees, but unlike other algorithms such as Prim's, Kruskal's and DFS, that tend to create predictable patterns or biases, Wilson's manages to generate truly random, perfect mazes.

Breadth First Search is ran on the maze graph at generation time. The maze cells are treated as graph nodes, with edges existing only where there is no wall between two adjacent cells. The algorithm produces the shortest path which we used to compare how many steps from the shortest path the player took and use it in the calculation of the players score and to display the shortest path after the game has ended.
*points: 30*

#### 2.3 *Interface with input/output device*

The ncurses library provides real-time keyboard input capturing (f.ex. arrow keys) and full terminal screen rendering. Going beyond the standard stdin/stdout and qualifies as interfacing with an input/output device.
*points: 20–40*

### 3. Additional implementation items

Hugmyndir:
#### 3.1 Breadcrumb trail
As the player moves through the maze the previously visited cell is marked with "." leaving a trail. This lets the player see where they have already been and after the game has ended the player can compare their path against the displayed shortest path.

#### 3.2 Multiple difficulties
The game has 4 difficulty levels (easy, medium, hard and no escape), each with a different maze size and time limit.

#### 3.3 Animated maze generation and shortest path

#### 3.4 Menu


### 4. Problems encountered
When diplaying the maze and playermovement we had issues where the maze would flicker since it was redrawing the whole maze for every update. We fixed this by only redrawing the cells that were being changed, so for the maze generation its only redrawing the current cell wilsons algorithm is effecting and redraws the walls for that cell, and for the player it only redraws the current cell and the one he was previously on.

Another problem we had was with the cell since we could not display the walls and the player at the same time so we had to scale each cell upp to take up multiple characters on screen.

### 5. Interesting solutions

### 6. Estimated total point value

| Version  | Features Included | Est. Points |
|----------|-------------------|-------------|
| Achieved |                   |             |