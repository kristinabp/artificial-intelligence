#include "PuzzleSolver.h"

int PuzzleSolver::func(int threshold, State s)
{
	if (s.f() > threshold)
		return s.f();

	if (s.isGoalState())
	{
		s.printState();
		return -1;
	}

	int minThreshold = 9000;
	std::vector<State*> adj = s.generateChildren();
	for (int i = 0; i < adj.size(); i++)
	{
		int temp = func(threshold, *adj[i]);
		if (temp == -1)
		{
			s.printState();
			return -1;
		}
		if (temp < minThreshold)
			minThreshold = temp;
	}

	return minThreshold;
}

bool PuzzleSolver::func2(State start)
{
	int threshold = start.f();
	bool goalStateFound = false;
	int curThreshold;
	while (!goalStateFound)
	{
		curThreshold = func(threshold, start);
		if (curThreshold == -1)
		{
			goalStateFound = true;
			break;
		}
		threshold = curThreshold;
	}

	return goalStateFound;
}


PuzzleSolver::PuzzleSolver()
{
	int n;
	std::cin >> n;
	int index;
	std::cin >> index;
	State start(n, index, 0, nullptr);
	solve(start);
}

void PuzzleSolver::solve(State start)
{
	if (func2(start))
	{

	}
}
