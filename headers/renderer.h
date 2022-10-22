#ifndef RENDERER_H
#define RENDERER_H

#include "board.h"
#include "my_utils.h"

typedef struct renderer_object
{
  int row_count; // board row count
  int col_count; // board column count
  const char *board_data_ptr; // indirect ptr to read board data
} Renderer;

Renderer *Renderer_Constr(Board *board);

void Renderer_Destr(Renderer *self);

void Renderer_drawAll();

#endif