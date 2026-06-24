/*
This program is a maze solver. It reads a square maze
from an input text file. It figures out the maze size
from the input.

If maze is N x N, each cell is represented by a char.
The four LSB of this char indicate the North (bit 0),
East (bit 1), South (bit 2) and West (bit 3)
boundaries. Bit value 1 implies a wall. Bit 0 implies
an open path. For example, 0x0A (1010) implies walls
on the West and East boundaries of the cell. We give
five examples below:
+---+     +---+     +   +     +   +     +---+
          |         |   |         |     |   
+---+     +---+     +   +     +---+     +   +
0x05      0x0D      0x0A      0x06      0x09

The algorithm is a depth-first search. Maze is
entered at the top-left corner from the West. Maze
exit at the bottom-right corner to the East. If
there are multiple solution paths, only one is found
and not necessarily the shortest one.

The following are the objectives:
- Print the full found path
- Print the number steps in the found path
- Print the total number of steps taken TODO
*/

#include "maze.h"
#include "io.h"
#include "solver.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: expecting the maze filename to process. Quitting...\n");
        return 1;
    }

    Maze maze;
    read_maze_from_file(&maze, argv[1]);
    encode_maze(&maze);
    
    solve_maze(&maze);
    free_maze(&maze);

    return 0;
}