
#include <stdio.h>
#include "getch.h"
#include "mineSweeper.h"
#include "colorPrint.h"
#include <stdlib.h>
int main() {
    int row, col, level;
    printf("how many rows do you want to play with(20=max) ?");
    scanf("%d", &row);
    printf("how many cols do you want to play with(20=max) ?");
    scanf("%d", &col);
    printf("enter a number from 1 to 3 for the difficulty level of the game:");
    scanf("%d", &level);
    char input;
    GameBoard g;// defines a new board named g.
    bool game;
    game = initBoard(&g, row, col, level);
    if (game == FALSE) exit(1);
    int array[2] = {0, 0}; // starting the cursor in (0,0)
    getch();
    do {
        clearScreen();
        printBoard(&g, array);
        input = getch();
        if (input == UP && array[0] != 0) array[0]--;
        else if (input == DOWN && array[0] != g.rows - 1) array[0]++;
        else if (input == LEFT && array[1] != 0) array[1]--;
        else if (input == RIGHT && array[1] != g.cols - 1) array[1]++;
            //moving the cursor according to the click if its possibale on the board.
        else if (input == FLAG_TILE) flagTile(&g, array[0], array[1]);
            //colling the flagTile function on the cursor position.
        else if (input == CLICK_TILE) clickTile(&g, array[0], array[1]);
        //calling the function clickTile on the cursor position.
        if (g.isMineClicked == TRUE) {
            printf("\n you lost :( ");
            break;
            // when the user clicked on a tile and loses.
        }
        if (g.hiddenTiles == g.totalMines) {
            clearScreen();
            array[0]=-1;
            array[1]=-1;
            // moving the cursor from the board.
            printBoard(&g,array);
            // printing the board without the cursor.
            printf("\n congratulations you won!!");
            break;
            //when the user win the game
        }
    } while (input != QUIT);

    //free the malloc of  the board
    for (int i = 0; i < g.rows; i++)
    {
        free(g.board[i]);
    }
    free(g.board);




}





