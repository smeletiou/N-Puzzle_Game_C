/**
 * @file Npuzzle.c
 * @author Sotiris Rafail Meletiou .
 * @brief N-Puzzle game HW1 project for EPL232.
 * 
 * The size of the game depends on the number that N has on the definition
 * Game starts after the right file is inserted by the user 
 * Goal is to put all the numbers in asceding order exept the number 0 
 * that has to go to the bottom right corner 
 * aster that the game is finished.
 *
 * 
 * @copyright Copyright (c) 2021.
 * @bug if you spam multiple chars in the same line of input or you press enter by mistake without input 
 * there is a chance that it will get stuck and cannot be close by E-e an you have to press enter a few times to get fixed.
 */
/* definition of libs*/
#include <stdio.h>
#include <stdlib.h>

/* definition of game size*/
#define N 3

/* definition of the functions */
char User_Input(void);
void Play(int grid[N][N]);
void swap(int grid[N][N], char input);
int moveValidity(int grid[N][N], char input);
int getY(int grid[N][N]);
int getX(int grid[N][N]);
int isSolution(int grid[N][N]);
void readPuzzle(char **argv, int grid[N][N], FILE *fp);
void displayPuzzle(int grid[N][N]);
int isValidNPuzzle(FILE *fp);
//////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief  Main function. 
 * 
 * Entry point 
 * reads the arguments given by the user
 * and gives them to the corresponting functions to run
 * and start the game.
 * 
 * @param argc is the length of the input from the user into the terminal.
 * @param argv is the file with the board of the game.
 * @return int 
 */
int main(int argc, char **argv)
{
  FILE *fp;
  int grid[N][N];
  char input;
  if (argc < 2)
  {
    printf("Usage: \n");
    printf("./Npuzzle <inputfile>\n");
    exit(1);
  }

  readPuzzle(argv, grid, fp);
  Play(grid);
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief  User input-Moves.
 *  reads the moves of the user .
 * @return char returns the character that is the input.
 */
char User_Input(void)
{
  char input;

  printf("Move : ");
  scanf("%c", &input);
  getchar();

  while (!(input == 'u' || input == 'U' || input == 'd' ||
           input == 'D' || input == 'l' || input == 'L' ||
           input == 'r' || input == 'R' || input == 'e' || input == 'E'))
  {
    printf("Wrong input : direction is one of: l(left), r(right), u(up), d(down), e(exit)\n");
    printf("Move : ");
    scanf("%c", &input);
    getchar();
  }

  return input;
}

/**
 * @brief Saves ths Puzzle.
 * creates a file after the game is finished
 * or stopped by the user 
 * and saves the grid of the game for future use.
 * 
 * @param grid the game board with the numbers in it
 */
void writePuzzle(int grid[N][N])
{
  FILE *output;
  int i, j;
  output = fopen("output.txt", "w");
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
      if (j != N - 1)
        fprintf(output, "%d   ", grid[i][j]);
      else
        fprintf(output, "%d", grid[i][j]);

    fprintf(output, " \n");
  }
  fclose(output);
}

/**
 * @brief Game.
 * This is where the game is ran
 * calls all the functions tha ara needed for the game.
 * 
 * @param grid game board.
 */
void Play(int grid[N][N])
{
  char input;
  int valid = 0;
  int win = 0;

  printf("Enter your command in the following format:\n");
  printf("Move : direction\n");
  printf("Notice: move> is the user prompt \ndirection is one of: l(left), r(right), u(up), d(down), e(exit)\n");

  displayPuzzle(grid);

  do
  {
    do
    {
      input = User_Input();
    } while ((valid = moveValidity(grid, input)) == 0);
    if (input != 'e' || input != 'E')
      swap(grid, input);

    displayPuzzle(grid);

  } while ((win = isSolution(grid)) != 1 && (input != 'e' && input != 'E'));

  writePuzzle(grid);
  printf("Saving out-test%dx%d.txt...Done\n", N, N);
  printf("Bye\n");
}

