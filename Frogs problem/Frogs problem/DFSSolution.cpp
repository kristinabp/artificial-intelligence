#include "DFSSolution.h"

void DFSSolution::solve(int n)
{
	std::vector<char> board;
	for (int i = 0; i < n*2 + 1; i++)
	{
		if (i < n)
			board.push_back('L');
		else if (i == n)
			board.push_back('_');
		else
			board.push_back('R');
	}

	dfs(board, n);
}

bool DFSSolution::dfs(std::vector<char> board, int zeroPosition)
{
	if (isGoalState(board, zeroPosition))
	{
		print(board, true);
		return true;
	}

	if (moveRight(board, zeroPosition, 2)) return true;
	if (moveRight(board, zeroPosition, 1)) return true;
	if (moveLeft(board, zeroPosition, 2)) return true;
	if (moveLeft(board, zeroPosition, 1)) return true;

	return false;
}

bool DFSSolution::isGoalState(std::vector<char> board, int zeroPosition)
{
	int midIndex = (board.size() * 2 - 1) / 2;
	if (midIndex != zeroPosition)
		return false;
	for (int i = 0; i < midIndex; i++)
	{
		if (board[i] != RIGHT_FROG)
			return false;
	 }

	for (int i = midIndex+1; i < board.size()-1; i++)
	{
		if (board[i] != LEFT_FROG)
			return false;
	}

	return true;
}

bool DFSSolution::moveRight(std::vector<char> board, int zeroPosition, int jump)
{
	int frogPosition = jump == 1 ? zeroPosition - 1 : zeroPosition - 2;
	if (0 <= frogPosition && board[frogPosition] == LEFT_FROG)
	{
		return move(board, zeroPosition, frogPosition);
	}

	return false;
}

bool DFSSolution::moveLeft(std::vector<char> board, int zeroPosition, int jump)
{
	int frogPosition = jump == 1 ? zeroPosition + 1 : zeroPosition + 2;
	if (frogPosition < board.size() && board[frogPosition] == RIGHT_FROG)
	{
		return move(board, zeroPosition, frogPosition);
	}

	return false;
}

bool DFSSolution::move(std::vector<char> board, int zeroPosition, int frogPosition)
{
	swap(board, zeroPosition, frogPosition);
	if (dfs(board, frogPosition))
	{
		swap(board, zeroPosition, frogPosition);
		print(board, true);
		return true;
	}

	swap(board, zeroPosition, frogPosition);
	return false;
}

void DFSSolution::swap(std::vector<char> board, int ind1, int ind2)
{
	char tmp = board[ind1];
	board[ind1] = board[ind2];
	board[ind2] = tmp;
}

void DFSSolution::print(std::vector<char> board, bool isReversedOrder)
{
	if (isReversedOrder)
		reversedOrderPrint(board);
	else
		straightOrderPrint(board);
}

void DFSSolution::reversedOrderPrint(std::vector<char> board)
{
	for (int i = 0; i < board.size(); i++)
	{
		std::cout << board[i] << " ";
	}
}

void DFSSolution::straightOrderPrint(std::vector<char> board)
{
	for (int i = board.size() - 1; i >= 0; i--)
	{
		std::cout << board[i] << " ";
	}
}
