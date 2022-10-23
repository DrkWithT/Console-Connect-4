/**
 * @file board.c
 * @author Derek Tan (DrkWithT @ GitHub)
 * @brief Implements the Board functions.
 * @note The win checking functions rely on the most recent piece placement location by some player.
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

    if (Board_canUse(new_board))
      memset(new_board->cell_data, BLANK_CELL, new_board->cell_count);

    new_board->last_row = 0;
    new_board->last_col = 0;
    new_board->fill_count = 0;
  }

  return new_board;
}

void Board_Destr(Board *self)
{
  if (self != NULL)
  {
    if (Board_canUse(self))
    {
      free(self->cell_data);
      self->cell_data = NULL;
    }
    
    self->cell_count = 0;
    self->cols = 0;
    self->rows = 0;
    
    self->last_col = 0;
    self->last_row = 0;
    self->fill_count = 0;
  }
}

int Board_getCols(const Board *self)
{
  return self->cols;
}

_Bool Board_canUse(const Board *self)
{
  return self->cell_data != NULL;
}

int Board_getCellCount(Board *self)
{
  return self->cell_count;
}

_Bool Board_isFull(const Board *self)
{
  return self->fill_count == self->cell_count;
}

const char *Board_getRawData(const Board *self)
{
  return self->cell_data;
}

int Board_getRowOfMove(const Board *self)
{
  return self->last_row;
}

int Board_getColOfMove(const Board *self)
{
  return self->last_col;
}

// TODO: rewrite loop logic!!
_Bool Board_putPiece(Board *self, int col_idx, char c)
{
  _Bool col_valid = col_idx >= 0 && col_idx < self->cols; // if the column dropped into is valid
  int drop_count = 0;                                     // how much the piece drops... > 0 if we have a vacant column
  int data_idx = 0;

  if (col_valid)
  {
    int i = 0;
    for (; i < self->rows; i++)
    {
      data_idx = col_idx + i * self->cols;
      char testc = self->cell_data[data_idx];

      if (testc != BLANK_CELL)
      {
        if (drop_count > 0)
        {
          data_idx -= self->cols; // backtrack to space above filled cell to place new piece

          if (data_idx >= 0 && data_idx < self->cell_count) // check if backtrack is still in bounds
          {
            self->cell_data[data_idx] = c;
            self->last_col = col_idx;
            self->last_row = 0;

            self->fill_count++; // on successful move: update fill count!
          }
        }

        return col_valid && drop_count > 0;
      }

      drop_count++; // track dropping depth of piece
    }

    i--; // backtrack above bottom row idx just outside bounds
    data_idx = col_idx + i * self->cols;
    
    // final placing attempt if column was all empty...
    if (self->cell_data[data_idx] == BLANK_CELL) {
      drop_count = i;
      self->cell_data[data_idx] = c;
      self->last_col = col_idx;
      self->last_row = i;

      self->fill_count++;
    }
  }

  return col_valid && drop_count > 0;
}

void Board_clearCells(Board *self)
{
  memset(self->cell_data, BLANK_CELL, self->cell_count);
  self->cell_data[self->cell_count] = '\0'; // put terminator char
}

_Bool Board_checkVerticalsAt(Board *self, int row_idx, int col_idx)
{
  int count = 0; // match count per vertical check

  char prev = BLANK_CELL; // previous cell for match checking
  int tmp_idx = col_idx + row_idx * self->cols;

  // check above vertical
  while (tmp_idx > 0)
  {
    char tmp = self->cell_data[tmp_idx];

    if (tmp == prev)
      count++;
    else
      count = 0;

    if (count >= 3)
      goto endChecks; // short circuit if 1st check is a win!

    tmp_idx -= self->cols;
    prev = tmp;
  }

  count = 0;
  prev = BLANK_CELL;
  tmp_idx = col_idx + row_idx * self->cols;

  while (tmp_idx < self->cell_count)
  {
    char tmp = self->cell_data[tmp_idx];

    if (tmp != BLANK_CELL && tmp == prev)
      count++;
    else
      count = 0;

    if (count >= 3)
      goto endChecks;

    tmp_idx += self->cols;
    prev = tmp;
  }
  
endChecks:
  return count >= 3;
}

_Bool Board_checkHorizontalsAt(Board *self, int row_idx, int col_idx)
{
  int count = 0;
  char prev = BLANK_CELL;
  int location = col_idx + row_idx * self->cols; // pre-computed location of most recent piece placement
  int tmp_idx = location;
  int lower_end = tmp_idx - self->cols + 1;
  
  // Goes to lower bound of horizontal check: "start of row" index!
  while (tmp_idx >= lower_end)
  {
    char tmp = self->cell_data[tmp_idx];

    if (tmp != BLANK_CELL && tmp == prev)
      count++;
    else
      count = 0;

    if (count >= 3)
      goto endChecks;
    
    tmp_idx--;
    prev = tmp;
  }

  count = 0;
  prev = BLANK_CELL;
  tmp_idx = location;
  
  // Goes to upper bound of the horizontal check: "end of row" index!
  while ((tmp_idx + 1) % self->cols != 0)
  {
    char tmp = self->cell_data[tmp_idx];

    if (tmp != BLANK_CELL && tmp == prev)
      count++;
    else
      count = 0;

    if (count >= 3)
      goto endChecks;
    
    tmp_idx--;
    prev = tmp;
  }
  
endChecks:
  return count >= 3;
}

_Bool Board_checkDiagonalFrom(Board *self, int row_idx, int col_idx, int row_step, int col_step)
{
  int count = 0;           // count of matched cells by diagonal
  char prev = BLANK_CELL;  // previous tracked cell's data
  int location = col_idx + row_idx * self->cols;

  int tmp_idx = location;  // cell data access index
  int temp_col = col_idx;  // equivalent column index
  int temp_row = row_idx;  // equivalent row index

  // check a diagonal by direction components...
  while (tmp_idx > 0)
  {
    char tmp = self->cell_data[tmp_idx];

    if (tmp != BLANK_CELL && tmp == prev)
      count++;
    else
      count = 0;

    if (count >= 3)
      break;

    // move selection to next, possible cell location
    temp_col += col_step;
    temp_row += row_step;

    // check if cell location is in bounds: end scan if it's not!
    if (temp_col < 0 || temp_col >= self->cols || temp_row >= self->rows || temp_row < 0)
    {
      count = 0;
      break;
    }

    tmp_idx = temp_col + temp_row * self->cols;
    prev = tmp;
  }

  return count >= 3; // todo
}

_Bool Board_hasWinner(Board *self, int row_idx, int col_idx)
{
  return Board_checkVerticalsAt(self, row_idx, col_idx)
  || Board_checkHorizontalsAt(self, row_idx, col_idx)
  || Board_checkDiagonalFrom(self, row_idx, col_idx, -1, -1) // top left diagonal
  || Board_checkDiagonalFrom(self, row_idx, col_idx, -1, 1)  // top right diagonal
  || Board_checkDiagonalFrom(self, row_idx, col_idx, 1, 1)   // bottom right diagonal
  || Board_checkDiagonalFrom(self, row_idx, col_idx, 1, -1); // bottom left diagonal
}