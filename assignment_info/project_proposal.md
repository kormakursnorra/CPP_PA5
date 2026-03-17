# PA5 Project Proposal

## Maze Game with Pathfinding & Hint System

### 1. Project Description

We will build a terminal-based maze game in C++ where the player navigates a randomly generated
maze from a start point to an exit. Before the player takes control, the program runs Dijkstra's algorithm to compute the shortest path through the maze. During gameplay, the player can receive hints at points where they're struggling; the hint system uses the precomputed path to reveal the next correct step without giving away the entire solution. The game is displayed in the terminal using the ncurses library, which also handles real-time keyboard input (arrow keys) without requiring the player to press Enter.

### 2. Grading Items

#### 2.1 New Program with Similar Methods to Previous Assignments

What fulfils this item: The entire project is a new standalone C++ program using familiar concepts such as classes, data structures, file I/O (loading/saving maze configurations), and standard algorithms all applied in a new context.
*Estimated point value: 40-60 pts*

#### 2.2 Complex Decisions — Search Algorithm (Dijkstra's)

What fulfills this item: Dijkstra's shortest-path algorithm is run on the maze graph at generation time. The maze cells are treated as graph nodes, with edges existing only where there is no wall between two adjacent cells. The algorithm produces the optimal path used by the hint system.
*Estimated point value: 40 pts*

#### 2.3 Interface with I/O Device (Other than Text Terminal) — ncurses

What fulfils this item: The ncurses library provides real-time keyboard input capture (arrow keys, hint key) and full terminal screen rendering. This goes beyond standard stdin/stdout and qualifies as interfacing with an input/output device.
*Estimated point value: 20–40 pts*

#### 2.4 Third-Party Library Integration

What fulfills this item: ncurses is used for terminal UI and raw input. nlohmann/json may be used for saving and loading maze state. This satisfies the requirement to integrate a third-party library.
*Estimated point value: Required / implicit*

### 3. Estimated Point Value

| Version  | Features Included                                                                                          | Est. Points |
|----------|------------------------------------------------------------------------------------------------------------|-------------|
| Basic    | Random maze generation, player movement with keyboard, win/lose detection, basic terminal rendering        |     ~50     |
| Complete | Dijkstra's shortest path computed at generation, hint system, clean ncurses UI, move counter, timer        |     ~75     |
| Extra    | Multiple maze sizes/difficulties, animated hint path, replay optimal solution at end, save/load maze state |     ~100    |

### 4. Interesting Problems Expected

* **Maze Generation Algorithm:** We plan to use Recursive Backtracking (depth-first search) or Prim's algorithm to generate mazes with exactly one path between any two cells. Choosing and implementing this correctly requires careful handling of the cell/wall data structure.
* **Representing the Maze as a Graph:** Dijkstra's algorithm requires a graph. We must convert the 2D grid of cells and walls into an adjacency representation that the algorithm can traverse efficiently.
* **Hint System Logic:** The hint must only reveal the next step, not the full solution. We need to track the player's position against the precomputed optimal path, count
the number of mistakes made at some section and only give them a hint once the number of mistakes exceeds a limit.
* **ncurses Input Handling:** Capturing arrow keys in real time (non-blocking, no Enter required) and refreshing the screen without flicker requires understanding ncurses' input modes and refresh cycle.
* **Edge Case:** Player Deviates from Optimal Path: If the player moves away from the optimal path, the hint system must either re-run Dijkstra from the new position or go back to the precomputed path from the nearest node.

### 5. Data Structures, Algorithms & Calculations

* 2D grid / matrix for maze cell and wall representation
* Adjacency list or implicit graph derived from the maze grid for Dijkstra's
* Priority queue (min-heap via std::priority_queue) for Dijkstra's algorithm
* Recursive Backtracking / DFS stack for maze generation
* Path vector storing the optimal sequence of cells from start to exit

### 6. Third-Party Libraries

* **ncurses / PDCurses:** Terminal rendering and real-time keyboard input. This is the core library for our UI and I/O device requirement. Well-documented and widely available on Linux/macOS. PDCurses is the Windows equivalent.
* **nlohmann/json (optional):** Header-only JSON library for saving and loading maze configurations to/from disk. Would be used in the dream scenario save/load feature.
*Note:* We are confident in our library choices. If ncurses causes platform compatibility issues we may switch to FTXUI, a modern header-only C++ TUI library with similar capabilities.
