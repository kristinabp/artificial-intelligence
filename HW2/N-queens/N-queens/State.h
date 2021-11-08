#ifndef STATE_H
#define STATE_H

#include "Queen.h"
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<queue>
#include<set>

class State
{
private:
	std::vector<int> queens;
	std::vector<int> numRowConf;
	std::vector<int> rightDiagConf; // from left to right
	std::vector<int> leftDiagConf; // from right to left
	int size;

	int getIndexRight(int row, int col) const;

public:
	State(int n);

	void printState()const;
	int getColWithQueenWithMaxConf();
	int getRowWithMinConf(int col);
	void moveQueen(int curCol, int newRow);
	int getSize()const;
	bool hasConflicts()const;
};
#endif // !STATE_H
