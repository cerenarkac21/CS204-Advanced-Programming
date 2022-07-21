/******************************************************************************
Purpose: The Minesweeper in a simplified form as indicated in CS 204 HW#1
Author: Ceren Arkac
Date: 10/12/2021

*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // for setw
#include "randgen.h" // for RandInt

using namespace std;


void PrintMatrix(const vector <vector<char>> & mat){  // as we did in the lecture
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[0].size(); j++)
		{
			cout << setw(4) << mat[i][j];
		}
		cout << endl;
	}

}
/**************************************************************************************
After nrMines is given by the user, bombs are settled to the matrix consisting of Xs.
***************************************************************************************/

void SettleBombs(int nrMines, int row, int col, vector <vector<char>> & mat){ 
	for (int i = 0; i < nrMines; i++)
	{
		int randForRow, randForCol; 
		RandGen gen;
		randForRow = gen.RandInt(0,row-1);
		randForCol = gen.RandInt(0, col-1);

		bool unique = mat[randForRow][randForCol] != 'B';
		while (unique == false)
		{
			randForRow = gen.RandInt(0,row-1);
			randForCol = gen.RandInt(0, col-1);
			unique = mat[randForRow][randForCol] != 'B';
		}
		mat[randForRow][randForCol] = 'B';
	}
}


bool BombCheck(const vector <vector<char>> & mat, int row, int col){
	if (mat[row][col] == 'B'){
		return true;
	}
	else
	{
		return false;
	}
}

