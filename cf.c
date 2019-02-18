#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//return true if there is no empty index left in the array (i.e there are no moves left in the board) which will end the game in draw, false otherwise
bool isBoardFull(char currState[6][7])
{
  int row = 0;
  int column = 0;
  bool isFull = true;
  while (column <= 6)
  {
    if (currState[row][column] == '.')
    {
      isFull = false;
    }
    column++;
  }
  return isFull;
}

//return true if the row and column passed in are in the bounds of the board array, false otherwise
bool inRange(int row, int column)
{
  if ((row >= 0 && row < 6) && (column >= 0 && column < 7))
  {
    return true;
  }
  return false;
}

//return the corresponding index of the board of the column character passed in, false otherwise
//return -1 if invlaid column is passed in
int charToIndex(char column)
{
  int col = -1; // varialbe to store the column index in array
  switch (column)
  {
  case 'A':
    col = 0;
    break;
  case 'B':
    col = 1;
    break;
  case 'C':
    col = 2;
    break;
  case 'D':
    col = 3;
    break;
  case 'E':
    col = 4;
    break;
  case 'F':
    col = 5;
    break;
  case 'G':
    col = 6;
    break;
  default:
    return col;
  }
  return col; //if -1 is returned get a valid column OR we can validate input at the beginning
}

//prints the board
void printBoard(char currState[6][7])
{
  printf("   A  B  C  D  E  F  G  \n");
  //variable 'i' used to print the number of column
  //variable 'index' used as an index of the 2d array
  for (int i = 6, index = 0; i >= 1, index < 6; i--, index++)
  {
    printf("%i  ", i);
    for (int j = 0; j < 7; j++)
    {
      printf("%c  ", currState[index][j]);
    }
    printf("\n");
  }
}

//return true if the column passed in is full (has no space left), false otherwise.
bool isFull(int column, char currState[6][7])
{
  int row = 0; //row = 0 to only check the uppermost 
  if (currState[row][column] != '.')
  {
    return true;
  }
  return false;
}

//source used: https://www.geeksforgeeks.org/generating-random-number-range-c/
// Generates and returns a random move for AI
// numbers in range [lower, upper].
int AIRandoms(char currState[6][7])
{
  int move;
  while (true)
  {
    srand(time(0));
    move = (rand() % (7 - 0 + 1)) + 0;
    if (!isFull(move, currState))
    {
      break;
    }
  }
  return move;
}

//return true if the move is successfully added to the board, false otherwise
//col = column
bool add(int col, char currState[6][7], char c)
{
  int k = 5;
  if (isFull(col, currState))
  {
    return false;
  }
  else
  {
    //find the empty row in the column passed in.
    while (currState[k][col] != '.')
    {
      k--;
    }
  }
  currState[k][col] = c;
  printf("\n");
  printBoard(currState);
  return true;
}

//Finds the first non-empty spot in a column and returns the index where a move has already been made.
//returns the row index of the character
//return -1 if invalid column (col) passed.
int findrow(char currState[6][7], int col)
{
  if (!isFull(col, currState))
  {
    int colIndex = col;
    int k = 5;
    while (currState[k][colIndex] != '.')
    {
      k--;
    }
    return k + 1; //Added 1 to k to access the position 
  }
  return -1;
}

//******* A=0, B=1, C=2, D=3, E=4, F=5, G=6 ***********
//return true if a match of 4 horizontally(backward or forward) is found, false otherwise
bool checkHorizontal(char currState[6][7], int column, char player)
{
  int row = findrow(currState, column);
  int counter = 0; //counter variable for a match of 4

  //finding match horizontally in the backward direction
  int temp_currColumn = column;
  while ((currState[row][temp_currColumn] == player) && (counter != 4))
  {
    //break if index out of bounds
    if (temp_currColumn < 0)
    {
      break;
    }
    counter++;
    temp_currColumn--;
  }

  //making sure index out of bounds is not accessed
  if (column != 6)
  {
    // if the column is not G, add 1 to column because the current column is already checked
    temp_currColumn = column + 1;
    //finding match horizontally in the backward direction
    while ((currState[row][temp_currColumn] == player) && (counter != 4))
    {
      //break if index out of bounds
      if (temp_currColumn > 6)
      {
        break;
      }
      counter++;
      temp_currColumn++;
    }
  }

  //if a match of 4 is found (i.e counter == 4) return true, false otherwise
  if (counter == 4)
  {
    return true;
  }
  return false;
}

