#include "FrogsPuzzle.h"


FrogsPuzzle::FrogsPuzzle(int n)
{
	this->n = n;
	this->boardSize = n * 2 + 1;
	for (int i = 0; i < this->boardSize; i++)
	{
		if (i < n)
			this->board.push_back('L');
		else if (i == n)
			this->board.push_back('_');
		else
			this->board.push_back('R');
	}
}

void FrogsPuzzle::solution(std::vector<char> board, int n)
{
	printBoard(board);

	for (int i = 0; i <= n; i++)
	{
		if (i % 2 == 0)
		{
			jump(board, i, true, true);
		}
		else
		{
			jump(board, i, true, false);
		}

		printBoard(board);
	}

	if (n % 2 == 0)
	{
		jump(board, n, nullptr, false);
	}
	else
	{
		jump(board, n, nullptr, true);
	}
	
	printBoard(board);

	for (int i = n; i > 0; i--)
	{
		if (i % 2 == 0)
		{
			jump(board, i, false, true);
		}
		else
		{
			jump(board, i, false, false);
		}
		printBoard(board);
	}
}


void FrogsPuzzle::printBoard(std::vector<char> board)
{
	for (int i = 0; i < this->boardSize; i++)
	{
		std::cout << this->board[i] << ' ';
	}
}

int FrogsPuzzle::findStartIndex(bool isLeftMove, std::vector<char> board)
{
	int startIndex = 0;

}

void FrogsPuzzle::swap(std::vector<char> board, bool isJump, int startIndex, bool isLeftMove)
{
	char buff = board[startIndex];
	int stepMoves = 0;
	if (isJump)
		stepMoves = 2;
	else
		stepMoves = 1;

	if (isLeftMove) {
		board[startIndex] = board[startIndex + stepMoves];
		board[startIndex + stepMoves] = buff;
	}
	else
	{
		board[startIndex] = board[startIndex - stepMoves];
		board[startIndex - stepMoves] = buff;
	}
}