/**
 * @brief Swap function.
 * It swaps the (zero) on the board 
 * with the cell that was corresponding to the move 
 * that the user gave
 * The move needs to be verified by the 
 * MoveValidity function.
 * 
 * @param grid game board.
 * @param input move.
 */
void swap(int grid[N][N], char input)
{
  int X, Y, temp;
  X = getX(grid);
  Y = getY(grid);
  switch (input)
  {

  case 'l':
  case 'L':
    temp = grid[X][Y];
    grid[X][Y] = grid[X][Y - 1];
    grid[X][Y - 1] = temp;
    break;
  case 'r':
  case 'R':
    temp = grid[X][Y];
    grid[X][Y] = grid[X][Y + 1];
    grid[X][Y + 1] = temp;
    break;
  case 'u':
  case 'U':
    temp = grid[X][Y];
    grid[X][Y] = grid[X - 1][Y];
    grid[X - 1][Y] = temp;
    break;
  case 'd':
  case 'D':
    temp = grid[X][Y];
    grid[X][Y] = grid[X + 1][Y];
    grid[X + 1][Y] = temp;
    break;
  }
}

/**
 * @brief Move validation.
 * It checks if the move that the user gave is valid 
 * that is that the given move doesnt go out of bounds
 * If this funtion returns true only then the Swap can work.
 * 
 * @param grid game board .
 * @param input move.
 * @return int true - false.
 */
int moveValidity(int grid[N][N], char input)
{
  int X, Y;
  X = getX(grid);
  Y = getY(grid);

  switch (input)
  {
  case 'l':
  case 'L':
    if (Y != 0)
      return 1;
    else
    {
      printf("Invalid Move\n");
      return 0;
    }
    break;
  case 'r':
  case 'R':
    if (Y != N - 1)
      return 1;
    else
    {
      printf("Invalid Move\n");
      return 0;
    }
    break;
  case 'u':
  case 'U':
    if (X != 0)
      return 1;
    else
    {
      printf("Invalid Move\n");
      return 0;
    }
    break;
  case 'd':
  case 'D':
    if (X != N - 1)
      return 1;
    else
    {
      printf("Invalid Move\n");
      return 0;
    }
    break;
  case 'e':
  case 'E':
    return 1;
    break;
  }
}

/**
 * @brief Finds Y.
 * 
 * finds the Y position of (zero).
 * @param grid game board.
 * @return int returns Y.
 */
int getY(int grid[N][N])
{
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      if (grid[i][j] == 0)
        return j;
}

/**
 * @brief Finds X.
 * finds the X lposition of (zero).
 * @param grid game board.
 * @return int  returns X.
 */
int getX(int grid[N][N])
{
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      if (grid[i][j] == 0)
        return i;
}

/**
 * @brief Check if solved.
 * checks if the board is solved
 * By seeing if the numbers are in ascending order.
 * 
 * @param grid game board 
 * @return int true(1)-false(0) 
 */
int isSolution(int grid[N][N])
{
  int i, j, isAscending = 0;
  for (i = 0; i < N; i++)
    for (j = 0; j < N - 1; j++)
    {
      if (i == N - 1 && j == N - 2 && grid[i][j + 1] == 0)
        break;
      else if ((j != N - 2 && grid[i][j] > grid[i][j + 1]) || (j == N - 2 && ((grid[i][j] > grid[i][j + 1]) || (grid[i][j + 1] > grid[i + 1][0]))))
        isAscending = 1;
    }
  if (grid[N - 1][N - 1] == 0 && isAscending == 0)
  {
    printf("Congratulations , you solved the %d-puzzle\n", N);
    return 1;
  }
  else
    return 0;
}

/**
 * @brief Puzzle validity.
 * checks if the user gave the correct file
 * for the corresponding N .
 * 
 * @param fp file.
 * @return int true-false 
 */
