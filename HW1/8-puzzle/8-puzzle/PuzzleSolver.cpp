#include "PuzzleSolver.h"

int PuzzleSolver::func(int threshold, State s, std::stack<std::string>& path)
{
	if (s.f() > threshold)
		return s.f();

	if (s.isGoalState())
	{
		std::cout << "\n" << s.getCurPathCost() << "\n";
		path.push(s.getDirection());
		return -1;
	}

	int minThreshold = std::numeric_limits<int>::max();;
	std::vector<State*> adj = s.generateChildren();
	for (int i = 0; i < adj.size(); i++)
	{
		int temp = func(threshold, *adj[i], path);
		if (temp == -1)
		{
			path.push(s.getDirection());
			return -1;
		}
		if (temp < minThreshold)
			minThreshold = temp;
	}

	return minThreshold;
}

bool PuzzleSolver::func2(State start)
{
	std::stack<std::string> path;
	int threshold = start.f();
	bool goalStateFound = false;
	int curThreshold;

	auto startt = std::chrono::steady_clock::now();
	while (!goalStateFound)
	{
		curThreshold = func(threshold, start, path);
		if (curThreshold == -1)
		{
			goalStateFound = true;
			break;
		}
		threshold = curThreshold;
	}
	auto end = std::chrono::steady_clock::now();
	int size = path.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << path.top() << "\n";
		path.pop();
	}

	std::cout << std::chrono::duration <double, std::milli>(end-startt).count() << " ms" << std::endl;
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
	if (start.isSolvable())
	{
		func2(start);
	}
	else
		std::cout << "This puzzle is unsolvable.\n";
}
