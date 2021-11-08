#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include "State.h"
#include<stack>
#include<limits>
#include<chrono>

class PuzzleSolver
{
	int search(int threshold, State s, std::stack<std::string>& path, std::vector<std::vector<std::vector<int>>>& visitedStates);
	bool idaStar(State start);
	bool isVisited(std::vector<std::vector<int>> state, std::vector<std::vector<std::vector<int>>> visitedStates);
	

public:
	PuzzleSolver();
	void solve(State start);
};
#endif // !PUZZLESOLVER_H

