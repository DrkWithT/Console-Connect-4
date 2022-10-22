/**
 * @file renderer.c
 * @author DrkWithT (GitHub)
 * @brief Implements Board renderer's functions.
 * @date 2022-10-21
 */

#include "renderer.h"

Renderer *Renderer_Constr(Board *board)
{
  Renderer *new_renderer = NULL;
  _Bool board_usable = true;

  if (board != NULL)
    new_renderer = _new(Renderer);

  if (new_renderer != NULL)
    board_usable = Board_canUse(board);

  if (board_usable)
  {
    new_renderer->col_count = board->cols;
    new_renderer->board_data_ptr = Board_getRawData(board);
    new_renderer->cell_count = Board_getCellCount(board);
  }
  else
  {
    new_renderer->col_count = 0;
    new_renderer->board_data_ptr = NULL;
    new_renderer->cell_count = 0;
  }

  return new_renderer;
}

void Renderer_Destr(Renderer *self)
{
  if (self != NULL)
  {
    self->board_data_ptr = NULL; // unbind ptr from board's data!
    self->cell_count = 0;
    self->col_count = 0;
  }
}

_Bool Renderer_canUse(const Renderer *self)
{
  return self->board_data_ptr != NULL;
}

void Renderer_drawAll(const Renderer *self)
{
  char prev_c = BLANK_CELL;

  for (int cell_idx = 0; cell_idx < self->cell_count; cell_idx++)
  {
    char c = self->board_data_ptr[cell_idx];

    // Moderate Optimization: do not change color mode if last and current chars match!
    // We should not interrupt the terminal with CTRL sequences for each cell char!
    if (c == prev_c)
      printf("%c", c);
    else
    {
      // If the last and current cells differ: switch color mode.
      switch (c)
      {
      case PLAYER_1_PIECE:
        console_set_color(P1_CELL_COLOR);
        break;
      case PLAYER_2_PIECE:
        console_set_color(P2_CELL_COLOR);
        break;
      case BLANK_CELL:
      default:
        console_clear_color();
        break;
      }
    }

    // render on new row after passing a row's span: cols per row
    if (cell_idx % self->col_count == 0)
      printf("\n");
  }
}