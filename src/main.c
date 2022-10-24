#include "renderer.h"
#include "board.h"

/**
 * @file main.c
 * @brief Driver code for my Connect 4 fork. :)
 * @authors DrkWithT (Forker), gskapoor (Original)
 * @version 0.1.0 Added basic checking logic.
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
  char c = fgetc(stdin); // TODO: handle possible input overflow?

  return c == 'y';
}

int Game_Prompt_User(int player_num)
{
  // show prompt
  printf("P%i, enter your column: ", player_num);

  int temp_col = -1; // probably default to the last ASCII char?

  // get input with finite length and null terminator:
  scanf("%i", &temp_col);

  return temp_col;
}

_Bool Game_Validate_Input(int col_num)
{
  return col_num >= 0 && col_num < Board_getCols(Game_Board);
}

void Game_Say_Winner(int player_num)
{
  switch (player_num)
  {
  case 1:
    puts("Player 1 won.");
    break;
  case 2:
    puts("Player 2 won.");
    break;
  default:
    puts("Tie!");
    break;
  }
}

int main()
{
  // Initialize game variables.
  int player_number = 1;
  char game_piece = PLAYER_1_PIECE;
  int chosen_column = 0;
  int move_row = 0;
  int move_col = 0;

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
  while (true)
  {
    Renderer_drawAll(Game_Drawer); // draw board

    chosen_column = Game_Prompt_User(player_number);

    if (Game_Validate_Input(chosen_column))
    {
      _Bool move_ok = Board_putPiece(Game_Board, chosen_column, game_piece);
      move_row = Board_getRowOfMove(Game_Board);
      move_col = Board_getColOfMove(Game_Board);

      if (!move_ok)
      {
        puts("This column is full!");
        player_number = -1;
        break;
      }

      if (Board_hasWinner(Game_Board, move_row, move_col)) break;

      if (Board_isFull(Game_Board)) break;
    }
    else
    {
      puts("Invalid move!"); // handle invalid column input!
      player_number = -1;
      break;
    }

    // Toggle current player and piece.
    if (player_number == 1)
    {
      player_number = 2;
      game_piece = PLAYER_2_PIECE;
    }
    else
    {
      player_number = 1;
      game_piece = PLAYER_1_PIECE;
    }
  }

  // show board and print winner at last!
  Renderer_drawAll(Game_Drawer);
  Game_Say_Winner(player_number);

  return 0;
}
