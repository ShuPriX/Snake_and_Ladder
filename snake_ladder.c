/* created on 20/08/2024 by Shubhradeep Paul(2330337)
Documentation:
    1.This is a friendly game created only using C programming language
    2.This Snake and Ladder game can accomodate two players taking their turns to roll the dice first one to reach 100 wins the game
    3.Consists of two functions Roll_Dice(), Update_player_position()
ThankYou for trying out and playing this game
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ANSI escape codes for colors
#define YELLOW_BOX "\x1b[43m  \x1b[0m"  // Yellow background box
#define PLAYER1_COLOR "\x1b[31mP1\x1b[0m"  // Red color for Player 1
#define PLAYER2_COLOR "\x1b[32mP2\x1b[0m"  // Green color for Player 2
#define SNAKE_SYMBOL "\x1b[33m$$\x1b[0m"   // Yellow color for snakes
#define LADDER_SYMBOL "\x1b[35mHH\x1b[0m"  // Magenta color for ladders

int rollDice() { //this function helps us retrive random numbers from 1 to 6, uses rand function
    return (rand() % 6) + 1;
}

void waitForEnter() {
    printf("Press Enter to continue...\n");
    while (getchar() != '\n');
}

int Snake_and_Ladder[101] = {0}; // Initialize the board with 0 for no snake or ladder

// Defining the ladders
void setupSnakesAndLadders() {
    Snake_and_Ladder[2] = 36;
    Snake_and_Ladder[4] = 10;
    Snake_and_Ladder[9] = 22;
    Snake_and_Ladder[33] = 52;
    Snake_and_Ladder[52] = 36;
    Snake_and_Ladder[80] = 11;

    // Defining the snakes
    Snake_and_Ladder[51] = -40;
    Snake_and_Ladder[56] = -41;
    Snake_and_Ladder[62] = -5;
    Snake_and_Ladder[92] = -39;
    Snake_and_Ladder[98] = -90;
}

void print_cell(int number, int player1_pos, int player2_pos) {
    // Check if this cell contains Player 1's position
    if (number == player1_pos) {
        printf(YELLOW_BOX PLAYER1_COLOR YELLOW_BOX " ");
    } 
    // Check if this cell contains Player 2's position
    else if (number == player2_pos) {
        printf(YELLOW_BOX PLAYER2_COLOR YELLOW_BOX " ");
    } 
    // Check if this cell contains a ladder
    else if (Snake_and_Ladder[number] > 0) { 
        printf(YELLOW_BOX LADDER_SYMBOL YELLOW_BOX " ");
    }
    // Check if this cell contains a snake
    else if (Snake_and_Ladder[number] < 0) {  
        printf(YELLOW_BOX SNAKE_SYMBOL YELLOW_BOX " ");
    } 
    //If none of the above, print a blank yellow cell
    else {
        printf(YELLOW_BOX "  " YELLOW_BOX " ");
    }
}

void board(int player1_pos, int player2_pos) {
    int board[101];
    for (int i = 1; i <= 100; i++) {
        board[i] = i;
    }

    int alt = 0;  //This variable alternates between 0 and 1 to control whether the current row is printed from left to right or right to left. It ensures that the "snaking" nature of the board (where odd rows go left-to-right and even rows go right-to-left) is correctly represented.
    int iterLR = 101;  //This variable is used to iterate from left to right on the board. It starts at 101 (just outside the board limit of 100) and decreases as the board is printed. It handles the odd-numbered rows (from top to bottom, like 91 to 100, 71 to 80, etc.).
    int iterRL = 80;   //This variable is used to iterate from right to left on the board. It starts at 80 and increases as the board is printed. It handles the even-numbered rows (like 81 to 90, 61 to 70, etc.).
    int val = 100; //This variable keeps track of the number of iterations. It counts down from 100 and ensures that the loop only runs 100 times, which corresponds to the 100 squares on the board.

    while (val--) { //This loop runs until val becomes 0. Since val is initialized to 100, it will run exactly 100 times, corresponding to each square on the board. The val-- operation decrements val with each iteration.
        
        if (alt == 0) { //When alt is 0, the board is being printed from left to right (e.g., 91 to 100, 71 to 80).Inside this block, iterLR-- decreases the value of iterLR, which moves from 101 down to 1.
            iterLR--;
            print_cell(board[iterLR], player1_pos, player2_pos);

            if (iterLR % 10 == 1) { //If the current square (iterLR) is at the end of a row (i.e., divisible by 10 with a remainder of 1, like 91, 81, etc.), a newline is printed, and alt is set to 1 to indicate that the next row should be printed from right to left. The iterLR -= 10 statement skips back 10 positions to prepare for the next row.
                printf("\n\n");
                alt = 1;
                iterLR -= 10;
            }
        } else { //When alt is 1, the board is being printed from right to left (e.g., 81 to 90, 61 to 70).Inside this block, iterRL++ increases the value of iterRL, which moves from 80 up to 100.
            iterRL++; // If iterRL matches the position of player 1 or player 2, their symbol is printed. Otherwise, the square number is printed.
            print_cell(board[iterRL], player1_pos, player2_pos);

            if (iterRL % 10 == 0) { //If the current square (iterRL) is at the end of a row (i.e., divisible by 10 with no remainder, like 90, 80, etc.), a newline is printed, and alt is set to 0 to indicate that the next row should be printed from left to right. The iterRL -= 30 statement skips back 30 positions to align the board for the next row.
                printf("\n\n");
                alt = 0;
                iterRL -= 30;
            }
        }
        if (iterRL == 10) //The loop will exit if iterRL reaches 10, meaning the entire board has been printed, and the loop can terminate early.
            break;
    }
    printf("\n");
}

int main() {
    srand(time(0)); // Seed the random number generator with current time.This ensures that every time you run the game, the dice rolls will be different.  
    int player1 = 0, player2 = 0;
    int turn = 1;  // 1 for player1, 2 for player2

    setupSnakesAndLadders();  // Setup snakes and ladders

    // Start the game
    printf("Welcome to Snake and Ladder!\n");
    waitForEnter();  // Wait for the player to start the game

    while (player1 < 100 && player2 < 100) {
        printf("\n");
        board(player1, player2);

        if (turn == 1) {
            printf("Player 1 rolled a ");
            int roll = rollDice();
            printf("%d\n", roll);
            player1 += roll;
            if (player1 > 100) {
                player1 -= roll;
                printf("Player 1 needs an exact roll to win. Try again next turn.\n");
            } else {
                if (Snake_and_Ladder[player1] != 0) {
                    int prev_position = player1;
                    player1 += Snake_and_Ladder[player1];
                    if (Snake_and_Ladder[prev_position] > 0) {
                        printf("Player 1 climbed a ladder to %d!\n", player1);
                    } else {
                        printf("Player 1 got bitten by a snake to %d!\n", player1);
                    }
                }
            }
            printf("Player 1 is at %d\n", player1);
            waitForEnter();  // Wait for player to press Enter
            turn = 2;  // Switch turn to player 2
        } else {
            printf("Player 2 rolled a ");
            int roll = rollDice();
            printf("%d\n", roll);
            player2 += roll;
            if (player2 > 100) {
                player2 -= roll;
                printf("Player 2 needs an exact roll to win. Try again next turn.\n");
            } else {
                if (Snake_and_Ladder[player2] != 0) {
                    int prev_position = player2;
                    player2 += Snake_and_Ladder[player2];
                    if (Snake_and_Ladder[prev_position] > 0) {
                        printf("Player 2 climbed a ladder to %d!\n", player2);
                    } else {
                        printf("Player 2 got bitten by a snake to %d!\n", player2);
                    }
                }
            }
            printf("Player 2 is at %d\n", player2);
            waitForEnter();  // Wait for player to press Enter
            turn = 1;  // Switch turn to player 1
        }

        if (player1 == 100) {			
            printf("Player 1 wins!\n");
            break;
        } else if (player2 == 100) {
            printf("Player 2 wins!\n");
            break;
        }
    }

    return 0;
}
