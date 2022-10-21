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

    new_board->last_row = 0;
    new_board->last_col = 0;
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
    self->last_col = 0;
    self->last_row = 0;
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

// TODO: rewrite loop logic!!
_Bool Board_putPiece(Board *self, int col_idx, char c)
{
  _Bool col_valid = col_idx >= 0 && col_idx < self->cols; // if the column dropped into is valid
  int drop_count = 0;                                     // how much the piece drops... > 0 if we have a vacant column
  int data_idx = 0;

  if (col_valid)
  {
    for (int i = 0; i < self->cell_count; i++)
    {
      data_idx = col_idx + i * self->cols;
      char testc = self->cell_data[data_idx];

      if (testc != BLANK_CELL)
      {
        if (drop_count > 0)
        {
          data_idx -= self->cols; // backtrack to space above filled cell to place new piece
          self->cell_data[data_idx] = c;
          self->last_col = col_idx;
          self->last_row = 0;
        }
        break;
      }

      drop_count++; // track dropping depth of piece
    }
  }

  return col_valid && drop_count > 0;
}

void Board_clearCells(Board *self)
{
  memset(self->cell_data, BLANK_CELL, self->cell_count);
}

_Bool Board_hasWinner(Board *self, int row_idx, int col_idx)
{
  // check most recently placed piece for a 4-streak...
  int count = 0;
  _Bool has_win_turn = false;

  // 1. check verticals

  // 2. check horizontals

  // 3. check diagonals

  return has_win_turn;
}