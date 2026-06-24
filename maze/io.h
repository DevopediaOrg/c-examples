#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "maze.h"

// ------------------------------------------
// File Input
// ------------------------------------------
/**
 * @brief Reads the raw ASCII layout from a file and initializes the Maze metadata.
 *
 * Opens the specified file, determines dimensions, allocates maze memories, 
 * and copies the textual lines into the `lines` buffer of the struct.
 *
 * @param[in,out] maze     Pointer to the Maze struct to populate.
 * @param[in]     filename Path to the text file containing the ASCII maze.
 */
void read_maze_from_file(Maze *maze, char *filename);

/**
 * @brief Parses the ASCII maze lines and encodes them into the bitmask representation.
 *
 * Iterates through the text character positions to identify wall configurations 
 * (North, East, South, West) and fills the flat dynamic grid `m`.
 *
 * @param[in,out] maze Pointer to the Maze struct containing the text to be processed.
 */
void encode_maze(Maze *maze);

// ------------------------------------------
// Terminal Output
// ------------------------------------------
/**
 * @brief Prints the raw numeric bitmask values of the encoded maze matrix.
 *
 * Displays the hexadecimal bytes stored in `maze->m` as a formatted grid 
 * for debugging purposes.
 *
 * @param[in] maze Pointer to the Maze struct to display.
 */
void print_encoded_maze(Maze *maze);

/**
 * @brief Prints the visual ASCII representation of the maze, overlaying a path if provided.
 *
 * Reconstructs the wall boundaries graphically in the console. If a solved path 
 * exists, it marks the visited cells with an asterisk (`*`).
 *
 * @param[in] maze Pointer to the Maze struct containing wall data.
 * @param[in] path Pointer to the Path struct holding coordinates to overlay (can be NULL).
 */
void print_maze(Maze *maze, Path *path);

#endif // IO_H
