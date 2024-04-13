# Minesweeper
A simple minesweeper game in c
works on linux only!!
For those who dont know the rules of the game here is a small tutorial:
https://minesweepergame.com/strategy/how-to-play-minesweeper.php
In order to start the game you will first have to choose a game size between 1 and 20 and a difficulty level between 1 and 3
To control the cursor click on the characters 'w' 'd' 's' 'a' in inglish only!
To mark a flag press space
And to finish the game press 'q'

---

**Features:**
1. Terminal interface for playing Minesweeper.
2. Customizable board size and difficulty levels.
3. Flagging tiles to mark potential mines.
4. Revealing tiles to uncover numbers or mines.
5. Win condition when all non-mine tiles are revealed.
6. Lose condition upon clicking a mine tile.
7. Dynamic board display during gameplay.

---

**Components:**
1. **`main.c`:**
   - Entry point for the program, contains the main game loop and logic.
   - Handles user input and calls appropriate functions based on input commands.

2. **`mineSweeper.h` and `mineSweeper.c`:**
   - Header and source files defining the Minesweeper game structure and functions.
   - Includes functions for initializing the board, populating mines, marking numbers, clicking tiles, flagging tiles, and checking game conditions.

3. **`colorPrint.h` and `colorPrint.c`:**
   - Header and source files providing functions for color printing in the terminal.
   - Includes functions for clearing the screen and printing colored text.

4. **`getch.h` and `getch.c`:**
   - Header and source files for reading a single character from the terminal without waiting for a newline.
   - Includes functions `getch` and `getche` for input handling.

---

**Running the Game:**
1. Compile the program using a C compiler such as GCC: `gcc main.c mineSweeper.c colorPrint.c getch.c -o minesweeper`.
2. Run the compiled executable: `./minesweeper`.
3. Follow the on-screen instructions to play the Minesweeper game.
4. Use arrow keys or WASD keys to navigate the cursor, spacebar to reveal tiles, and F to flag tiles.

---

**Example:**

```
$ gcc main.c mineSweeper.c colorPrint.c getch.c -o minesweeper
$ ./minesweeper
Welcome to Minesweeper!

Enter number of rows (4-20): 10
Enter number of columns (4-20): 10
Select difficulty level (1-Easy, 2-Medium, 3-Hard): 2

Game started! Use arrow keys or WASD to navigate, Space to reveal tiles, and F to flag/unflag tiles.

   1 2 3 4 5 6 7 8 9 10
A  _ _ _ _ _ _ _ _ _ _
B  _ _ _ _ _ _ _ _ _ _
C  _ _ _ _ _ _ _ _ _ _
D  _ _ _ _ _ _ _ _ _ _
E  _ _ _ _ _ _ _ _ _ _
F  _ _ _ _ _ _ _ _ _ _
G  _ _ _ _ _ _ _ _ _ _
H  _ _ _ _ _ _ _ _ _ _
I  _ _ _ _ _ _ _ _ _ _
J  _ _ _ _ _ _ _ _ _ _

Enter command (WASD to move, Space to reveal, F to flag): 
```
![Image Alt Text](https://github.com/Emelloul98/Minesweeper/blob/main/Example.png)
---