int isValidNPuzzle(FILE *fp)
{
  int i = 0, j, t, Odigit = 0, Ddigit = 0, temp, nums = 0, other = 0, ZeroFound = 0;
  char ch;

  fseek(fp, 0, SEEK_END); //finds the end of the file
  int size = ftell(fp);   //saves the size of the file
  fseek(fp, 0, SEEK_SET); //resets the file to the beggining
  int tab[size];          //creates a tab with the size of the file

  while ((ch = fgetc(fp)) != EOF)
  {
    tab[i] = ch;
    //printf("%d ", tab[i]);
    i++;
  }

  for (t = 0; t < size - 1; t++)
    if ((tab[t] > 47 && tab[t] < 58 && (tab[t + 1] > 47 && tab[t + 1] < 58)))
      Ddigit++;

  for (j = 0; j < size; j++)
  {
    if (tab[j] > 48 && tab[j] < 58)
      nums++;
    else if (tab[j] == 48)
      ZeroFound++;
    else if (tab[j] != '\n' && tab[j] != 9 && tab[j] != 10 && tab[j] != 32 && (tab[j] < 48 || tab[j] > 57))
    {
      printf("%c \n", tab[j]);
      other++;
    }
  }
  Odigit = nums+ZeroFound - 2 * Ddigit;
  printf("nums %d others %d zero %d ddigit %d odigit %d\n", nums, other, ZeroFound, Ddigit, Odigit);
  if (N * N > 9)
  {
    if (Odigit > 10 || Ddigit < N * N - 10  ||other!=0|| ZeroFound == 0)
    {
      printf("Error:File does not have the correct format for a %dx%d puzzle\n", N, N);
      printf("Please load a correct file\n");
      exit(1);
    }
  }
  else
  {
    if (nums > N * N || ZeroFound == 0 || other != 0)
    {
      printf("Error:File does not have the correct format for a %dx%d puzzle\n", N, N);
      printf("Please load a correct file\n");
      exit(1);
    }
  }
  fclose(fp);
  return 1;
}

/**
 * @brief Reads the puzzle.
 * reads the puzzle from the file
 * and inserts it into the game board.
 * 
 * @param argv file location on the terminal input.
 * @param grid game board.
 * @param fp file.
 */
void readPuzzle(char **argv, int grid[N][N], FILE *fp)
{

  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    printf("Error:File cannot be opened\n");
    exit(-1);
  }

  int valid = 0;
  valid = isValidNPuzzle(fp);
  if (valid == 1)
  {
    fp = fopen(argv[1], "r");

    int i, j;
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
        fscanf(fp, "%d", &grid[i][j]);
  }
  int x1, x2, y1, y2;
  for (x1 = 0; x1 < N; x1++)
    for (y1 = 0; y1 < N; y1++)
      for (x2 = 0; x2 < N; x2++)
        for (y2 = y1 + 1; y2 < N; y2++)
          if (grid[x1][y1] == grid[x2][y2])
          {
            printf("Error:File has duplicates in it\n");
            printf("Please load a correct file\n");
            exit(1);
          }

  for (x1 = 0; x1 < N; x1++)
    for (y1 = 0; y1 < N; y1++)
      if (grid[x1][y1] > N * N)
      {
        printf("Error:File doesnt have correct values for a %dx%d puzzle\n", N, N);
        printf("Please load a correct file\n");
        exit(1);
      }
  fclose(fp);
}

/**
 * @brief Displays the Puzzle.
 * prints the game board with the numbers in it 
 * to the begining and after every move.
 * @param grid game board.
 */
void displayPuzzle(int grid[N][N])
{
  int i, j;
  for (i = 0; i < N; i++)
  {
    /* Draw Top */
    for (j = 0; j < N; j++)
      printf("+---");
    printf("+\n");

    /* Draw Middle */
    for (j = 0; j < N; j++)
      if (grid[i][j] == 0)
      {
        printf("|");
        printf("\033[0;31m");
        printf("%2d ", grid[i][j]);
        printf("\033[0m");
      }
      else
        printf("|%2d ", grid[i][j]);
    printf("|\n");
  }

  /* Draw Bottom */
  for (j = 0; j < N; j++)
    printf("+---");
  printf("+\n");
}