#include <set>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Sudoku.h"

/*********Sudoku***********
constructs a Sudoku object with a string as input for hints
@param hints - the input sudoku game
**************************/
Sudoku::Sudoku(string hints)
{
	for (int i = 0; i < 9; i++)
		hintValues[i] = 0;
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (hints[row * 9 + col] != '0')
			{
				sudokuMatrix[row][col].value = hints[row * 9 + col];
				sudokuMatrix[row][col].isHint = true;
				hintValues[hints[row * 9 + col] - 49]++;
			}
		}
	}
}
/*********display********
prints out the sudoku game to the console
************************/
void Sudoku::display() const
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			cout << '|' << sudokuMatrix[row][col].value;
		}
		cout << '|' << endl;
	}
}

/**********randomize**********
randomly fills the sudoku with values from 1-9 (9 each)
*****************************/
void Sudoku::randomize()
{
	vector<int> valuesToShuffle;
	for(int i = 0; i < 9; i++)
	{
		for(int j = hintValues[i]; j < 9; j++)
			valuesToShuffle.push_back(i + 1);
	}
	random_shuffle (valuesToShuffle.begin(), valuesToShuffle.end());
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (!sudokuMatrix[row][col].isHint)
			{
				sudokuMatrix[row][col].value = valuesToShuffle[0] + 48;
				valuesToShuffle.erase(valuesToShuffle.begin());
			}
		}
	}
}

/********validate**********
checks if solution is valid
@return - true if solution is valid, false otherwise
**************************/
bool Sudoku::validate() const
{
	bool matches[9] = { false, false, false, false, false, false, false, false, false };
	// Check if rows have errors
    for (unsigned int i = 0; i < 9; ++i)
    {
        for (unsigned int j = 0; j < 9; ++j)
        {
            if (!matches[sudokuMatrix[i][j].value - 49])
                matches[sudokuMatrix[i][j].value - 49] = true;
            else
                return false;
        }
        for (unsigned int j = 0; j < 9; ++j)
            matches[j] = false;
    }
	// Check if columns have errors
    for (unsigned int i = 0; i < 9; ++i)
    {
        for (unsigned int j = 0; j < 9; ++j)
        {
            if (!matches[sudokuMatrix[j][i].value - 49])
                matches[sudokuMatrix[j][i].value - 49] = true;
            else
                return false;
        }
        for (unsigned int j = 0; j < 9; ++j)
            matches[j] = false;
    }
	// Check if 3x3s have errors
    for (unsigned int I = 0; I < 3; ++I)
    {
        for (unsigned int J = 0; J < 3; ++J)
        {
            for (unsigned int i = 3 * I; i < 3 * I + 3; ++i)
            {
                for (unsigned int j = 3 * J; j < 3 * J + 3; ++j)
                {
                    if (!matches[sudokuMatrix[i][j].value - 49])
                        matches[sudokuMatrix[i][j].value - 49] = true;
                    else
                        return false;
                }
            }
            for (unsigned int j = 0; j < 9; ++j)
                matches[j] = false;
        }
    }
    return true;
}

