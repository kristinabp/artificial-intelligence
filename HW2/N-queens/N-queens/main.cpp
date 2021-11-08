#include <iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<queue>
#include<chrono>

const double K = 0.6;

int n;
std::vector<int> queens;
std::vector<int> numRowConfl;
std::vector<int> numRightDiagConfl;
std::vector<int> numLeftDiagConfl;


int getIndexRight(int row, int col)
{
	if (col - row <= 0)
		return n - abs(col - row) - 1;
	else
		return col - row + n - 1;
}

//void initialize(int n)
//{
//	numRowConfl.resize(n, 0);
//	numRightDiagConfl .resize(2 * n - 1, 0);
//	numLeftDiagConfl.resize(2 * n - 1, 0);
//	queens.resize(n, 0);
//
//	srand((unsigned)time(0));
//	std::vector<int> numOfQueensPerRow(n, 0);
//	std::vector<int> numOfQueensPerRightDiag(2 * n - 1, 0);
//	std::vector<int> numOfQueensPerLeftDiag(2 * n - 1, 0);
//
//	for (int i = 0; i < n; i++)
//	{
//		int randRow = rand() % n;
//		queens[i] = randRow;
//		numOfQueensPerRow[randRow]++;
//		numOfQueensPerRightDiag[getIndexRight(randRow, i, n)]++;
//		numOfQueensPerLeftDiag[randRow + i]++;
//	}
//
//	for (int i = 0; i < n; i++)
//		numRowConfl [i] = ((numOfQueensPerRow[i] - 1) + 1) * (numOfQueensPerRow[i] - 1) / 2;
//
//	for (int i = 0; i < n * 2 - 1; i++)
//	{
//		numRightDiagConfl [i] = ((numOfQueensPerRightDiag[i] - 1) + 1) * (numOfQueensPerRightDiag[i] - 1) / 2;
//		numLeftDiagConfl[i] = ((numOfQueensPerLeftDiag[i] - 1) + 1) * (numOfQueensPerLeftDiag[i] - 1) / 2;
//	}
//
//}

void minConflInit()
{
	numRowConfl.resize(n, 0);
	numRightDiagConfl.resize(2 * n - 1, 0);
	numLeftDiagConfl.resize(2 * n - 1, 0);
	queens.resize(n, 0);

	queens[0] = n - 1;
	numRowConfl[n - 1]++;
	numRightDiagConfl[0]++;
	numLeftDiagConfl[n - 1]++;
	for (int col = 1; col < n ; col++)
	{
		std::vector<int> minRowConfl;
		int minConfl = INT32_MAX;

		for (int row = 0; row < n; row++)
		{
			int conflPerRow = numRowConfl[row] + numRightDiagConfl[getIndexRight(row, col)] + numLeftDiagConfl[row + col];
			if (conflPerRow < minConfl)
			{
				minRowConfl.clear();
				minRowConfl.push_back(row);
				minConfl = conflPerRow;
			}
			else if (conflPerRow == minConfl)
				minRowConfl.push_back(row);
		}
		int curRow = minRowConfl[rand() % minRowConfl.size()];
		queens[col] = curRow;
		numRowConfl[curRow]++;
		numRightDiagConfl[getIndexRight(curRow, col)]++;
		numLeftDiagConfl[curRow + col]++;
	}

}

void printState()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (queens[j] == i)
				std::cout << "* ";
			else
				std::cout << "_ ";
		}
		std::cout << std::endl;
	}

	std::cout << "-------------------------------------------------------------------\n";

	for (int i = 0; i < n; i++)
	{
		std::cout << numRowConfl [i] << ' ';
	}

	std::cout << std::endl;

	for (int i = 0; i < n * 2 - 1; i++)
	{
		std::cout << numRightDiagConfl[i] << ' ';
	}

	std::cout << std::endl;

	for (int i = 0; i < n * 2 - 1; i++)
	{
		std::cout << numLeftDiagConfl[i] << ' ';
	}
	std::cout << std::endl;
}

bool hasConflicts()
{
	int conflicts;
	for (int col = 0; col < n; col++)
	{
		int row = queens[col];
		conflicts = numRowConfl[row] + numRightDiagConfl[getIndexRight(row, col)] + numLeftDiagConfl[col + row] ;
		if (conflicts > 3)
			return true;
	}
	return false;
}

void moveQueen(int curCol, int newRow)
{
	int prevRow = queens[curCol];
	queens[curCol] = newRow;
	numRowConfl[prevRow]--;
	numRowConfl[newRow]++;
	numRightDiagConfl[getIndexRight(prevRow, curCol)]--;
	numLeftDiagConfl[curCol + prevRow]--;
	numRightDiagConfl[getIndexRight(newRow, curCol)]++;
	numLeftDiagConfl[curCol + newRow]++;
}


int getRowWithMinConf(int col)
{
	int minConfl = INT32_MAX;
	std::vector<int> minRowConfl;
	for (int row = 0; row < n; row++)
	{
		int curConfl = numRowConfl[row] + numRightDiagConfl[getIndexRight(row, col)] + numLeftDiagConfl[col + row];
		if (curConfl < minConfl)
		{
			minRowConfl.clear();
			minRowConfl.push_back(row);
			minConfl = curConfl;
		}
		else if (curConfl == minConfl)
			minRowConfl.push_back(row);
	}
	return minRowConfl[rand() % minRowConfl.size()];
}

int getColWithQueenWithMaxConf()
{
	/*int conflicts;
	int maxConflicts = 0;
	std::priority_queue<int> colWithQueenWithMaxConf;

	for (int i = 0; i < n; i++)
	{
		int row = queens[i];
		conflicts = numRowConfl[row] + numRightDiagConfl[getIndexRight(row, i, n)] + numLeftDiagConfl[i + row] ;
		if (conflicts > maxConflicts)
		{
			colWithQueenWithMaxConf.push(i);
			maxConflicts = conflicts;
		}
		else if (conflicts == maxConflicts && conflicts != 0)
		{
			colWithQueenWithMaxConf.push(i);
		}
	}*/

	int maxConfl = INT32_MIN;
	std::vector<int> maxColConfl;
	for (int col = 0; col < n; col++)
	{
		int row = queens[col];
		int curConfl = numRowConfl[row] + numRightDiagConfl[getIndexRight(row, col)] + numLeftDiagConfl[col + row];
		if (curConfl > maxConfl)
		{
			maxColConfl.clear();
			maxColConfl.push_back(col);
			maxConfl = curConfl;
		}
		else if (curConfl == maxConfl)
			maxColConfl.push_back(col);
	}
	return maxColConfl[rand() % maxColConfl.size()];
}

void solve()
{
	srand((unsigned)time(0));
	minConflInit();
	//printState();
	auto startt = std::chrono::steady_clock::now();
	int counter = 0;
	while (counter <= K*n || hasConflicts())
	{
		int col = getColWithQueenWithMaxConf();
		int row = getRowWithMinConf(col);
		moveQueen(col, row);
		counter++;
	}
	if (hasConflicts())
		solve();
	auto endd = std::chrono::steady_clock::now();
	//printState();
	std::cout << std::chrono::duration <double, std::milli>(endd - startt).count() << " ms" << std::endl;
	std::cout << std::chrono::duration <double, std::milli>(endd - startt).count()/1000 << " sec" << std::endl;
}

int main()
{
	std::cin >> n;

	solve();


	return system("pause");
}