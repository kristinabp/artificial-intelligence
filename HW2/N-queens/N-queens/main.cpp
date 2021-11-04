#include <iostream>
#include "State.h"

const double K = 0.6;

void solve(State s)
{
	int iter = 0;
	double maxIterations = K * s.getSize();
	//auto startt = std::chrono::steady_clock::now();
	while (iter++ <= maxIterations)
	{
		int col = s.getColWithQueenWithMaxConf();
		int row = s.getRowWithMinConf(col);
		s.moveQueen();
	}

	if (s.hasConflicts())
		solve(s);
	//auto endd = std::chrono::steady_clock::now();
	//std::cout << std::chrono::duration <double, std::milli>(endd - startt).count() << " ms" << std::endl;
}

int main()
{
	int n;
	std::cin >> n;
	State s(n);
	s.printState();
	std::cout << std::boolalpha << s.hasConflicts();
	//s.getColWithQueenWithMaxConf();
	//solve(s);

	return system("pause");
}