/******printValidity*****
prints a statement to the console about the validity of the solution
************************/
void Sudoku::printValidity() const
{
	cout << "This solution is ";
	if (!validate())
		cout << "not ";
	cout << "valid." << endl;
}
/*****shuffleErrors******
shuffles the nodes that cause the most errors around with each other
finds all the errors and assigns an errorCount value
@return - the sum of each of the values shuffled
*////////////////////////
int Sudoku::shuffleErrors()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			sudokuMatrix[row][col].errorCount = 0;
		}
	}
	int highestErrorCount = 0;
	bool matches[9] = { false, false, false, false, false, false, false, false, false };
	// Check if rows have errors
    for (unsigned int i = 0; i < 9; ++i)
    {
        for (unsigned int j = 0; j < 9; ++j)
        {
            if (!matches[sudokuMatrix[i][j].value - 49])
                matches[sudokuMatrix[i][j].value - 49] = true;
            else
			{
				for (int col = 0; col < j; col++)
				{
					if (sudokuMatrix[i][j].value == sudokuMatrix[i][col].value)
					{
						sudokuMatrix[i][j].errorCount++;
						sudokuMatrix[i][col].errorCount++;
						if (sudokuMatrix[i][col].errorCount > highestErrorCount)
							highestErrorCount = sudokuMatrix[i][col].errorCount;
					}
				}
				if (sudokuMatrix[i][j].errorCount > highestErrorCount)
					highestErrorCount = sudokuMatrix[i][j].errorCount;
			}
        }
        for (unsigned int j = 0; j < 9; ++j)
            matches[j] = false;
    }
	// Check if columns have errors
	for (unsigned int i = 0; i < 9; ++i)
    {
        for (unsigned int j = 0; j < 9; ++j)
        {
            if (!matches[sudokuMatrix[j][i].value - 49])
                matches[sudokuMatrix[j][i].value - 49] = true;
            else
			{
				for (int row = 0; row < j; row++)
				{
					if (sudokuMatrix[j][i].value == sudokuMatrix[row][i].value)
					{
						sudokuMatrix[j][i].errorCount++;
						sudokuMatrix[row][i].errorCount++;
						if (sudokuMatrix[row][i].errorCount > highestErrorCount)
							highestErrorCount = sudokuMatrix[row][i].errorCount;
					}
				}
				if (sudokuMatrix[j][i].errorCount > highestErrorCount)
					highestErrorCount = sudokuMatrix[j][i].errorCount;
			}
        }
        for (unsigned int j = 0; j < 9; ++j)
            matches[j] = false;
    }
	// Check if 3x3s have errors
    for (unsigned int I = 0; I < 3; ++I)
    {
        for (unsigned int J = 0; J < 3; ++J)
        {
            for (unsigned int i = 3 * I; i < 3 * I + 3; ++i)
            {
                for (unsigned int j = 3 * J; j < 3 * J + 3; ++j)
                {
                    if (!matches[sudokuMatrix[i][j].value - 49])
                        matches[sudokuMatrix[i][j].value - 49] = true;
                    else
					{
						for (int row = 3 * I; row < i; row++)
						{
							for (int col = 3 * J; col < 3 * J + 3; col++)
							{
								if (col != j)
								{
									if (sudokuMatrix[i][j].value == sudokuMatrix[row][col].value)
									{
										sudokuMatrix[i][j].errorCount++;
										sudokuMatrix[row][col].errorCount++;
										if (sudokuMatrix[row][col].errorCount > highestErrorCount)
											highestErrorCount = sudokuMatrix[row][col].errorCount;
									}
								}
							}
						}
						if (sudokuMatrix[i][j].errorCount > highestErrorCount)
							highestErrorCount = sudokuMatrix[i][j].errorCount;
					}
                }
            }
            for (unsigned int j = 0; j < 9; ++j)
                matches[j] = false;
        }
    }
	vector<Node*> errorsToShuffle;
	while (errorsToShuffle.size() <= 2 && highestErrorCount > 0)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (!sudokuMatrix[row][col].isHint)
				{
					if (sudokuMatrix[row][col].errorCount == highestErrorCount)
						errorsToShuffle.push_back(&(sudokuMatrix[row][col]));
				}
			}
		}
		highestErrorCount--;
	}
	vector<char> valuesToShuffle;
	int sumOfShuffled = 0;
	for (int i = 0; i < errorsToShuffle.size(); i++)
	{
		valuesToShuffle.push_back(errorsToShuffle[i]->value);
		sumOfShuffled += valuesToShuffle[i];
	}
	random_shuffle (valuesToShuffle.begin(), valuesToShuffle.end());
	for (int i = 0; i < errorsToShuffle.size(); i++)
	{
		errorsToShuffle[i]->value = valuesToShuffle[i];
	}
	return sumOfShuffled;
}

