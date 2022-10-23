#include "renderer.h"
#include "board.h"

/**
 * @file main.c
 * @brief Driver code for my Connect 4 fork. :)
 * @authors DrkWithT (Forker), gskapoor (Original)
 */

/**
 * x is an empty cell, O is for player 1, o is for player 2.
 * 
 * Here is a sample board:
 * xxxxxxx
 * xxxxxxx
 * xxOoxxx
 * oooOOox
 */

static Board *Game_Board = NULL;
static Renderer *Game_Drawer;

_Bool Game_Initialize()
{
  Game_Board = Board_Constr(DEFAULT_BOARD_ROWS, DEFAULT_BOARD_COLS);

  if (!Game_Board)
    return false;
  
  Game_Drawer = Renderer_Constr(Game_Board);

  if (!Game_Drawer)
    return false;

  return true;
}

void Game_Cleanup()
{
  puts("Cleanup Objects...");
  Renderer_Destr(Game_Drawer);
  Board_Destr(Game_Board);
}

_Bool Game_Intro()
{
  console_set_color(C4_INFO_COLOR);
  puts("Connect 4:");
  puts("Player 1 is 'o'. Player 2 is 'O'. Empty cells are 'x'.");
  puts("For each turn, choose a column to drop a piece.");
  puts("To win, one of you should match 4 of your piece, diagonal too.");
  console_clear_color();

  printf("Enter 'y' to continue.");

  // Read 1 char to confirm that one read the info, discard other characters.
  char c = fgetc(stdin);
  fflush(stdin);

  return c == 'y';
}

int main()
{
  // Initialize game variables.
  _Bool turn_is_player1 = true;
  char game_piece = PLAYER_1_PIECE;
  char game_winner = BLANK_CELL;
  int chosen_column = 0;

  // Initialize special objects and setup exit handler in case.
  if (!Game_Initialize())
  {
    printf("Failed to initialize game from allocation error.\n");
    return 1;
  }
  else
  {
    atexit(Game_Cleanup); // This function will be called when the game ends!
  }

  // Confirm game info to continue...
  if (!Game_Intro())
    return 0;

  // Run game loop.
  while (1)
  {
    Renderer_drawAll(Game_Drawer);
    break; // todo: replace with full-board and winner checks for breaking the loop!
  }

  // todo: Print winner!
  return 0;
}
