/**
 * @file board.c
 * @author Derek Tan (DrkWithT @ GitHub)
 * @brief Implements the Board object.
 * @version 0.1
 * @date 2022-10-19
 */

#include "board.h"

Board *Board_Constr(int rowc, int colc)
{
  Board *new_board = _new(Board);

  _Bool alloc_ok = new_board != NULL;
  _Bool args_ok = rowc > 4 && colc > 4;

  int temp_rows = 0;
  int temp_cols = 0;

  // Initialize only if allocation of object went ok.
  if (args_ok)
  {
    temp_rows = rowc;
    temp_cols = colc;
  } else {
    temp_rows = DEFAULT_BOARD_ROWS;
    temp_cols = DEFAULT_BOARD_COLS;
  }

  if (alloc_ok)
  {
    new_board->rows = temp_rows;
    new_board->cols = temp_cols;
    new_board->cell_count = temp_rows * temp_cols;
    new_board->cell_data = malloc(new_board->cell_count + 1);
    memset(new_board->cell_data, BLANK_CELL, new_board->cell_count);
  }

  return new_board;
}

void Board_Destr(Board *self)
{
  if (self != NULL)
  {
    free(self->cell_data);
    self->cell_count = 0;
    self->cols = 0;
    self->rows = 0;
  }
}

_Bool Board_canUse(const Board *self)
{
  return self->cell_data != NULL;
}

int Board_getCellCount(Board *self)
{
  return self->cell_count;
}

const char *Board_getRawData(const Board *self)
{
  return self->cell_data;
}

_Bool Board_putPiece(Board *self, int col_idx, char c)
{
  _Bool col_valid = col_idx >= 0 && col_idx < self->cols; // if the column dropped into is valid
  int drop_count = 0;                                     // how much the piece drops... > 0 if we have a vacant column

  if (col_valid)
  {
    for (int i = 0; i < self->cell_count; i += self->cols)
    {
      char testc = self->cell_data[col_idx];
      int slot_idx = i;

      if (testc != BLANK_CELL)
      {
        slot_idx -= self->cols;
        self->cell_data[slot_idx] = c;
        break;
      }

      drop_count++; // track dropping depth of piece
    }
  }

  return col_valid && drop_count;
}

void Board_clearCells(Board *self)
{
  memset(self->cell_data, BLANK_CELL, self->cell_count);
}

char Board_findWinner(Board *self)
{
  char winning_piece = BLANK_CELL;
  int match_count = 0;

  // todo: implement logic: track "match scores" per row, column, and diagonals (rows below 3rd row from top)!

  return winning_piece;
}