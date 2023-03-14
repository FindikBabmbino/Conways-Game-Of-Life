#include<iostream>
#include<ctime>
#include <Windows.h>

/*
	----------------------------MADE BY Sinan Berk Karaagac ----------------------------
								Date(DD/MM/YY): 14/12/2023
	------------------------------------------------------------------------------------
*/

//These control how big the grid is going to be.
const int NUMBER_OF_COLUMNS = 20;
const int NUMBER_OF_ROWS = 20;

//These are the states the cells can have.
const int ALIVE_CELL = 1;
const int DEAD_CELL = 0;

//Characters of the cells to render depending on the state.
const char ALIVE_CELL_CHAR = '#';
const char DEAD_CELL_CHAR = ' ';

void StartGrid(int (&gameGrid)[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS]);

void CheckGrid(int (&gameGrid)[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS]);
void CheckCell(int(&gameGrid)[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS], int column, int row);

void DrawGrid(int gameGrid [NUMBER_OF_COLUMNS][NUMBER_OF_ROWS]);

int main()
{
	/*Each time you start the project the array is filled randomly you can disable 
	StartGrid function and make your own patterns */
	srand(time(NULL));

	int gameGrid[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS];
	StartGrid(gameGrid);

	while (true)
	{
		//Sleep controls how often the game is going to be rendered.
		Sleep(200);
		//We do this to clear the console and write the new iteration 
		system("cls");
		CheckGrid(gameGrid);
		DrawGrid(gameGrid);
	}

}

void StartGrid(int(&gameGrid)[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS])
{
	//This fills the grid in with random 1s and 0s. You can stop calling this at the start of main and create your own patterns
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		for (int k = 0; k < NUMBER_OF_ROWS; k++)
		{
			gameGrid[i][k] = rand() % 2;
		}
	}
}

void CheckGrid(int(&gameGrid)[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS])
{
	//This loops through the grid and checks all values.
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		for (int k = 0; k < NUMBER_OF_ROWS; k++)
		{
			//We send all of the values to checkcell function
			CheckCell(gameGrid, i, k);
		}
	}
}

void CheckCell(int (&gameGrid) [NUMBER_OF_COLUMNS][NUMBER_OF_ROWS], int column, int row)
{
	/*
		Now we get the current column and row to know which cell we want to evaluate.
		Since we need to check 8 neighbours we create a neigboursChecked var that ticks down each time we check a neighbour.
		Also we are going to move through the rows and columns to check so we create currentColumn and currentRow to keep track of it.
		liveNeighbours variable dictates if the current cell is going to die, be reborn or stay alive.
	*/
	int neighboursChecked = 8;

	int currentColumn = column;
	int currentRow = row;

	int liveNeighbours = 0;
	while (neighboursChecked > 0)
	{

		/*
			Movement of the rows and columns depends on what value is the neigbourChecked. 
			We first start in the same column go forwards and backwards.
			Then we move a column up and check all of that.
			After that we go 2 columns down and check that.
		*/
		switch (neighboursChecked)
		{
		case 8:
			currentRow++;
			break;
		case 7:
			currentRow -= 2;
			break;
		case 6:
			currentColumn--;
			break;
		case 5:
			currentRow++;
			break;
		case 4:
			currentRow++;
			break;
		case 3:
			currentColumn += 2;
			break;
		case 2:
			currentRow--;
			break;
		case 1:
			currentRow--;
			break;
		}

		/*
			Since we only check if the value is 1 we don't really have to check for null arrays.
			Not really safe but it works :)
		*/
		if (gameGrid[currentColumn][currentRow] == 1) liveNeighbours++;
		
		neighboursChecked--;
	}

	/*
		Here we check if the cell is going to die or live. This is based on the rules defined by the game.

			Any live cell with fewer than two live neighbours dies, as if by underpopulation.
			Any live cell with two or three live neighbours lives on to the next generation.
			Any live cell with more than three live neighbours dies, as if by overpopulation.
			Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction

		This description of the rules were taken from https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
	*/


	if (liveNeighbours < 2|| liveNeighbours > 3)
	{
		gameGrid[column][row] = DEAD_CELL;
	}
	else if(gameGrid[column][row] == DEAD_CELL && liveNeighbours == 3)
	{
		gameGrid[column][row] = ALIVE_CELL;
	}
	else if(gameGrid[column][row] == ALIVE_CELL && liveNeighbours == 2 || liveNeighbours == 3)
	{
		gameGrid[column][row] = ALIVE_CELL;
	} 
}
void DrawGrid(int gameGrid[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS])
{
	//This function draws the grid.
	for (int i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		for (int k = 0; k < NUMBER_OF_ROWS; k++)
		{
			//We place characters we defined to the values.
			if (gameGrid[i][k] == DEAD_CELL) std::cout << DEAD_CELL_CHAR;
			else std::cout << ALIVE_CELL_CHAR;
		}
		std::cout << '\n';
	}
}