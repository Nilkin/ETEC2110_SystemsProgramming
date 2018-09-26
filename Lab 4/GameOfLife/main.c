//Name: Thomas Gilman
//Class: ETEC 2110
//Section: 51
//Assignment: 5

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "LifeFunctions.h"

#define NUM_ALIVE 1000
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT

int Drawing = 1;
char** Board;
char StringInput[6]; //string input from user

int main(int argc, char * argv[])
{
    //Create 2d array of type char
    Board = (char**) malloc(BOARD_WIDTH * sizeof(*Board));
    for(int row = 0 ; row < BOARD_WIDTH ; row++)
        Board[row] = (char *) malloc(BOARD_HEIGHT * sizeof(**Board));

    init_board(Board,NUM_ALIVE);
    display_board(Board);

    while(Drawing)
    {
        printf("type quite to exit,\npress enter for next phase:\n");
        fgets(StringInput,sizeof(StringInput),stdin);
        if(strcmp(StringInput,"quite") == 0
           || strcmp(StringInput,"exit\n") == 0
           || strcmp(StringInput,"q\n") == 0)
            Drawing=0;
        else
            next_generation(Board);
    }
    //Free memory for use
    for(int row = 0 ; row < BOARD_WIDTH ; row++)
        free(Board[row]);
    free(Board);

    return 0;
}
