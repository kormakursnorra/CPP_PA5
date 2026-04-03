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

At the heart of the game is Wilsons Algorithm. Formally, it produces uniform spanning trees using loop-erased random walks. Perfect mazes are in eseence spanning trees, but unlike other algorithms such as Prims, Kruskals and DFS, that tend to create predictable patterns or biases, Wilsons manages to generate truly random, perfect mazes.

Breadth First Search is ran on the maze graph at generation time. The maze cells are treated as graph nodes, with edges existing only where there is no wall between two adjacent cells. The algorithm produces the shortest path which we used to compare how many steps from the shortest path the player took and use it in the calculation of the players score and to display the shortest path after the game has ended.
*points: 30*

#### 2.3 *Interface with input/output device*

The ncurses library provides real-time keyboard input capturing (f.ex. arrow keys) and full terminal screen rendering. Going beyond the standard stdin/stdout and qualifies as interfacing with an input/output device.
*points: 20–40*

### 3. Additional implementation

#### 3.1 Breadcrumb trail
As the player moves through the maze the previously visited cell is marked with "." leaving a trail. This lets the player see where they have already been and after the game has ended the player can compare their path against the displayed shortest path.
*points: 5*

#### 3.2 Multiple difficulties
The game has 4 difficulty levels (easy, medium, hard and no escape), each with a different maze size and time limit.
*points: 5*

#### 3.3 Animated maze generation and shortest path

We animated the maze generation in real time using ncurses, which shows how the Wilsons algorithm creates the maze. The shortest path is animated at the end of each game, then the player can see how close their path was from the shortest path.
*points: 10*

#### 3.4 Menu
We made a navigation menu with a main screen, a control screen and a difficulty selection screen, which allows the player to choose between them without restarting the program.
*points: 10-15*


### 4. Problems Encountered and Interesting Solutions

#### *Problem 1.*

When diplaying the maze and the player movement we had issues where the maze rendering would flicker since it was redrawing the whole maze for every update.

We overcame this by only redrawing the walls of the current cell Wilsons algorithm is effecting. And for the player movement, we made it so that it only redraws the current- and previous cell he had visited.

#### *Problem 2.*

Another problem we faced had to do with displaying the cell and the player character simultaneously. Due to the differing scaling sizes of the player character and the horizontal- and vertical wall characters, we were unable to render the two a fixed size.

To solve this, we had to upscale every cell on rendering to accomodate for the scaling inbalance. This however wasn't enough, since the size of the horizontal- and vertical walls also differed, we needed to apply different scaling constants to them as well.

#### *Problem 3.*

Despite mazes being functionally identical to graphs, we still ran into some issues when it came to applying BFS on the grid structure. Where the traditional graph and our maze structure diverge is in the implementation of the edges.

While the traditional approach makes use of adjency lists/matrixes to store a graph's edges, we implicitly defined the edges by setting each directional wall of each `Cell` instance to `true` or `false` (has a wall in some direction and does not have a wall in some direction respectively).

So the problem at hand was figuring out how to adjust the algorithm to our specific structure.

The solution we came up with entailed, for each cell, instead of checking it's adjacent cells through the use of adjacency lists, iterating through the four directions available to it (north, south, east, west) and checking if:

1. the cell has a wall at the current direction being checked and
2. if the next cell accessible to it is within the bounds of the grid.

Although, especially in retrospect, this proved to be more of a minor obstacle rather than a major one, it still required careful though and consideration to implement correctly.

### 5. Interesting Solutions

### 6. Estimated total point value

| Version  | Features Included | Est. Points |
|----------|-------------------|-------------|
| Achieved |                   |             |