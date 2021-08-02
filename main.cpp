#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Sudoku.h"
#include <set>
#include <chrono>
#include <random>
using namespace std;

//Note: Main only considers valid inputs; inputting things like other numbers, characters, etc. are not accounted for.
int main() {
	mt19937 random(time(0));
	uniform_int_distribution<int> generator(1, 100000); //Random number generator used when choosing to randomly select a puzzle
	ifstream inFile("sudoku.csv"); //Stream var to get data from
	string problem;
	string solved;
	int option;
	while (true) {
		inFile.seekg(ios_base::beg); //Reset to beginning so that if the user solves another puzzle, entering puzzle number '1' does not yield the puzzle after the first iteration.
		getline(inFile, problem); //Reading the header
		cout << "How many sudoku problems do you want to solve?" << endl;
		cout << "1. Solve 1 sudoku problem" << endl;
		cout << "2. Solve n sudoku problems (Board not shown)" << endl;
		cout << "3. Exit" << endl;
		cout << "\nEnter option: ";
		cin >> option;
		cout << endl;
		if (option == 1) {
			while (true) {
				inFile.seekg(ios_base::beg);
				getline(inFile, problem); //Reading the header
				cout << "1. Choose puzzle" << endl;
				cout << "2. Randomly select puzzle" << endl;
				cout << "\nEnter option: ";
				cin >> option;
				cout << endl;
				int puzzleNum;
				if (option == 1) {
					cout << "Choose puzzle number (1 - 100000): ";
					cin >> puzzleNum;
					cout << endl;
				}
				else if (option == 2) {
					puzzleNum = generator(random);
				}
				else
					continue;
				for (int i = 0; i < puzzleNum; i++) {
					getline(inFile, problem, ',');
					getline(inFile, solved);
				}
				Sudoku newBoard(problem);
				cout << "Sudoku Problem #" << puzzleNum << ":" << endl;
				newBoard.display();
				cout << endl;
				cout << "Is this the problem you would like to solve?" << endl;
				cout << "1. Yes" << endl;
				cout << "2. Choose another problem" << endl;
				cout << "\nEnter option: ";
				cin >> option;
				cout << endl;
				if (option == 1) {
					cout << "Which algorithm would you like to use?" << endl;
					cout << "1. Brute Force Algorithm" << endl;
					cout << "2. Stochastic Algorithm" << endl;
					cout << "3. Both algorithms" << endl;
					cout << "\nEnter option: ";
					cin >> option;
					cout << endl;
					if (option == 1) {
						//Solve using brute force
						auto start = chrono::high_resolution_clock::now();//Clock start
						newBoard.publicSolveBT();
						auto stop = chrono::high_resolution_clock::now();//Clock end
						auto time = chrono::duration_cast<chrono::milliseconds>(stop - start);
						cout << "Sudoku Solution using Brute Force: " << time.count() << " ms" << endl;
						newBoard.display();
						cout << endl;
						newBoard.printValidity();
						cout << endl;
						Sudoku solution(solved);
						cout << "Intended Solution: " << endl;
						solution.display();
						break;

					}
					else if (option == 2) {
						//Solve using Stochastic
						auto start = chrono::high_resolution_clock::now();
						newBoard.solveStochastic();
						auto stop = chrono::high_resolution_clock::now();
						auto time = chrono::duration_cast<chrono::milliseconds>(stop - start);
						cout << "Sudoku Solution using Stochastic: " << time.count() << " ms" << endl;
						newBoard.display();
						cout << endl;
						newBoard.printValidity();
						cout << endl;
						Sudoku solution(solved);
						cout << "Intended Solution: " << endl;
						solution.display();
						break;
					}
					else if (option == 3) {
						//Solve using Both
						Sudoku btBoard(problem);
						Sudoku stochBoard(problem);
						auto start = chrono::high_resolution_clock::now();
						btBoard.publicSolveBT();
						auto stop = chrono::high_resolution_clock::now();
						auto time = chrono::duration_cast<chrono::milliseconds>(stop - start);
						cout << "Brute Force Algorithm Runtime: " << time.count() << " ms" << endl;
						btBoard.printValidity();
						start = chrono::high_resolution_clock::now();
						stochBoard.solveStochastic();
						stop = chrono::high_resolution_clock::now();
						time = chrono::duration_cast<chrono::milliseconds>(stop - start);
						cout << "Stochastic Algorithm Runtime: " << time.count() << " ms" << endl;
						stochBoard.printValidity();
						cout << endl;
						Sudoku solution(solved);
						cout << "Intended Solution: " << endl;
						solution.display();
						break;
					}
				}
				else if (option == 2)
					continue;
				return 0;
			}
		}
		else if (option == 2) {
			int n;
			cout << "Specify n: ";
			cin >> n;
			cout << endl;
			cout << "Which algorithm would you like to use?" << endl;
			cout << "1. Brute Force Algorithm" << endl;
			cout << "2. Stochastic Algorithm" << endl;
			cout << "3. Both algorithms" << endl;
			cout << "\nEnter option: ";
			cin >> option;
			cout << endl;
			cout << "Note: Total runtime may take a while to display for large n values." << endl;
			if (option == 1) {
				cout << "Brute Force Algorithm Runtime: ";
				int totalTime = 0;
				for (int i = 0; i < n; i++) {
					getline(inFile, problem, ',');
					getline(inFile, solved);
					Sudoku newBoard(problem);
					auto start = chrono::high_resolution_clock::now();
					newBoard.publicSolveBT();
					auto stop = chrono::high_resolution_clock::now();
					auto time = chrono::duration_cast<chrono::milliseconds>(stop - start);
					totalTime += time.count();
				}
				cout << totalTime << " ms" << endl;
				cout << endl;
			}
			else if (option == 2) {
				cout << "Stochastic Algorithm Runtime: ";
				int totalTime = 0;
				for (int i = 0; i < n; i++) {
					getline(inFile, problem, ',');
					getline(inFile, solved);
					Sudoku newBoard(problem);
					auto start = chrono::high_resolution_clock::now();
					newBoard.solveStochastic();
					auto stop = chrono::high_resolution_clock::now();
					auto time = chrono::duration_cast<chrono::milliseconds>(stop - start);
					totalTime += time.count();
				}
				cout << totalTime << " ms" << endl;
				cout << endl;
			}
			else if (option == 3) {
				cout << "Brute Force Algorithm Runtime: ";
				int totalTime = 0;
				for (int i = 0; i < n; i++) {
					getline(inFile, problem, ',');
					getline(inFile, solved);
					Sudoku newBoard(problem);
					auto start = chrono::high_resolution_clock::now();
					newBoard.publicSolveBT();
					auto stop = chrono::high_resolution_clock::now();
					auto time = chrono::duration_cast<chrono::milliseconds>(stop - start);
					totalTime += time.count();
				}
				cout << totalTime << " ms" << endl;
				inFile.seekg(ios_base::beg);
				getline(inFile, problem);
				cout << "Stochastic Algorithm Runtime: ";
				totalTime = 0;
				for (int i = 0; i < n; i++) {
					getline(inFile, problem, ',');
					getline(inFile, solved);
					Sudoku newBoard(problem);
					auto start = chrono::high_resolution_clock::now();
					newBoard.solveStochastic();
					auto stop = chrono::high_resolution_clock::now();
					auto time = chrono::duration_cast<chrono::milliseconds>(stop - start);
					totalTime += time.count();
				}
				cout << totalTime << " ms" << endl;
				cout << endl;
			}

		}
		else if (option == 3)
			return 0;

	}

}