//return true if a match of 4 vertically(upwards or downwards) is found,  false otherwise
bool checkVertical(char currState[6][7], int column, char player)
{
  int row = findrow(currState, column);
  int counter = 0; //counter variable for a match of 4

  //fidning match vertically in the UPWARD direction
  int temp_currRow = row;
  while ((currState[temp_currRow][column] == player) && (counter != 4))
  {
    //break if index out of bounds
    if (temp_currRow < 0)
    {
      break;
    }
    counter++;
    temp_currRow--;
  }

  if (row != 5)
  {
    // if the ROW INDEX is not 5, add 1 to temp_currRow because the current ROW INDEX is already checked
    temp_currRow = row + 1;
    //fidning match vertically in the DOWNWARD direction
    while ((currState[temp_currRow][column] == player) && (counter != 4))
    {
      //break if index out of bounds
      if (temp_currRow > 5)
      {
        break;
      }
      counter++;
      temp_currRow++;
    }
  }

  //if a match of 4 is found (i.e counter == 4) return true, false otherwise
  if (counter == 4)
  {
    return true;
  }
  return false;
}

//return true if a match of 4 diagonally(SouthWest, NorthEast, SouthEast, NorthWest) is found, return false otherwise
bool checkDiagonal(char currState[6][7], int column, char player)
{
  int temp_currColumn = column;
  int row = findrow(currState, column);
  int temp_currRow = row;
  int counter = 0; //counter variable for a match of 4

  //DIAGONALS --> SW, NE, SE, NW

  //fidning match in the SouthWest direction
  while ((inRange(temp_currRow, temp_currColumn)) && (currState[temp_currRow][temp_currColumn] == player) && (counter != 4))
  {
    counter++;
    temp_currRow++;
    temp_currColumn--;
  }

  //fidning match in the NorthEast direction
  if (row != 0 && column != 6)
  {
    temp_currColumn = column + 1;
    temp_currRow = row - 1;
    temp_currColumn = column;
    while ((inRange(temp_currRow, temp_currColumn)) && (currState[temp_currRow][temp_currColumn] == player) && (counter != 4))
    {
      counter++;
      temp_currRow--;
      temp_currColumn++;
    }
  }

  if (counter >= 4)
  {
    return true;
  }

  //RESET TEMPERORY COLUMN AND ROW VARIABLES
  temp_currRow = row;
  temp_currColumn = column;
  counter = 0;

  //fidning match in the SouthEast direction
  while ((inRange(temp_currRow, temp_currColumn)) && (currState[temp_currRow][temp_currColumn] == player) && (counter != 4))
  {
    counter++;
    temp_currRow++;
    temp_currColumn++;
  }

  //fidning match in the NorthWest direction
  if (row != 0 && column != 0)
  {
    temp_currColumn = column - 1;
    temp_currRow = row - 1;
    while ((inRange(temp_currRow, temp_currColumn)) && (currState[temp_currRow][temp_currColumn] == player) && (counter != 4))
    {
      counter++;
      temp_currRow--;
      temp_currColumn--;
    }
  }

  if (counter >= 4)
  {
    return true;
  }

  return false;
}

bool won(char currState[6][7], int col, char player)
{
  return checkHorizontal(currState, col, player) || checkVertical(currState, col, player) || checkDiagonal(currState, col, player);
}

