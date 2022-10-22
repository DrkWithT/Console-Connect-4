#ifndef RENDERER_H
#define RENDERER_H

#include "board.h"
#include "my_utils.h"

typedef struct renderer_object
{
  int col_count; // board column count
  const char *board_data_ptr; // indirect ptr to read board data
  int cell_count; // count of board data's cells
} Renderer;

Renderer *Renderer_Constr(Board *board);

void Renderer_Destr(Renderer *self);

_Bool Renderer_canUse(const Renderer *self);

void Renderer_drawAll(const Renderer *self);

#endif