/*******strongShuffle*********
shuffles around every error
*/////////////////////////////
void Sudoku::strongShuffle()
{
	vector<Node*> errorsToShuffle;
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (!sudokuMatrix[row][col].isHint)
			{
				if (sudokuMatrix[row][col].errorCount > 0)
					errorsToShuffle.push_back(&(sudokuMatrix[row][col]));
			}
		}
	}
	vector<char> valuesToShuffle;
	for (int i = 0; i < errorsToShuffle.size(); i++)
	{
		valuesToShuffle.push_back(errorsToShuffle[i]->value);
	}
	random_shuffle (valuesToShuffle.begin(), valuesToShuffle.end());
	for (int i = 0; i < errorsToShuffle.size(); i++)
	{
		errorsToShuffle[i]->value = valuesToShuffle[i];
	}
}

/*********randomSwap********
swaps a random error with a random node that does not give an error
***************************/
void Sudoku::randomSwap()
{
	vector<Node*> errorNodes;
	vector<Node*> errorlessNodes;
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (!sudokuMatrix[row][col].isHint)
			{
				if (sudokuMatrix[row][col].errorCount == 0)
					errorlessNodes.push_back(&(sudokuMatrix[row][col]));
				else
					errorNodes.push_back(&(sudokuMatrix[row][col]));
			}
		}
	}
	random_shuffle (errorNodes.begin(), errorNodes.end());
	random_shuffle (errorlessNodes.begin(), errorlessNodes.end());
	char temp = errorNodes[0]->value;
	errorNodes[0]->value = errorlessNodes[0]->value;
	errorlessNodes[0]->value = temp;
}

/********solveStochastic*******
solves the sudoku problem by employing a stochastic algorithm
*****************************/
void Sudoku::solveStochastic()
{
	randomize();
	int lastSumOfShuffled = 0;
	int currentSumOfShuffled;
	int repetitions = 0;
	int strongCount = 0;
	while (!validate())
	{
		currentSumOfShuffled = shuffleErrors();
		if (currentSumOfShuffled == lastSumOfShuffled)
		{
			repetitions++;
			if (repetitions == 10)
			{
				strongCount++;
				repetitions = 0;
				if (strongCount == 5)
				{
					randomSwap();
					strongCount = 0;
				}
				else
					strongShuffle();
			}
		}
		else
			lastSumOfShuffled = currentSumOfShuffled;
	}
}

void Sudoku::publicSolveBT()
{
	solveBT(1);
	return;
}

// /////////////////////////////////////////

//Returns the set of numbers that are in the row asked for
set<char> Sudoku::getRow(int row)
{
	set<char> output;
	for (int i = 0; i < 9; i++) {
		if (sudokuMatrix[row][i].value != '0')
			output.insert(sudokuMatrix[row][i].value);
	}
	return output;
}

//Returns the set of numbers that are in the column asked for
set<char> Sudoku::getColumn(int column)
{
	set<char> output;
	for (int i = 0; i < 9; i++)
		if (sudokuMatrix[i][column].value != '0')
			output.insert(sudokuMatrix[i][column].value);
	return output;
	
}

//Returns the set of numbers that are associated in the given cell's corresponding 3x3
set<char> Sudoku::getSquare(int row, int column)
{
	set<char> output;
	int square;
	if (row < 3) {
		if (column < 3)
			square = 1;
		else if (column < 6)
			square = 2;
		else
			square = 3;
	}
	else if (row < 6) {
		if (column < 3)
			square = 4;
		else if (column < 6)
			square = 5;
		else
			square = 6;

	}
	else {
		if (column < 3)
			square = 7;
		else if (column < 6)
			square = 8;
		else
			square = 9;
	}
	if (square == 1)
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (sudokuMatrix[i][j].value != '0') {
					output.insert(sudokuMatrix[i][j].value);
				}
			}
		}
	else if (square == 2)
		for (int i = 0; i < 3; i++) {
			for (int j = 3; j < 6; j++) {
				if (sudokuMatrix[i][j].value != '0')
					output.insert(sudokuMatrix[i][j].value);
			}
		}
	
	else if (square == 3)
		for (int i = 0; i < 3; i++) {
			for (int j = 6; j < 9; j++) {
				if (sudokuMatrix[i][j].value != '0')
					output.insert(sudokuMatrix[i][j].value);
			}
		}
	else if (square == 4)
		for (int i = 3; i < 6; i++) {
			for (int j = 0; j < 3; j++) {
				if (sudokuMatrix[i][j].value != '0')
					output.insert(sudokuMatrix[i][j].value);
			}
		}
	else if (square == 5)
		for (int i = 3; i < 6; i++) {
			for (int j = 3; j < 6; j++) {
				if (sudokuMatrix[i][j].value != '0')
					output.insert(sudokuMatrix[i][j].value);
			}
		}
	else if (square == 6)
		for (int i = 3; i < 6; i++) {
			for (int j = 6; j < 9; j++) {
				if (sudokuMatrix[i][j].value != '0')
					output.insert(sudokuMatrix[i][j].value);
			}
		}
	else if (square == 7)
		for (int i = 6; i < 9; i++) {
			for (int j = 0; j < 3; j++) {
				if (sudokuMatrix[i][j].value != '0')
					output.insert(sudokuMatrix[i][j].value);
			}
		}
	else if (square == 8)
		for (int i = 6; i < 9; i++) {
			for (int j = 3; j < 6; j++) {
				if (sudokuMatrix[i][j].value != '0')
					output.insert(sudokuMatrix[i][j].value);
			}
		}
	else if (square == 9)
		for (int i = 6; i < 9; i++) {
			for (int j = 6; j < 9; j++) {
				if (sudokuMatrix[i][j].value != '0')
					output.insert(sudokuMatrix[i][j].value);
			}
		}
	return output;
	
}

