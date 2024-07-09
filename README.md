/**
@mainpage EPL232 HomeWork1 

@author Sotiris Rafail Meletiou 

The program starts by calling the name of it in the terminal folowing by a txt file with the numbers that would fill the board.
The game size can be adjusted accordingly by the definition of N 

Bugs:if you spam multiple chars in the same line of input or you press enter by mistake without input there is a chance that it will get stuck and cannot be close by E-e an you have to press enter a few times to fix the problem and continue the game.

The game :
This game is a NxN puzzle with numbers from 0--(N*N)-1
the goal is to put all the numbers in ascending order with the number zero being at the last cell of the board.
When all the numbers are in ascending order and the 0 is last the game is finished.

Start:
The code starts with the input of a txt file from the user. 
Then the readPuzzle function checks if the file exist and then sends it to the isValidNPuzzle function.

(This function is the most complicated in the program so i will give a more explenation)

First we find the length of the file with fseek and we create a temporary tab with its length.
There the contents of the file are imported on the temp table in ascii form to be checked.
This routine checks every ascii character from 0-255 and counts the amount of digits,zeros and other characters from the ascii code.
Then because ascii doesnt save double digits as one number but it saves them as two ex. 10 is saved as 1 and 0 the next routine finds which characters are from a double digit number by looking in the table if the are two continuous cells with numbers that are not seperated by space or tab.
Then depended on the N the are different checkpoints with different variables.
for n>3 it checks if the are the right amount o onedigit and two digit numbers and there are not any other character in the file.
If nothing wrong was found the the function returns 1 so the file has the correct format.

Then the readPuzzle function imports all the numbers in the game board 
and after that there are two more checks.
The duplicate number check and the correct value check.
The duplicate check finds if there are more than one of the same number in the board
and the correct value is that there are the correct numbers in the game board for example for N=3 the numbers must be from 0-8.
After all this checks the game can start.

Play
The play function has a loop that is repeated until the user has finished the game or gave as an input (exit).
User input is check to see if it is one of the 5 correct characters and then a check of the move is in place o a repeat until the user gives a valid move (not out of bounds).
Then if the move is valid it mades the swap with the corresponding move.
The moves are made by finding first the X and Y of 0 and swaps it with the corresponding move.
Then if all numbers are in ascending order the game ends and the board is saved in an output file.

**/