#pragma once
#include <string>
using namespace std;

class Sudoku
{
	public:
	
	Sudoku(string hints);
	void solveStochastic();
	void display() const;
	void printValidity() const;
	
	private:
	
	struct Node
	{
		char value = 0;
		bool isHint = false;
		int errorCount = 0; //used for stochastic algorithm
	};
	
	void randomize();
	bool validate() const;
	int shuffleErrors();
	void strongShuffle();
	void randomSwap();
	
	Node sudokuMatrix[9][9];
	int hintValues[9];
	
};