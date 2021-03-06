#include "PuzzleSolver.h"

int PuzzleSolver::search(int threshold, State s, std::stack<std::string>& path, std::vector<std::vector<std::vector<int>>>& visitedStates)
{
	int f = s.f();
	if (f > threshold)
		return f;

	if (s.isGoalState())
	{
		std::cout << "\n" << s.getCurPathCost() << "\n";
		path.push(s.getDirection());
		return -1;
	}

	std::vector<State*> children = s.generateChildren();
	int minThreshold = std::numeric_limits<int>::max();
	for (int i = 0; i < children.size(); i++)
	{
		if (!isVisited(children[i]->getState(), visitedStates))
		{
			visitedStates.push_back(children[i]->getState());
			int temp = search(threshold, *children[i], path, visitedStates);
			if (temp == -1)
			{
				path.push(s.getDirection());
				return -1;
			}
			if (temp < minThreshold)
				minThreshold = temp;
			visitedStates.pop_back();
		}
	}

	return minThreshold;
}

bool PuzzleSolver::idaStar(State start)
{
	std::stack<std::string> path;
	std::vector<std::vector<std::vector<int>>> visitedStates;
	visitedStates.push_back(start.getState());
	int threshold = start.f();
	bool goalStateFound = false;
	int curThreshold;

	auto startt = std::chrono::steady_clock::now();
	while (!goalStateFound)
	{
		curThreshold = search(threshold, start, path, visitedStates);
		if (curThreshold == -1)
		{
			goalStateFound = true;
			break;
		}
		threshold = curThreshold;
	}
	auto endd = std::chrono::steady_clock::now();
	int size = path.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << path.top() << "\n";
		path.pop();
	}

	std::cout << std::chrono::duration <double, std::milli>(endd-startt).count()/1000 << " sec" << std::endl;
	return goalStateFound;

}

bool PuzzleSolver::isVisited(std::vector<std::vector<int>> state, std::vector<std::vector<std::vector<int>>> visitedStates)
{
	for (int i = 0; i < visitedStates.size(); i++)
	{
		if (state == visitedStates[i])
			return true;
	}
	return false;
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
	if (start.isSolvable())
	{
		std::cout << "This puzzle is solvable.\n";
		idaStar(start);
	}
	else
		std::cout << "This puzzle is unsolvable.\n";
}
