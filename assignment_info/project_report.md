# PA5 Project Report

## Maze game with pathfinding and a hint system

### 1. Project description
We have made a terminal-based maze game in C++ where the player navigates a randomly generated maze from a start point to an exit, and must reach the end before the alloted time is up. Before the player can start he must choose a difficulty level, the maze grid size and time alloted increases with added difficulty. The maze was generated using wilsons algorithim to generate a uniform maze?---------skoda. During the game, for every move the player makes a "breadcrumb" is left so the player can see where he has been. The players score depends on the time it took for the player to reach the exit and how many mistaks the player made (hitting a wall or straying of the shortest path). The game is displayed in the terminal using the ncurses library, which also handles real-time keyboard input (arrow keys) without requiring the player to press enter.

Gamla ->Our proposal is to build a terminal-based maze game in C++ where the player navigates a randomly generated maze from a start point to an exit. Before the player starts, the program runs Breath First Search to find the shortest path through the maze. During the game the player can receive hints at points where they're struggling; the hint system uses the precomputed path to reveal the next correct step. Throughout a round, the game keeps track of the number of mistakes the player makes. If the player manages to finish the maze, they receive a score based on the number of steps made in the wrong direction, if the player however is unable to clear the maze under the alloted time limit, he loses. The game is displayed in the terminal using the ncurses library, which also handles real-time keyboard input (arrow keys) without requiring the player to press enter.

### 2. Fulfilled proposal items

#### 2.1 Make entire new program with similar methods to some previous assignment

The project is a new standalone C++ program using known concepts such as classes, data structures, file I/O (loading/saving maze configurations), and standard algorithms that are being applied in a new context.
*points: 40-60*

#### 2.2 Make program take complex decisions

Wilson?????

Breath First Search is ran on the maze graph at generation time. The maze cells are treated as graph nodes, with edges existing only where there is no wall between two adjacent cells. The algorithm produces the shortest path which we used to compair how many steps from the shortest path the player took and use it in the calculation of the players score and to display the shortest path after the game has ended.
(by the hint system)-------
*points: 30* 

#### 2.3 Interface with input/output device

The ncurses library provides real-time keyboard input capturing (f.ex. arrow keys) and full terminal screen rendering. Going beyond the standard stdin/stdout and qualifies as interfacing with an input/output device.
*points: 20–40*

### 3. Additional implementation items

Hugmyndir:

#### 3.1 Time??

#### 3.2 Breadcrumb trail??

#### 3.3 Multiple difficulties??

#### 3.4 Animated/(Displaying the) maze generation and shortest path??

#### 3.5 Menu??


### 4. Problems encountered

### 5. Interesting solutions

### 6. Estimated total point value

| Version  | Features Included | Est. Points |
|----------|-------------------|-------------|
| Achieved |                   |             |