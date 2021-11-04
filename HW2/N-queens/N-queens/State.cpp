#include "State.h"

int State::getIndexRight(int row, int col) const
{
	if (col - row <= 0)
		return this->size - abs(col - row) - 1;
	else
		return col - row + this->size - 1;
	
}

State::State(int n): size(n)
{
	this->numRowConf.resize(n, 0);
	this->leftDiagConf.resize(2 * n - 1, 0);
	this->rightDiagConf.resize(2 * n - 1, 0);

	srand((unsigned)time(0));
	std::vector<int> numOfQueensPerRow(n, 0);
	std::vector<int> numOfQueensPerRightDiag(2 * n - 1, 0);
	std::vector<int> numOfQueensPerLeftDiag(2 * n - 1, 0);
	for (int i = 0; i < this->size; i++)
	{
		int randRow = rand() % this->size;
		Queen queen(randRow, i);
		this->queens.push_back(queen);
		numOfQueensPerRow[randRow]++;
		numOfQueensPerRightDiag[getIndexRight(randRow, i)]++;
		numOfQueensPerLeftDiag[randRow + i]++;
	}

	for (int i = 0; i < this->size; i++)
		this->numRowConf[i] = ((numOfQueensPerRow[i] - 1) + 1) * (numOfQueensPerRow[i] - 1) / 2; 

	for (int i = 0; i < this->size * 2 - 1; i++)
	{
		this->rightDiagConf[i] = ((numOfQueensPerRightDiag[i] - 1) + 1) * (numOfQueensPerRightDiag[i] - 1) / 2;
		this->leftDiagConf[i] = ((numOfQueensPerLeftDiag[i] - 1) + 1) * (numOfQueensPerLeftDiag[i] - 1) / 2;
	}
	
}

int State::getColWithQueenWithMaxConf()
{
	int conflicts;
	int maxConflicts=0;
	std::priority_queue<int> colWithQueenWithMaxConf;

	for (int i = 0; i < this->size; i++)
	{
		int row = this->queens[i].getRow();
		conflicts = this->numRowConf[row] + this->rightDiagConf[getIndexRight(row, i)] + this->leftDiagConf[i + row];
		if (conflicts > maxConflicts)
		{
			colWithQueenWithMaxConf.push(i);
			maxConflicts = conflicts;
		}
		else if(conflicts == maxConflicts && conflicts != 0)
		{
			colWithQueenWithMaxConf.push(i);
		}
	}
	
	// to do max col
	return 1;
}

int State::getRowWithMinConf(int col)
{
	int conflicts;
	int minConflicts = this->size + 1;
	std::priority_queue<int> rowWithMinConf;

	for (int i = 0; i < this->size; i++)
	{
		conflicts = this->numRowConf[this->queens[i].getRow()] + this->rightDiagConf[i + this->queens[i].getRow()] + this->leftDiagConf[i + this->queens[i].getRow()];
		

	}

	return 0;
}

void State::moveQueen()
{
}

int State::getSize() const
{
	return this->size;
}

bool State::hasConflicts() const
{
	int conflicts;
	int row, col;
	for (int i = 0; i < this->size; i++)
	{
		row = this->queens[i].getRow();
		col = this->queens[i].getCol();
		conflicts = this->numRowConf[row] + this->rightDiagConf[col + row] + this->leftDiagConf[col + row];
		if (conflicts != 0)
			return true;
	}
	return false;
}

void State::printState() const
{
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			if (this->queens[j].getRow() == i && this->queens[j].getCol() == j)
				std::cout << "* ";
			else
				std::cout << "_ ";
		}
		std::cout << std::endl;
	}

	std::cout << "-------------------------------------------------------------------\n";

	for (int i = 0; i < this->size; i++)
	{
		std::cout << numRowConf[i] << ' ';
	}

	std::cout << std::endl;

	for (int i = 0; i < this->size*2-1; i++)
	{
		std::cout << rightDiagConf[i] << ' ';
	}

	std::cout << std::endl;

	for (int i = 0; i < this->size * 2 - 1; i++)
	{
		std::cout << leftDiagConf[i] << ' ';
	}
}