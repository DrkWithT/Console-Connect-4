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

/// User input buffer size:
#define INPUT_BUF_SIZE 4

static Board *Game_Board = NULL;
static Renderer *Game_Drawer;
static char Input_Buffer[INPUT_BUF_SIZE];

_Bool Game_Initialize()
{
  memset(Input_Buffer, '\0', INPUT_BUF_SIZE);

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

void Game_Prompt_User(int player_num, char *input_buf, int buf_size)
{
  // show prompt
  printf("P%i, enter your column: ", player_num);

  // get input with finite length and null terminator
  fgets(input_buf, 1, stdin);
  input_buf[buf_size - 1] = '\0';
}

int Game_Atoi(const char *input_buf)
{
  int temp = atoi(input_buf);

  if (input_buf[0] == '0')
    temp = 0;
  else if (temp == 0)
    temp = -1; // default conversion for NaN literals!
  
  return temp;
}

inline _Bool Game_Validate_Input(int col_num)
{
  return col_num >= 0 && col_num < Game_Board->cols;
}

void Game_Say_Winner(char player_piece)
{
  switch (player_piece)
  {
  case PLAYER_1_PIECE:
    puts("Player 1 won.");
    break;
  case PLAYER_2_PIECE:
    puts("Player 2 won.");
    break;
  case BLANK_CELL:
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
  char game_winner = BLANK_CELL;
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
  while (1)
  {
    Renderer_drawAll(Game_Drawer); // draw board

    Game_Prompt_User(player_number, Input_Buffer, INPUT_BUF_SIZE);

    chosen_column = Game_Atoi(Input_Buffer); // convert input string to column index or -1

    if (Game_Validate_Input(chosen_column))
    {
      Board_putPiece(Game_Board, chosen_column, game_piece);
      move_row = Board_getRowOfMove(Game_Board);
      move_col = Board_getColOfMove(Game_Board);
    }
    else
    {
      game_winner = BLANK_CELL;
      break; // treat invalid cols as quitting!
    }

    if (Board_hasWinner(Game_Board, move_row, move_col))
    {
      game_winner = game_piece;
      break;
    }
    else
      game_winner = BLANK_CELL;

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

  Game_Say_Winner(game_winner);

  return 0;
}
