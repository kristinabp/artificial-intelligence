#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include "State.h"
#include<stack>
#include<limits>
#include<chrono>

class PuzzleSolver
{
	int func(int threshold, State s, std::stack<std::string>& path);
	bool func2(State start);

public:
	PuzzleSolver();
	void solve(State start);
};
#endif // !PUZZLESOLVER_H

