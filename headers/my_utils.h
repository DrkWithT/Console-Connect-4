#ifndef MY_UTILS_H
#define MY_UTILS_H

#include <stdio.h>

// ANSI CTRL for setting color
#define BEGIN_COLOR_MODE "\033[1;%im"

// ANSI CTRL for defaulting color
#define RESET_COLOR_MODE "\033[0m"

// Player 1 is red
#define P1_CELL_COLOR 31

// Player 2 is blue
#define P2_CELL_COLOR 34

void console_set_color(int ansi_color);

void console_clear_color();

#endif