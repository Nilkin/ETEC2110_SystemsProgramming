//Name: Thomas Gilman
//Class: ETEC 2110
//Section: 51
//Assignment: 5
#ifndef LIFEFUNCTIONS_H_INCLUDED
#define LIFEFUNCTIONS_H_INCLUDED

#define BOARD_HEIGHT 50
#define BOARD_WIDTH 50

#include <time.h>

//Fill a board with a randomly selected alive cells
void init_board(char **board, int num_alive)
{
    srand(time(0));

    for(int row = 0 ; row < BOARD_WIDTH ; row++)
    {
        for(int col = 0 ; col < BOARD_HEIGHT ; col++)
        {
            board[row][col] = '-'; //fill board with dead cells
        }
    }
    while(num_alive) //pick random alive cells
    {
        int row = rand() % BOARD_WIDTH;
        int col = rand() % BOARD_HEIGHT;
        if(board[row][col] == '-')
        {
            board[row][col] = '*';
            num_alive--;
        }
    }
}
//print rows of chars
void display_board(char **board)
{
    for(int row = 0 ; row < BOARD_WIDTH ; row++)
    {
        for(int col = 0 ; col < BOARD_HEIGHT ; col++)
        {
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}
//return how many neighbors are alive and how many are dead
int num_neighbors(char **board, int x, int y)
{
    int numAlive=0;

    for(signed short row = -1 ; row <= 1 ; row++)
    {
        for(signed short col = -1 ; col <= 1 ; col++)
        {
            if(((x+row < BOARD_HEIGHT) && x+row >= 0) && (y+col < BOARD_WIDTH && y+col >= 0)) //make sure not out of bounds
            {
                if(board[x+row][y+col] == '*' && (x != x+row && y != y+col)) //not itself
                    numAlive++;
            }
        }
    }
    return numAlive++;
}
//determine if the cell is alive or dead
char next_state(char **board, int x, int y)
{
    char newState;
    int numAlive = num_neighbors(board, x, y); //get NumNeighbors still alive

    if(board[x][y] == '*' && (numAlive > 3 || numAlive < 2))
        newState = '-';        //cell is now dead
    else if(board[x][y] == '*' && (numAlive == 3 || numAlive == 2))
        newState = '*';
    else if(board[x][y] == '-' && numAlive == 3)
        newState = '*';
    else
        newState = '-';

    return newState;
}
//parse through the array and use num_neighbors to check if cell should be alive or dead
void next_generation(char **board)
{
    char newBoard[BOARD_WIDTH][BOARD_HEIGHT];
    //fill states for nextGen in separateBoard
    for(short row = 0 ; row < BOARD_WIDTH ; row++)
    {
        for(short col = 0 ; col < BOARD_HEIGHT ; col++)
        {
            newBoard[row][col] = next_state(board,row,col);
        }
    }
    //set board to new generation
    for(short row = 0 ; row < BOARD_WIDTH ; row++)
    {
        for(short col = 0 ; col < BOARD_HEIGHT ; col++)
        {
            board[row][col] = newBoard[row][col];
        }
    }
    display_board(board); //redraw board
}

#endif // LIFEFUNCTIONS_H_INCLUDED
