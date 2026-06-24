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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 0


/*--------------------------------------
Type definitions
----------------------------------------*/
typedef enum direction {
    North = 1,
    East = 2,
    South = 4,
    West = 8
} Direction;

typedef struct cell {
    int x;
    int y;
} Cell;

typedef struct maze {
    int num_rows;
    int num_cols;
    char **lines; // as stored in file
    char *m; // as encoded in memory
} Maze;

typedef struct path {
    bool found_path;
    int num_steps; // indexes into path[]
    Cell *cells;
} Path;


/*--------------------------------------
Functions
----------------------------------------*/
int get_num_cols(FILE *fp) {
    int num_corners = 0;

    int ch; // fgetc() returns int and EOF is int
    while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
        if (ch == '+') num_corners++;
    }

    // Reset fp to start
    fseek(fp, 0, SEEK_SET);

    return num_corners - 1;
}

int get_num_rows(FILE *fp) {
    int num_lines = 0;

    char line[100]; // an arbitrary limit
    while (fgets(line, 100, fp) != NULL) {
        num_lines++;
    }

    // Reset fp to start
    fseek(fp, 0, SEEK_SET);

    return (num_lines - 1) / 2;
}

void read_maze_from_file(Maze *maze, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: unable to open maze file %s. Quitting...\n", filename);
        exit(1);
    }

    maze->num_cols = get_num_cols(fp);
    maze->num_rows = get_num_rows(fp);

    int total_lines = 2 * (maze->num_rows) + 1;
    int max_line_len = 4 * (maze->num_cols) + 3; // 4 chars per cell + 1 for boundary + '\n' + '\0'

    maze->lines = malloc(total_lines * sizeof(char *));
    for (int i = 0; i < total_lines; i++) {
        maze->lines[i] = malloc((max_line_len) * sizeof(char));
        if (fgets(maze->lines[i], max_line_len, fp) == NULL) {
            maze->lines[i][0] = '\0';
        }
    }

    fclose(fp);
}

void encode_maze(Maze *maze) {
    maze->m = calloc(maze->num_rows * maze->num_cols, sizeof(char));
    char (*m)[maze->num_cols] = (char (*)[maze->num_cols])maze->m;

    for (int r = 0; r < maze->num_rows; r++) {
        for (int c = 0; c < maze->num_cols; c++) {
            char cell_val = 0;

            if (maze->lines[2 * r][4 * c + 1] == '-') {
                cell_val |= North;
            }
            if (maze->lines[2 * r + 1][4 * c + 4] == '|') {
                cell_val |= East;
            }
            if (maze->lines[2 * r + 2][4 * c + 1] == '-') {
                cell_val |= South;
            }
            if (maze->lines[2 * r + 1][4 * c] == '|') {
                cell_val |= West;
            }

            m[r][c] = cell_val;
        }
    }
}

void free_maze(Maze *maze) {
    int total_lines = 2 * (maze->num_rows) + 1;
    for (int i = 0; i < total_lines; i++) {
        free(maze->lines[i]);
    }
    free(maze->lines);

    free(maze->m);
}

void print_encoded_maze(Maze *maze) {
    for (int i = 0; i < maze->num_rows; i++) {
        for (int j = 0; j < maze->num_cols; j++) {
            printf("0x%02X", (unsigned char)maze->m[i*maze->num_cols + j]);
            if (j == maze->num_cols-1) printf("\n");
            else printf(" ");
        }
    }
}

bool is_on_path(int r, int c, Path *path) {
    if (path == NULL) return false;
    for (int i = 0; i < path->num_steps; i++) {
        if (path->cells[i].x == r && path->cells[i].y == c) {
            return true;
        }
    }
    return false;
}

void print_maze(Maze *maze, Path *path) {
    char (*m)[maze->num_cols] = (char (*)[maze->num_cols])maze->m;

    for (int r = 0; r < maze->num_rows; r++) {
        
        // --- 1. Print the North Walls Row ---
        for (int c = 0; c < maze->num_cols; c++) {
            printf("+");
            if (m[r][c] & North) {
                printf("---");
            } else {
                printf("   ");
            }
        }
        // Caps off the right side of the North boundary row
        printf("+\n");

        // --- 2. Print the Cell Middle Row (West wall, Space/*, East wall) ---
        for (int c = 0; c < maze->num_cols; c++) {
            // Print the West wall of the cell
            if (m[r][c] & West) {
                printf("|");
            } else {
                printf(" ");
            }

            // Print the cell interior center (Path marker '*' or empty space)
            if (is_on_path(r, c, path)) {
                printf(" * ");
            } else {
                printf("   ");
            }
        }
        // Caps off the very last East wall of the current row
        if (m[r][maze->num_cols - 1] & East) {
            printf("|\n");
        } else {
            printf(" \n");
        }
    }

    // --- 3. Print the Final South Wall Row ---
    // The bottom-most outer border needs to be closed out cleanly
    for (int c = 0; c < maze->num_cols; c++) {
        printf("+");
        if (m[maze->num_rows - 1][c] & South) {
            printf("---");
        } else {
            printf("   ");
        }
    }
    printf("+\n");
}

Cell* explore(int x, int y, Direction in, Maze *maze, Path *path, int path_idx) {
    Direction dirs[] = {North, East, South, West};
    int num_dirs = sizeof(dirs) / sizeof(dirs[0]);

    #if DEBUG
    printf("explore(%d, %d, %d, %d)\n", x, y, in, path_idx);
    #endif

    // Skip if indices are out of bounds
    if (x < 0 || x >= maze->num_rows || y < 0 || y >= maze->num_cols) return NULL;

    if (x == maze->num_rows-1 && y == maze->num_cols-1) {
        // We have reached the bottom-right cell: Success!
        path->found_path = 1;
        path->num_steps = path_idx + 1;
        path->cells[path_idx].x = x;
        path->cells[path_idx].y = y;
        return path->cells + path_idx;
    }

    Cell *next = NULL;
    for (int i = 0; i < num_dirs; i++) {
        // Don't explore the way we came in
        if (dirs[i] == in) continue;

        // Bit-wise operation non-zero implies a wall
        if ((maze->m[x*maze->num_cols + y] & dirs[i])) continue;

        switch (dirs[i]) {
            case North:
                next = explore(x-1, y, South, maze, path, path_idx+1);
                break;
            case East:
                next = explore(x, y+1, West, maze, path, path_idx+1);
                break;
            case South:
                next = explore(x+1, y, North, maze, path, path_idx+1);
                break;
            case West:
                next = explore(x, y-1, East, maze, path, path_idx+1);
                break;
        }

        // If found a path, don't search in other directions
        if (path->found_path) break;
    }

    if (next) {
        // Found a path
        path->cells[path_idx].x = x;
        path->cells[path_idx].y = y;
        return path->cells + path_idx;
    }

    return NULL;
}

void solve_maze(Maze *maze) {
    Path path;
    path.found_path = false;
    path.cells = malloc(maze->num_rows * maze->num_cols * sizeof(Cell));

    explore(0, 0, West, maze, &path, 0);
    printf("Found maze path of %d steps: ", path.num_steps);
    for (int i = 0; i < path.num_steps; i++) {
        printf("(%d, %d) ", path.cells[i].x, path.cells[i].y);
    }
    printf("\n\n");
    print_maze(maze, &path);

    free(path.cells);
}


/*--------------------------------------
Main processing
----------------------------------------*/
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