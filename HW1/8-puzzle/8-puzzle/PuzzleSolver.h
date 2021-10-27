#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include "State.h"

enum moves
{
	left = 'l',
	right = 'r',
	up = 'u',
	down = 'd'
};

class PuzzleSolver
{
	int func(int threshold, State s);
	bool func2(State start);

public:
	PuzzleSolver();
	void solve(State start);
};
#endif // !PUZZLESOLVER_H

