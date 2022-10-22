#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_BOARD_ROWS 6
#define DEFAULT_BOARD_COLS 7

#define PLAYER_1_PIECE 'o'
#define PLAYER_2_PIECE 'O'
#define BLANK_CELL 'x'

/// Simulate a crude "new" operator in C.
#define _new(my_type) malloc(sizeof(my_type))

typedef struct board_object
{
  int rows;         // Row count
  int cols;         // Column count
  int cell_count;   // Row * Column counts
  char *cell_data;  // A 1-D array storing all row data, and it is rows x cols in size: [r1, r2... r_n]

  int last_row; // last placement position: row

  int last_col; // last placement position: column

  int fill_count; // filled cell count
}Board;

Board *Board_Constr(int rowc, int colc);

void Board_Destr(Board *self);

_Bool Board_canUse(const Board *self);

int Board_getCellCount(Board *self);

_Bool Board_isFull(const Board *self);

const char *Board_getRawData(const Board *self);

int Board_getRowOfMove(const Board *self);

int Board_getColOfMove(const Board *self);

/**
 * @brief Inserts a piece at the specified column by index. The piece is then translated downward to the last, lowest blank cell.
 * 
 * @param self 
 * @param col_idx 
 * @param c 
 * @return _Bool 
 */
_Bool Board_putPiece(Board *self, int col_idx, char c);

void Board_clearCells(Board *self);

_Bool static Board_checkVerticalsAt(Board *self, int row_idx, int col_idx);

_Bool static Board_checkHorizontalsAt(Board *self, int row_idx, int col_idx);

_Bool static Board_checkUpperDiagonalsAt(Board *self, int row_idx, int col_idx);

/**
 * @brief This is a generalized function that checks for any 4-streak of a player piece along a diagonal. The diagonal is specified with step components, like 2D vector x-component or y-component.
 * 
 * @param self The Board ptr.
 * @param row_idx Position row.
 * @param col_idx Position column.
 * @param row_step Step magnitude to next row from position.
 * @param col_step Step magnitude to next col from position.
 * @return _Bool If the diagonal has a win.
 */
_Bool static Board_checkDiagonalFrom(Board *self, int row_idx, int col_idx, int row_step, int col_step);

_Bool Board_hasWinner(Board *self, int row_idx, int col_idx);

#endif