//Does set subtraction to find the numbers that can be put into a cell. Returns empty set if no numbers can be placed.
set<char> Sudoku::getChoices(int row, int column)
{
	//Set of numbers 1-9 - set(Row) - set(Column) - set(3x3) = applicable choices
	set<char> digits;
	for (int i = 1; i <= 9; i++)
		digits.insert(i + 48);
	set<char> choices;
	set<char> cNum = getColumn(column);
	set<char> rNum = getRow(row);
	set<char> sNum = getSquare(row, column);
	set<char> temp;
	set<char> temp2;
	set_difference(digits.begin(), digits.end(), cNum.begin(), cNum.end(), inserter(temp, temp.begin()));
	set_difference(temp.begin(), temp.end(), rNum.begin(), rNum.end(), inserter(temp2, temp2.begin()));
	set_difference(temp2.begin(), temp2.end(), sNum.begin(), sNum.end(), inserter(choices, choices.begin()));
	return choices;
}

//Goes through the sudoku left to right, top to bottom; if number can be chosen to be put in cell, it will do so and call itself on the next cell.
bool Sudoku::solveBT(int index)
{
	if (index > 81) { //Case where all cells are solved
		cout << "Reached end of board" << endl;
		return true;
	}
	if (indices.find(index) == indices.end()) {
		cout << index << " is not found within the map" << endl;
		return true;
	}

	int& row = indices.find(index)->second.first;
	int& column = indices.find(index)->second.second;

	if (sudokuMatrix[row][column].isHint) { //Skip Hint cells, as they won't be edited and are correct to begin with
		cout << index << " is a hint" << endl;
		return solveBT(index + 1);
	}
	set<char> choices = getChoices(row, column); //Get applicable numbers to put in cell

	cout << "Choices for " << index << " are: " << endl; //Debug code
	for (auto iter = choices.begin(); iter != choices.end(); iter++)
		cout << *iter << ", ";

	cout << endl;
	for (auto iter = choices.begin(); iter != choices.end(); iter++) { //Iterate through applicable numbers, assign to cell, and try to solve next cell
		sudokuMatrix[row][column].value = *iter;
		if (solveBT(index + 1) == false) { //If a dead end was reached using the number chosen, use another applicable number
			//cout << "Choosing " << *iter << " at " << index << " led to a dead end" << endl;
			continue;
		}
		else { //Case where sudoku was solved using the cell's chosen number; returns true to conclude all nested calls
			return true;
		}
	}
	sudokuMatrix[row][column].value = '0'; //0 is assigned again to clean up wrong answers when backtracking

	if (choices.empty()) //Returns false if no numbers can be put into a cell
		return false;

	return false; //Returns false if all applicable numbers lead to dead ends(paths that lead to a cell with no applicable numbers)

}


