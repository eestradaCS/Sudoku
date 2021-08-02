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
feel free to ignore this for now as it is not currently functional
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
	I used it for debugging
************************/
void Sudoku::printValidity() const
{
	cout << "This solution is ";
	if (!validate())
		cout << "not ";
	cout << "valid." << endl;
}

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
	//	display();
	}
}