/***********************************************************************
This function was created to be used in SettleNums. 
It checks if (rowCoor, colCoor) is a real coordinate for the matrix mat.
************************************************************************/
bool CoorCheckForNums(int rowCoor, int colCoor, const vector <vector<char>> & mat){
	if ((0 <= rowCoor) &&  (rowCoor < mat.size()) && (0 <= colCoor) && (colCoor < mat[0].size()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*****************************************************************************
This function checks all of the 8 possible neighbooring cells for a cell. 
It finds the real neighbooring cells thanks to CoorCheckForNums
and if the neighbooring cells includes bomb and that bomb is not its own bomb, 
num is incremented by one and at the end of checking 8 cells, 
num is assigned to cell's value on matToUpdate.
Finally, matToUpdate consists of only nums.
*******************************************************************************/
void SettleNums(const vector <vector<char>> & matWXsandBs, int the_row, int the_col, vector <vector<char>> & matToUpdate){
	int num = 0;
	bool isBomb = false ;

	for (int i = the_row-1; i <= the_row+1; i++)
	{
		for (int j = the_col-1; j <= the_col+1; j++)
		{
			bool realCoor = CoorCheckForNums(i, j, matToUpdate);
			if (realCoor)
			{
				isBomb = BombCheck(matWXsandBs, i, j);

				if (isBomb && ((i != the_row) || (j != the_col))){
					num+=1;
				}
			}
		}
		
	}


	char c  = char(num + '0'); // converts num to char because I want to assign this num to my matrix which is a matrix for chars.
	matToUpdate[the_row][the_col] = c;
	
}

/**************************************************************
This function serves choice 1.
It takes the data from matToUpdate and prints it to matToShow.
***************************************************************/
int DisplaySurrounding(vector <vector<char>> & matToShow, int rowCoor, int colCoor, const vector <vector<char>> & matToUpdate){
	for (int i = 0; i < matToShow.size(); i++)
	{
		for (int j = 0; j < matToShow[0].size(); j++)
		{
			if (i == rowCoor && j == colCoor)
			{
				matToShow[rowCoor][colCoor] = matToUpdate[rowCoor][colCoor];
			}
			cout << setw(4) << matToShow[i][j];
		}
		cout << endl;

	}
	int numSurrounding  = int(matToUpdate[rowCoor][colCoor] - '0'); // another type casting
	return numSurrounding;

}
/**********************************************************************
This function checks matWBsandNums matrix and according to that matrix, 
show user the values as the user opens cells.
***********************************************************************/
void OpenCell(const vector <vector<char>> & matWBsandNums, int rowCoor, int colCoor, vector <vector<char>> & matToShowPlayer, bool & bombChosen){
	for (int i = 0; i < matToShowPlayer.size(); i++)
	{
		for (int j = 0; j < matToShowPlayer[0].size(); j++)
		{
			if (i == rowCoor && j == colCoor) // takes data from matWBsandNums
			{
				matToShowPlayer[rowCoor][colCoor] = matWBsandNums[rowCoor][colCoor];
			}
			cout << setw(4) << matToShowPlayer[i][j];
		}
		cout << endl;
	}
	if (matToShowPlayer[rowCoor][colCoor] == 'B') //chech wether given coordinate is a bomb
	{
		bombChosen = true; // if the chosen coordinate is a bomb, the user looses.
		cout << "Unfortunately, you stepped on a mine"  << endl;
		cout << "Arrangement of mines: " << endl;
		PrintMatrix(matWBsandNums);
		cout << ">>>>> Game Over! <<<<<" << endl;
	}
}

/*********************************************************************
This function is wandering all coordinates to call SettleNums function.
**********************************************************************/
void SettleAllNums(const vector <vector<char>> & mat, vector <vector<char>> & matToUpdate){
	for (int i = 0; i < matToUpdate.size(); i++)
	{
		for (int j = 0; j < matToUpdate[0].size(); j++)
		{
			SettleNums(mat, i, j, matToUpdate);
		}
	}

}

/***************************************************************************************
This CoorCheck checks the coordinates given by the user whether it is a real coordinate.
****************************************************************************************/
void CoorCheck(int & rowCoor, int & colCoor, const vector <vector<char>> & mat, bool & realCoor){
	if ((rowCoor >= mat.size()) || (colCoor >= mat[0].size()))
	{
		cout << "It is out of range. Please give a valid coordinates: ";

		cin >> rowCoor >> colCoor;
		CoorCheck(rowCoor, colCoor, mat, realCoor); // recursion. 
		// until user gives real coordinates, it continues to take input from the user.
	}
	realCoor = true;
}


/***************************************************************************
This function swap Xs with numbers and makes mat including Bs and nums
****************************************************************************/
void MatWithBsandNums(const vector <vector<char>> & matToDisplay, vector <vector<char>> & mat){
	for (int i = 0; i < matToDisplay.size(); i++)
	{
		for (int j = 0; j < matToDisplay[0].size(); j++)
		{
			if (mat[i][j] != 'B')
			{
				mat[i][j] = matToDisplay[i][j];
			}
		}
	}

}


/*********************************************************************
To user wins, if I have a bomb, all of the cells except these bombs 
should have been opened by the user on the matrix the user will see.
**********************************************************************/
void isWin(const vector <vector<char>> & matToShowPlayer, const vector <vector<char>> & matWNumsandBs, bool & win){
	win = true;
	for (int i = 0; i < matToShowPlayer.size(); i++)
	{
		for (int j = 0; j < matToShowPlayer[0].size(); j++)
		{
			if (matWNumsandBs[i][j] != 'B') 
			{
				if (matToShowPlayer[i][j] == 'X')
				{
					win = false;
				}

			}
		}
	}

}


int main(){
	int row, col, nrMines;
	bool nrMinesCheck = false;
	cout << "Give the dimensions of the matrix: ";
	cin >> row >> col;
	vector <vector<char>> matToShowPlayer(row, vector<char>(col, 'X')); // user will always see this matrix with adjustmnets.
	vector <vector<char>> matWBsandNums(row, vector<char>(col, 'X')); // eventually, this matrix will consists of the numbers of neighboring cells for each cell and Bs if a cell is mine . 
	vector <vector<char>> matToUpdate(row, vector<char>(col)); // this matrix is mainly created to be used in choice 1. it will involves only numbers, i.e. bomb are also numbers. 


	cout << "How many bombs: ";
	cin >> nrMines;
	while ((nrMines < 1) || (nrMines >= (row*col))) // checking the correct range for the number of mines which is taken from user.
	{
		while (nrMines >= (row*col))
		{
			cout << "The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
			cin >> nrMines;
		}

		while (nrMines < 1)
		{
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin >> nrMines;
		}
	}

	PrintMatrix(matToShowPlayer); // starting matrix (with Xs)
	cout << endl;
	SettleBombs(nrMines, row, col, matWBsandNums); // matWBsandNums consists of Xs and Bs now.
	SettleAllNums(matWBsandNums, matToUpdate); // matToUpdate consists of only numbers now.
	MatWithBsandNums(matToUpdate, matWBsandNums); // matWBsandNums consists of Bs and numbers now.

	bool bombChosen = false;
	bool win = false;
	string choice = ""; // choice should be string because user can give characters such as @.
	while (choice != "3" && (bombChosen == false) && (win == false))
	{
		cout << endl;
		cout << "Press:" << endl;
		cout << "1. If you want to find out the surrounding of a cell" << endl;
		cout << "2. If you want to open the cell" << endl;
		cout << "3. If you want to exit." << endl;
		cin >> choice;
		if (choice == "1")
		{
			int rowCoortoDisplay, colCoortoDisplay;
			bool realCoor = false;
			cout << "Give the coordinates: ";
			cin >> rowCoortoDisplay >> colCoortoDisplay;
			CoorCheck(rowCoortoDisplay, colCoortoDisplay, matWBsandNums, realCoor);
			if (realCoor)
			{
				cout << "Displaying the surrounding of (" << rowCoortoDisplay <<"," << colCoortoDisplay << "):" << endl;
				int numSurrounding;
				bool openedBefore = matToShowPlayer[rowCoortoDisplay][colCoortoDisplay] != 'X';
				numSurrounding = DisplaySurrounding(matToShowPlayer, rowCoortoDisplay, colCoortoDisplay, matToUpdate);
				cout << "Around (" << rowCoortoDisplay << "," << colCoortoDisplay << ") you have " << numSurrounding << " bomb(s)" << endl;
				if (openedBefore == false)
				{
					matToShowPlayer[rowCoortoDisplay][colCoortoDisplay] = 'X';
				}
			}
			
		}
		else if(choice == "2")
		{
			int rowCoortoOpen, colCoortoOpen;
			bool realCoor = false;
			cout << "Give the coordinates: ";
			cin >> rowCoortoOpen >> colCoortoOpen;
			CoorCheck(rowCoortoOpen, colCoortoOpen, matWBsandNums, realCoor);
			if (realCoor)
			{
				cout << "Opening cell (" << rowCoortoOpen << "," << colCoortoOpen << "): " << endl;
				OpenCell(matWBsandNums, rowCoortoOpen, colCoortoOpen, matToShowPlayer, bombChosen);
				isWin(matToShowPlayer, matWBsandNums, win);
				if (win)
				{
					cout << "Congratulations! All the non-mined cells opened successfully" << endl;
					cout << "You won!" << endl;
					cout << ">>>>> Game Over! <<<<<" << endl;
				}
			}
		}
		else if(choice == "3")
		{
			cout << "Program exiting ..." << endl;
		}
		else
		{
			cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
		}
	}
	
	return 0;
}
