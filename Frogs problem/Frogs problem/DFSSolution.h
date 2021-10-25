#ifndef DFSSOLUTION_H
#define DFSSOLUTION_H

#include "FrogsPuzzle.h"

class DFSSolution {
private:
	const static char LEFT_FROG = 'L';
	const static char RIGHT_FROG = 'R';
	const static char LEAF = '_';


public:
	void solve(int n);
	bool dfs(std::vector<char> board, int zeroPosition);
	bool isGoalState(std::vector<char> board, int zeroPosition);
	bool moveRight(std::vector<char> board, int zeroPosition, int jump);
	bool moveLeft(std::vector<char> board, int zeroPosition, int jump);
	bool move(std::vector<char> board, int zeroPosition, int frogPosition);
	void swap(std::vector<char> board, int ind1, int ind2);
	void print(std::vector<char> board, bool isReversedOrder);
	void reversedOrderPrint(std::vector<char> board);
	void straightOrderPrint(std::vector<char> board);
};


#endif // !DFSSOLUTION_H
