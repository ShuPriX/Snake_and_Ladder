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

int Roll_Dice() //this function helps us retrive random numbers from 1 to 6, uses rand function
{
    return (rand() % 6) + 1;
}
int player1_pos = 0;
int player2_pos = 0;
int Update_player_position(int currentPosition, int roll)
{
    int Snake_and_Ladder[101] = {0}; // Initialize the board with 0 for no snake or ladder

    // Defining the ladders
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

    int newPosition = currentPosition + roll; //this gives the position of the player by adding the current position and the die number
    if (newPosition > 100) //checks if the player goes beyond the 100th square
    {
        return currentPosition; // Player cannot move beyond square 100 and his turn is skipped
    }

    newPosition += Snake_and_Ladder[newPosition]; //new position corresponds to the board

    if (newPosition > 100)
    {
        return currentPosition; // Again, ensure player doesn't go beyond square 100
    }

    return newPosition;
}

void board(){ 
/* First Row (alt == 0): The board starts printing from 100 down to 91. This is handled by iterLR.
    Second Row (alt == 1): The board prints from 81 up to 90. This is handled by iterRL.
    Third Row (alt == 0): The board prints from 80 down to 71, again using iterLR.
    And so on...
    This alternating pattern continues until the entire board is printed, following the snaking nature of a traditional Snake and Ladder game board. The players' positions are updated dynamically during gameplay, so each time the board is printed, it reflects their current positions. */
    int board[101];
    for (int i = 1; i <= 100; i++)
    {
        board[i] = i;
    }

    int alt = 0; //This variable alternates between 0 and 1 to control whether the current row is printed from left to right or right to left. It ensures that the "snaking" nature of the board (where odd rows go left-to-right and even rows go right-to-left) is correctly represented.
    int iterLR = 101; //This variable is used to iterate from left to right on the board. It starts at 101 (just outside the board limit of 100) and decreases as the board is printed. It handles the odd-numbered rows (from top to bottom, like 91 to 100, 71 to 80, etc.).
    int iterRL = 80; //This variable is used to iterate from right to left on the board. It starts at 80 and increases as the board is printed. It handles the even-numbered rows (like 81 to 90, 61 to 70, etc.).
    int val = 100; //This variable keeps track of the number of iterations. It counts down from 100 and ensures that the loop only runs 100 times, which corresponds to the 100 squares on the board.
    while (val--) //This loop runs until val becomes 0. Since val is initialized to 100, it will run exactly 100 times, corresponding to each square on the board. The val-- operation decrements val with each iteration.
    {
        if (alt == 0) //When alt is 0, the board is being printed from left to right (e.g., 91 to 100, 71 to 80).Inside this block, iterLR-- decreases the value of iterLR, which moves from 101 down to 1.
        {
            iterLR--;
            if (iterLR == player1_pos) //If iterLR matches the position of player 1 or player 2 (player1_pos or player2_pos), their symbol (#P1 or #P2) is printed on the board. Otherwise, the square number (board[iterLR]) is printed.
            {
                printf("#P1 ");
            }
            else if (iterLR == player2_pos)
            {
                printf("#P2 "); 
            }
            else
            {
                printf("%d ", board[iterLR]);
            }

            if (iterLR % 10 == 1) //If the current square (iterLR) is at the end of a row (i.e., divisible by 10 with a remainder of 1, like 91, 81, etc.), a newline is printed, and alt is set to 1 to indicate that the next row should be printed from right to left. The iterLR -= 10 statement skips back 10 positions to prepare for the next row.
            {
                printf("\n\n");
                alt = 1;
                iterLR -= 10;
            }
        }
        else //When alt is 1, the board is being printed from right to left (e.g., 81 to 90, 61 to 70).Inside this block, iterRL++ increases the value of iterRL, which moves from 80 up to 100.
        {
            iterRL++; // If iterRL matches the position of player 1 or player 2, their symbol is printed. Otherwise, the square number is printed.
            if (iterRL == player1_pos)
            {
                printf("#P1 ");
            }
            else if (iterRL == player2_pos)
            {
                printf("#P2 ");
            }
            else 
            {
                printf("%d ", board[iterRL]);
            }

            if (iterRL % 10 == 0) //If the current square (iterRL) is at the end of a row (i.e., divisible by 10 with no remainder, like 90, 80, etc.), a newline is printed, and alt is set to 0 to indicate that the next row should be printed from left to right. The iterRL -= 30 statement skips back 30 positions to align the board for the next row.
            {
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

int main()
{
    srand(time(0)); // Seed the random number generator with current time.This ensures that every time you run the game, the dice rolls will be different.
    int currentPlayer = 1; //currentPlayer = 1: Indicates that Player 1 starts the game.
    int won = 0; //won = 0: This variable tracks if the game has been won. The game continues to loop until won becomes 1.

    printf("Snake and Ladder Game\n");

    while (!won)
    {
        printf("\nPlayer %d, press Enter to roll the die...", currentPlayer);
        getchar(); // Wait for the player to press Enter
        int roll = Roll_Dice();
        printf("You rolled a %d.\n", roll);

        if (currentPlayer == 1)
        {
            int newPosition = Update_player_position(player1_pos, roll);
            if (newPosition == player1_pos) // If newPosition is the same as player1_pos, it means the player can't move (e.g., because the roll would take them past 100). In this case, a message is printed, and the player remains in the same position.
            {
                printf("Cannot move. You remain at square %d.\n", player1_pos);
            }
            else
            {
                player1_pos = newPosition; //If the player can move their position is updated and printed on the board
                printf("Player 1 is now at square %d.\n\n", player1_pos);
                board();
            }
            if (player1_pos == 100) //checks the won flag if its 1, and updates the winner
            {
                printf("Player 1 wins!\n");
                won = 1;
            }
        }
        else
        {
            int newPosition = Update_player_position(player2_pos, roll);
            if (newPosition == player2_pos)
            {
                printf("Cannot move. You remain at square %d.\n", player2_pos);
            }
            else
            {
                player2_pos = newPosition;
                printf("Player 2 is now at square %d.\n\n", player2_pos);
                board();
            }
            if (player2_pos == 100)
            {
                printf("Player 2 wins!\n");
                won = 1;
            }
        }
        currentPlayer = (currentPlayer == 1) ? 2 : 1; //After each turn, this line checks the condition of the current player, If currentPlayer was 1, it becomes 2; if it was 2, it becomes 1. This ensures that the next turn will belong to the other player.

    }

    return 0;
}
