#include <iostream>
#include "State.h"

void solve(State s)
{
	while (s.hasConflicts())
	{
		int col = s.getColWithQueenWithMaxConf();
		int row = s.getRowWithMinConf(col);
		//s.moveQueen();
	}
}

int main()
{
	int n;
	std::cin >> n;
	State s(n);
	s.printState();
	s.getColWithQueenWithMaxConf();
	//solve(s);

	return system("pause");
}