//return true if a match of 3 is found, false otherwise
//for AI attack and defense purposes
bool AIcheckHorizontal(char currState[6][7], int column, char player)
{
  int row = findrow(currState, column);
  int counter = 0;
  int temp_currColumn = column;

  //backward direction
  while ((currState[row][temp_currColumn] == player) && (counter != 3))
  {
    //break if index out of bounds
    if (temp_currColumn < 0)
    {
      break;
    }
    counter++;
    temp_currColumn--;
  }

  // if the column is not G, add 1 to column because the current column is already checked
  if (column != 6)
  {
    temp_currColumn = column + 1;
    //forward direction
    while ((currState[row][temp_currColumn] == player) && (counter != 3))
    {
      //break if index out of bounds
      if (temp_currColumn > 6)
      {
        break;
      }
      counter++;
      temp_currColumn++;
    }
  }
  if (counter == 3)
  {
    return true;
  }
  return false;
}

//return true if a match of 3 is found, false otherwise
//for AI attack and defense purposes
bool AIcheckVertical(char currState[6][7], int column, char player)
{
  int row = findrow(currState, column);
  char currPlayer = player;
  int counter = 0; //counter variable for a match of 4

  //fidning match vertically in the UPWARD direction
  int temp_currRow = row;
  while ((currState[temp_currRow][column] == player) && (counter != 4))
  {
    //break if index out of bounds
    if (temp_currRow < 0)
    {
      break;
    }
    counter++;
    temp_currRow--;
  }

  // if the ROW INDEX is not 5, add 1 to temp_currRow because the current ROW INDEX is already checked
  if (row != 5)
  {
    temp_currRow = row + 1;
    //DOWNWARD direction
    while ((currState[temp_currRow][column] == player) && (counter != 4))
    {
      //break if index out of bounds
      if (temp_currRow > 5)
      {
        break;
      }
      counter++;
      temp_currRow++;
    }
  }

  if (counter == 3)
  {
    return true;
  }
  return false;
}

//return true if a match of 3 is found, false otherwise
//for AI attack and defense purposes
bool AIcheckDiagonal(char currState[6][7], int column, char player)
{
  int temp_currColumn = column;
  int row = findrow(currState, column);
  int temp_currRow = row;
  int counter = 0; //counter variable for a match of 4

  //DIAGONALS --> SW, NE, SE, NW

  //fidning match in the SouthWest direction
  while ((inRange(temp_currRow, temp_currColumn)) && (currState[temp_currRow][temp_currColumn] == player) && (counter != 4))
  {
    counter++;
    temp_currRow++;
    temp_currColumn--;
  }

  //fidning match in the NorthEast direction
  if (row != 0 && column != 6)
  {
    temp_currColumn = column + 1;
    temp_currRow = row - 1;
    temp_currColumn = column;
    while ((inRange(temp_currRow, temp_currColumn)) && (currState[temp_currRow][temp_currColumn] == player) && (counter != 4))
    {
      counter++;
      temp_currRow--;
      temp_currColumn++;
    }
  }

  if (counter == 3)
  {
    return true;
  }

  //RESET TEMPERORY COLUMN AND ROW VARIABLES
  temp_currRow = row;
  temp_currColumn = column;
  counter = 0;

  //fidning match in the SouthEast direction
  while ((inRange(temp_currRow, temp_currColumn)) && (currState[temp_currRow][temp_currColumn] == player) && (counter != 4))
  {
    counter++;
    temp_currRow++;
    temp_currColumn++;
  }

  //fidning match in the NorthWest direction
  if (row != 0 && column != 0)
  {
    temp_currColumn = column - 1;
    temp_currRow = row - 1;
    while ((inRange(temp_currRow, temp_currColumn)) && (currState[temp_currRow][temp_currColumn] == player) && (counter != 4))
    {
      counter++;
      temp_currRow--;
      temp_currColumn--;
    }
  }

  if (counter == 3)
  {
    return true;
  }

  return false;
}

bool AIwon(char currState[6][7], int col, char player)
{
  return AIcheckHorizontal(currState, col, player) || AIcheckVertical(currState, col, player) || AIcheckDiagonal(currState, col, player);
}

