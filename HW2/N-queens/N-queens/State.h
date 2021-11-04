#ifndef STATE_H
#define STATE_H

#include "Queen.h"
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<queue>

class State
{
private:
	std::vector<Queen> queens;
	std::vector<int> numRowConf;
	std::vector<int> rightDiagConf; // from left to right
	std::vector<int> leftDiagConf; // from right to left
	int size;

	int getIndexRight(int row, int col) const;
	void initQueenMinMax(int col);
	void updateConflicts(int col, int row);

public:
	State(int n);

	void printState()const;
	int getColWithQueenWithMaxConf();
	int getRowWithMinConf(int col);
	void moveQueen();
	int getSize()const;
	bool hasConflicts()const;
};
#endif // !STATE_H
