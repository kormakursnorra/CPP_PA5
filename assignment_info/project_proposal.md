# PA5 Project Proposal

## Maze game with pathfinding and a hint system

### 1. Project description

Our proposal is to build a terminal-based maze game in C++ where the player navigates a randomly generated maze from a start point to an exit. Before the player starts, the program runs Breath First Search to find the shortest path through the maze. During the game the player can receive hints at points where they're struggling; the hint system uses the precomputed path to reveal the next correct step. Throughout a round, the game keeps track of the number of mistakes the player makes. If the player manages to finish the maze, they receive a score based on the number of steps made in the wrong direction, if the player however is unable to clear the maze under the alloted time limit, he loses. The game is displayed in the terminal using the ncurses library, which also handles real-time keyboard input (arrow keys) without requiring the player to press enter.

### 2. What will be fulfilled

#### 2.1 Make entire new program with similar methods to some previous assignment

The project is a new standalone C++ program using known concepts such as classes, data structures, file I/O (loading/saving maze configurations), and standard algorithms that are being applied in a new context.
*points: 40-60*

#### 2.2 Make program take complex decisions

Breath First Search is ran on the maze graph at generation time. The maze cells are treated as graph nodes, with edges existing only where there is no wall between two adjacent cells. The algorithm produces the optimal path used by the hint system and in the calculation of the players score.
*points: 40*

#### 2.3 Interface with input/output device

The ncurses library provides real-time keyboard input capturing (f.ex. arrow keys) and full terminal screen rendering. Going beyond the standard stdin/stdout and qualifies as interfacing with an input/output device.
*points: 20–40*

### 3. Interesting problems expected

* **Maze generation algorithm:** We plan to use Recursive Backtracking (depth-first search) or Prim's algorithm to generate mazes with exactly one path between any two cells. Choosing and implementing this correctly will require careful handling of the cell/wall data structure.
* **Representing the maze as a graph:** BFS algorithm requires a graph. We must convert the 2D grid of cells and walls into an adjacency representation that the algorithm can traverse efficiently.
* **Hint system logic:** The hint must only reveal the next step, not the full solution. We need to track the player's position against the precomputed optimal path, count the number of mistakes made at some section and only give them a hint once the number of mistakes exceeds a limit.
* **ncurses input handling:** Capturing arrow keys in real time (non-blocking, no enter required) and refreshing the screen without flicker requires understanding ncurses input modes and refresh cycle.
* **Edge case:** Player deviates from the optimal path: If the player moves away from the optimal path, the hint system must either re-run BFS from the new position or go back to the precomputed path from the nearest node.

### 4. Data structures, algorithms and calculations

* 2D grid / matrix for maze cell and wall representation.
* Adjacency list or implicit graph from the maze grid for BFS.
* Queue and vector for BFS.
* Recursive Backtracking / DFS stack for the maze generation.
* Path vector storing the optimal sequence of cells from start to exit.

### 5. Libraries

* **ncurses / PDCurses:** We plan to use ncurses for terminal rendering and real-time keyboard input. This is the core library for our UI and I/O device requirement. Which is well-documented and widely available on Linux/macOS. PDCurses is the Windows equivalent.
* **nlohmann/json (optional):** Header-only JSON library for saving and loading maze configurations to and from the disk. Would be used in the dream scenario save/load feature.


### 6. Estimated point value

| Version  | Features Included                                                                                          | Est. Points |
|----------|------------------------------------------------------------------------------------------------------------|-------------|
| Basic    | Random maze generation, player movement with keyboard, win/lose detection, basic terminal rendering        |     ~50     |
| Complete | BFS shortest path computed at generation, hint system, clean ncurses UI, move counter, timer               |     ~75     |
| Extra    | Multiple maze sizes/difficulties, animated hint path, replay optimal solution at end, save/load maze state |     ~100    |
