## Overview

This repo includes a set of examples for beginners to learn C. Each folder can be considered as separate project, that is, it has its own `main()` function. Hence, C files within a folder (and those in its sub-folders) have to be compiled and linked together.

These C concepts can be studied in the following programs:
* Pass by reference: `average`, `noduplicates`, `reverse`, `swap`
* `enum`: `bmp2ascii`, `euler19`, `maze`
* `struct`: `bmp2ascii`, `distance`, `maze`, `rgb`
* File IO: `bmp2ascii`, `euler13`, `maze`
* Arguments to `main()`: `bmp2ascii`, `maze`, `temperature`, `timediff`
* Function return: `average`, `distance`, `maxstr`
* `sscanf`: `rgb`, `timediff`
* `sprintf`: `euler40`
* `for` loops and `printf`: `shapes`
* Treating large numbers as strings: `euler13`
* Data handling: `students`

`bmp2ascii` is an example of how to deal with images, saving them in memory as an array of pixel data. This program is also an introduction to BMP file format and ASCII art.

`bsearch` illustrates the difference between linear and binary search. It also shows how to use a pointer to a function.

`maze` shows how to organize a program into multiple C header and source files. It also shows the use of documentation comments, which can help is correctly using and maintaining user-written functions.

`mcpi` introduces Monte Carlo simulation and how to make use of randomness.

`snake` is an example of a user-interactive game that can be played on a Windows terminal. It also illustrates the use of emojis, multi-byte symbols and UTF-8 encoding.


## More Exercises
Here are some exercises that a student can attempt (not in any particular order):
- Conway's Game of Life
- Random Walk
- Vigenère cipher
- Any card game
- Sudoku solver
- Tetris
- Huffman coding
- Markdown to HTML converter
- C code formatter
- Basic calculator
- Web API call
- Replay a game of chess
- Balance an AVL tree
- Implement FIFO (queue) and LIFO (stack) using linked lists


## Project Euler
In this repo, we solve some problems from Project Euler. For reference, answers are available at https://github.com/lucky-bai/projecteuler-solutions/blob/master/Solutions.md


## Quizzes
1. Set 1: https://gist.github.com/arvindpdmn/50ee9e084806aa518f80efb9edf3f9fe
2. Set 2: https://gist.github.com/arvindpdmn/81a597bada7ad152f2d7ebb2ec3e6223


## C Concepts
These are some essentials concepts that a beginner has to learn.
- Data types
    - char, short, int, long long, float, double
    - unsigned char, unsigned short, unsigned int, unsigned long long
- Size and range of values of each data type
- Number systems: binary, decimal, hexadecimal
- ASCII encoding: https://www.ascii-code.com/
- Comments: single line and multi-line
- Constants and variables
- Initialization of variables
- Arrays and their initialization
- Declaration versus definition
- Operators
    - arithmetic: + - * / % ++ --
    - comparison: == != >= <= > < 
    - logical: && || !
    - bitwise: & | ^ ~ << >>
    - assignment: = += -= *= /= %= &= |= ^= <<= >>=
    - ternary: (? :)
    - pointers: & *
    - struct: . ->
    - operator precedence
- Scope: local, global, static
- Preprocessor directives: includes, macros, conditionals
- Naming conventions: variables, functions
- Branching: if, else if, else
- Loops
    - for, do-while, while
    - break, continue
- Basic programming pitfalls
    - Using a variable without initializing it
    - Copying or writing data beyond array boundary
    - Ignoring or overwriting the string-terminating '\0' character
    - Ignoring the signed or unsigned nature of the data type
    - Not freeing heap memory
    - Passing by value instead of by reference
    - Unreadable code due to:
        - lack of functions
        - improper indentation or spacing
        - unclear variable names
- Basic C library functions: https://en.cppreference.com/c
    - input/output: printf, scanf, sprintf, sscanf
    - string: strlen, strcpy, strncpy, strcmp, strncmp, strcat, strncat, strchr, strstr
    - file: fopen, fprintf, fscanf, fwrite, fclose
    - memory: malloc, free, calloc, memcpy, memcmp, memset
    - math: cos, sin, exp, log, log10, pow, sqrt


## Books
1. The C Programming Language" (2nd Edition) by Brian W. Kernighan and Dennis M. Ritchie. Old book but a classic: https://www.amazon.in/Programming-Language-Ansi-Version-Old/dp/8120305965/ or https://www.cs.sfu.ca/~ashriram/Courses/CS295/assets/books/C_Book_2nd.pdf
2. C Programming: A Modern Approach" (2nd Edition) by K. N. King. An excellent beginner level book: https://github.com/Embed-Threads/Learn-C/blob/main/books/c-programming-a-modern-approach-2nbsped-0393979504-9780393979503_compress.pdf


## Technical Papers to Read
1. https://www.cs.tufts.edu/cs/40/docs/CTrapsAndPitfalls.pdf


## Installing C Environment in Windows + VS Code
1. Install VS Code: https://code.visualstudio.com/download

2. Install MSYS2: https://www.msys2.org/ or https://github.com/msys2/msys2-installer
- Open CMD
- Run .\msys2-x86_64-latest.exe in --confirm-command --accept-messages --root C:/msys64
- Add to PATH ENV variable: C:\msys64
- Open MSYS2 CRT64
- Run pacman -S base-devel mingw-w64-ucrt-x86_64-toolchain

3. Testing
- Open VS Code, open a Terminal
- Run gcc --version
- Run gdb --version

