#ifndef MY_UTILS_H
#define MY_UTILS_H

#include <stdio.h>

// ANSI CTRL for setting color
#define BEGIN_COLOR_MODE "\033[1;%im"

// ANSI CTRL for defaulting color
#define RESET_COLOR_MODE "\033[0m"

#define CLEAR_SCR_SEQ "\033[2J;1;1H\033[0m"

#define RESET_CUR_SEQ "\033[1;1H\033[0m"

// Start info is green.
#define C4_INFO_COLOR 32

// Player 1 is red
#define P1_CELL_COLOR 31

// Player 2 is blue
#define P2_CELL_COLOR 34

/**
 * @brief Sets the terminal color to a color by ANSI code.
 * 
 * @param ansi_color The color code.
 */
void console_set_color(int ansi_color);

/**
 * @brief Resets the terminal printing mode, clearing the color too.
 */
void console_clear_color();

/**
 * @brief Clears all text on the terminal screen.
 */
void console_clear_all();

#endif