#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Here is the current plan for the connect for program:
 *
 *  There will be a display, with capital O having an empty space, and o using a space.
 *
 *  Here is a sample board: 
 *  
 *  OOOOOOO
 *  OOOOOOO
 *  ooOOOoO
 *  oOOOOoO
 *  
 *
 */

// Sets up the board with 42 'empty' slots
// uses chars for ease of use as well as for
// the 1 byte memory size
char* init_board(){
  char* board = malloc(sizeof(char) * (6 * 7));
  memset(board, 'X', 42);

}

// Prints out board (by character)
// Currently there is no feature to implement
// different colored boards
void print_board(char* board){
  for (int i = 0; i < 42; i++){
    printf("%c", board[i]);

    if (i % 7 == 0){
      printf("\n");
    }
  }
}

int main(){
  printf("Hello world\n");

  // Time to make the board
  
  init_board();



  return 0;
}
