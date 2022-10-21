#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_BOARD_ROWS 6
#define DEFAULT_BOARD_COLS 6

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

  // last placement position: row
  int last_row;

  // last placement position: column
  int last_col;
}Board;

Board *Board_Constr(int rowc, int colc);

void Board_Destr(Board *self);

_Bool Board_canUse(const Board *self);

int Board_getCellCount(Board *self);

const char *Board_getRawData(const Board *self);

_Bool Board_putPiece(Board *self, int col_idx, char c);

void Board_clearCells(Board *self);

_Bool Board_hasWinner(Board *self, int row_idx, int col_idx);

#endif