//returns defence and attacking move or else random for default.
int AIturn(char currState[6][7])
{
  int move = AIRandoms(currState);
  for (int i = 0; i < 7; i++)
  {
    //making sure AI does not make a move out of board
    if (!isFull(i, currState))
    {
      if (AIwon(currState, i, 'X') || (AIwon(currState, i, 'O')))
      {
        move = i;
        break;
      }
    }
  }

  return move;
}

int main(void)
{
  //*************variables*******************
  char currState[6][7];  //current state of game
  char winner = ' ';     // 'P' for player, 'AI' for AI
  char column = ' ';     // Valid characters --> 'A - G'
  char currPlayer = ' '; //'p' for player, 'a' for AI
  //whoever goes first will be assigned X
  bool turn = false;
  char chr = ' ';

  //************$$$$$$$$$$$$$$$$$*************

  //Initialise Board
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      currState[i][j] = '.';
    }
  }
  printf("************************ \n");
  printf("************************ \n");
  printf("Welcome to Connect Four! \n");
  printf("************************ \n");
  printf("\n");
  printBoard(currState);
  printf("\n");
  char y_or_n = ' ';
  printf("Do want to go first?(Y/N)\n");
  printf("\n");
  scanf(" %c", &y_or_n);

  while (!isBoardFull(currState))
  {
    //P goes first
    if (y_or_n == 'Y' || y_or_n == 'y')
    {
      if (turn == false) //player is false (p's turn)
      {
        char w = ' ';
        printf("Where do you want to go(A-G)?\n");
        scanf(" %c", &w);

        int colm = charToIndex(w);
        if (colm == -1)
        {
          printf("INVALID!! Please enter columns A->G \n");
          printf("Where do you want to go(A-G)?\n");
          while (true)
          {

            scanf("%c", &w);
            colm = charToIndex(w);
            if (w == 'A' || w == 'B' || w == 'C' || w == 'D' || w == 'E' || w == 'F' || w == 'G')
              break;
          }
        }

        if (isFull(colm, currState))
        {
          printf("Column full!!!\n");
          printf("Please Enter Again\n");
          while (true)
          {
            scanf("%c", &w);
            colm = charToIndex(w);
            if (!isFull(colm, currState))
              break;
          }
        }
        colm = charToIndex(w);
        add(colm, currState, 'X');
        if (won(currState, colm, 'X') == true)
        {
          printf("Player X won\n");
          break;
        }
        printf("\n");
      }

      else //AI is true (AI's turn)
      {
        printf("AI's turn\n");
        int aiMove = AIturn(currState);
        add(aiMove, currState, 'O');
        if (won(currState, aiMove, 'O'))
        {
          printf("Player O won (AI WON) \n");
          break;
        }
      }
    }

    //AI goes first
    else
    {
      if (turn == false) //AI is false AI's turn
      {
        printf("AI's turn\n");
        int aiMove = AIturn(currState);
        add(aiMove, currState, 'X');
        if (won(currState, aiMove, 'X') == true)
        {
          printf("Player X won (AI WON)\n");
          break;
        }
      }
      else //Player is true
      {
        printf("Where do you want to go(A-G)?\n");
        char w = ' ';
        scanf(" %c", &w);
        int colm = charToIndex(w);

        if (isFull(colm, currState))
        {
          printf("Column Full!!!\n");
          while (true)
          {
            printf("Please Enter Again\n");
            scanf("%c", &w);
            colm = charToIndex(w);
            if (!isFull(colm, currState))
              break;
          }
        }
        colm = charToIndex(w);
        add(colm, currState, 'O');
        if (won(currState, colm, 'O') == true)
        {
          printf("Player O won\n");
          break;
        }
      }
    }
    turn = !turn;
    printf("\n");
  }
  printf("\n");
  printf("*****GAME OVER *****");
  printf("\n");
  return 0;
}