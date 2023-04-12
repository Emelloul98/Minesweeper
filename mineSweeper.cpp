
#include "mineSweeper.h"
#include "colorPrint.h"
#include <stdio.h>
#include <string.h>
#include<time.h>
#include <stdlib.h>

bool isInBoard(GameBoard *, int, int);


bool initBoard(GameBoard *g, int rows, int cols, int level) {
    if(cols<1) cols=4;
    if(rows<1) rows=4;
    // a default board value if the input is too small.
    if(cols>20) cols=MAX_BOARD_DIM;
    if(rows>20) rows=MAX_BOARD_DIM;
    // a default board value if the input is too big.
    g->board = (Tile **) malloc(rows * sizeof(Tile *));//the array of pointers initializing.
    if (g->board == NULL) return FALSE;
    for (int i = 0; i < rows; i++) {
        g->board[i] = (Tile *) malloc(cols * sizeof(Tile));//the small arrays that g is pointing at.
        if (g->board[i] == NULL) return FALSE;
    }
    g->rows = rows;
    g->cols = cols;
    g->isMineClicked = FALSE;
    g->hiddenTiles = (cols * rows);
    // default values to all the gameBoard attribute.
    populateMines(g, level);// defining which index will be a Mine.
    markNumbers(g);// a function that calculates how many mines there are around each cell.
    return TRUE;
}

void populateMines(GameBoard *g, int level) {
    // A function that scatters mines randomly on the board.
    int counter, percent, randI, randJ;
    if (level == EASY) percent = EASY_LEVEL_PERCENT;
    else if (level == MEDIUM) percent = MEDIUM_LEVEL_PERCENT;
    else percent = HARD_LEVEL_PERCENT;
    counter = (g->cols * g->rows * percent) / 100;
    g->totalMines = counter;//Defines the total amount of mines in g.
    srand(time(NULL));
    while (counter > 0) {
        randI = rand() % g->rows;
        randJ = rand() % g->cols;
        if (g->board[randI][randJ].isMine == FALSE) {
            // checks if the index is not already a mine.
            g->board[randI][randJ].isMine = TRUE;
            g->board[randI][randJ].numOfMines = -1;
            counter--;
            //increase the counter only if we find a place that is not a mine
        }
    }
}

void markNumbers(GameBoard *g) {
    // a function that is running on all the board and marking the number of mines around each tile.
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->cols; j++) {
            if (g->board[i][j].isMine == FALSE) {
                // only if the tile is not a mine himself.
                int counter = 0;
                if (isInBoard(g, i - 1, j) == TRUE && g->board[i - 1][j].isMine == TRUE) counter++;
                if (isInBoard(g, i + 1, j) == TRUE && g->board[i + 1][j].isMine == TRUE) counter++;
                if (isInBoard(g, i, j - 1) == TRUE && g->board[i][j - 1].isMine == TRUE) counter++;
                if (isInBoard(g, i, j + 1) == TRUE && g->board[i][j + 1].isMine == TRUE) counter++;
                if (isInBoard(g, i - 1, j - 1) == TRUE && g->board[i - 1][j - 1].isMine == TRUE) counter++;
                if (isInBoard(g, i + 1, j - 1) == TRUE && g->board[i + 1][j - 1].isMine == TRUE) counter++;
                if (isInBoard(g, i - 1, j + 1) == TRUE && g->board[i - 1][j + 1].isMine == TRUE) counter++;
                if (isInBoard(g, i + 1, j + 1) == TRUE && g->board[i + 1][j + 1].isMine == TRUE) counter++;
                //counting how many neighbors of g[i][j] are mines.
                g->board[i][j].numOfMines = counter;
            }

        }
    }

}

void clickTile(GameBoard *g, int row, int col) {
    if (isInBoard(g, row, col) == FALSE || g->board[row][col].isVisible == TRUE ||g->board[row][col].isFlagged == TRUE)
        return;
    // when g[i][j] is not in board, or already visible or already flagged -> dont do nothing.
    if (g->board[row][col].isMine == TRUE) {
        g->isMineClicked = TRUE;
        return;
        //when g[i][j] is a mine ->  dont do nothing.
    }
    if (g->board[row][col].numOfMines > 0) {
        g->board[row][col].isVisible = TRUE;
        g->hiddenTiles = (g->hiddenTiles - 1);
        return;
    }
    // when the tile is a number that is not zero.

    if (g->board[row][col].numOfMines == 0) {
        g->board[row][col].isVisible = TRUE;
        g->hiddenTiles = (g->hiddenTiles - 1);
        // shows the tile and marking that he is not hidden anymore.
        clickTile(g, row - 1, col);
        clickTile(g, row + 1, col);
        clickTile(g, row, col - 1);
        clickTile(g, row, col + 1);
        clickTile(g, row - 1, col - 1);
        clickTile(g, row + 1, col - 1);
        clickTile(g, row - 1, col + 1);
        clickTile(g, row + 1, col + 1);
        // calls the function in recursion with all g[i][j] neighbors.
    }
}


bool isInBoard(GameBoard *g, int row, int col) // a private function that returns if the point is in the board limit.
{
    if ((row >= 0) && (row < g->rows) && (col >= 0) && (col < g->cols)) return TRUE;
    return FALSE;
}

void flagTile(GameBoard *g, int row, int col)
// a function that is working when the on and off button of the flag is clicked.
{
    if (g->board[row][col].isVisible == FALSE) {
        if (g->board[row][col].isFlagged == TRUE)
            g->board[row][col].isFlagged = FALSE;
        else g->board[row][col].isFlagged = TRUE;
    }
    // changing the isMine value from true to false or from false to true.

}

void printBoard(GameBoard *g, int cursorCoords[2]) {
//use the colorPrint function in colorPrint.c doc to print the board.
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->cols; j++) {
            if (i == cursorCoords[0] && j == cursorCoords[1]) {
                // represents the cursor.
                colorPrint(FG_Yellow, BG_Yellow, ATT_Def, "  \0");
                continue;
            }

            if (g->board[i][j].isVisible == FALSE) {
                if (g->board[i][j].isFlagged == TRUE) {
                    //when the tile is flagged and is not visible.
                    colorPrint(FG_Red, BG_White, ATT_Def, " F\0");
                } else colorPrint(FG_Blue, BG_White, ATT_Def, "  \0");
                // the else is when the tile is not visible and not flagged.
            }
            if (g->board[i][j].isVisible == TRUE) {
                char str[3];// sent a 3 length char in this format
                sprintf(str, " %d", g->board[i][j].numOfMines);
                colorPrint(FG_Blue, BG_White, ATT_Def, str);
                // sending the char to colorPrint in colorPrint.c doc
                continue;
            }

        }
        printf("\n");

    }
}









