#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
using namespace std;

class Sudoku
{
	public:
	
	Sudoku(string hints);
	void solveStochastic();
	void display() const;
	void printValidity() const;
	void publicSolveBT();
	
	private:
	
	
	struct Node
	{
		char value = 0;
		bool isHint = false;
		int errorCount = 0; //used for stochastic algorithm
	};
	// Used for both algorithms
	bool validate() const;
	// Used for stochastic algorithm
	void randomize();
	int shuffleErrors();
	void strongShuffle();
	void randomSwap();
	// Member variables
	Node sudokuMatrix[9][9];
	map<int, pair<int,int>> indices;
	int hintValues[9];
	// Used for backtracking algorithm
	set<char> getChoices(int row, int column);
	set<char> getRow(int row);
	set<char> getColumn(int column);
	set<char> getSquare(int row, int column);
	bool solveBT(int index);
	
};