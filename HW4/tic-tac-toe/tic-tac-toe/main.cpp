#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<limits>
#include<map>
#include<chrono>

#define TABLE_SIZE 3
std::vector<std::vector<std::string>> table;
std::string computer = "X";
std::string player = "O";
int alpha = INT32_MIN;
int beta = INT32_MAX;

std::string gameDone()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (table[0][i] != "-" && table[0][i] == table[1][i] &&
			table[0][i] == table[2][i])
			return table[0][i];
	}

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (table[i][0] != "-" && table[i][0] == table[i][1] &&
			table[i][0] == table[i][2])
			return table[i][0];
	}

	if (table[0][0] != "-" && table[0][0] == table[1][1] &&
		table[0][0] == table[2][2])
		return table[0][0];

	if (table[0][2] != "-" && table[0][2] == table[1][1] &&
		table[0][2] == table[2][0])
		return table[0][2];

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		for (int j = 0; j < TABLE_SIZE; j++)
		{
			if (table[i][j] == "-")
				return "";
		}
	}

	return "T";
}

void initTable()
{
	table.resize(TABLE_SIZE);
	for (int i = 0; i < TABLE_SIZE; i++)
		for (int j = 0; j < TABLE_SIZE; j++)
		{
			table[i].push_back("-");
		}
}

void printTable()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		std::cout << "  __  __  __   \n";
		std::cout << "| ";
		for (int j = 0; j < TABLE_SIZE; j++)
		{
			std::cout << table[i][j] << " | ";
		}

		std::cout << '\n';
	}
	std::cout << "  __  __  __  \n";
}

std::vector<std::pair<int, int>> getFreeMoves(std::vector<std::vector<std::string>> curState)
{
	std::vector<std::pair<int, int>> freeMoves;
	for (int i = 0; i < TABLE_SIZE; i++)
		for (int j = 0; j < TABLE_SIZE; j++)
		{
			if (curState[i][j] == "-")
				freeMoves.push_back({ i, j });
		}

	return freeMoves;
}

std::pair<int, std::pair<int, int>> minimax(std::vector<std::vector<std::string>>& curState, int _alpha, int _beta, bool isMaxPlayer)
{
	std::string result = gameDone();
	if (result == "X")
	{
		int utility = getFreeMoves(table).size() + 1;
		return { utility, {-1, -1} };
	}
	else if (result == "O")
	{
		int utility = getFreeMoves(table).size() + 1;
		return { -utility, {-1, -1} };
	}
	else if (result == "T")
		return { 0, {-1, -1} };


	int x = -1;
	int y = -1;

	if (isMaxPlayer)
	{
		int maxValue = INT32_MIN;
		std::vector<std::pair<int, int>> freeM = getFreeMoves(table);
		for (int i = 0; i < freeM.size(); i++)
		{
			table[freeM[i].first][freeM[i].second] = computer;
			int value = minimax(table, _alpha, _beta, false).first;

			if (value > maxValue)
			{
				maxValue = value;
				x = freeM[i].first;
				y = freeM[i].second;
			}
			table[freeM[i].first][freeM[i].second] = "-";

			if (maxValue >= _beta)
			{
				return { maxValue, {x, y } };
			}

			if (maxValue > _alpha)
			{
				_alpha = maxValue;
			}
		}
		return { maxValue, { x, y } };
	}
	else
	{
		int minValue = INT32_MAX;
		std::vector<std::pair<int, int>> freeM = getFreeMoves(table);
		for (int i = 0; i < freeM.size(); i++)
		{
			table[freeM[i].first][freeM[i].second] = player;
			int value = minimax(table, _alpha, _beta, true).first;
			if (value < minValue)
			{
				minValue = value;
				x = freeM[i].first;
				y = freeM[i].second;
			}
			table[freeM[i].first][freeM[i].second] = "-";

			if (minValue <= _alpha)
			{
				return { minValue, {x, y } };
			}

			if (minValue < _beta)
			{
				_beta = minValue;
			}
		}
		return { minValue, { x, y } };
	}
}

void playerTurn()
{
	bool validIndex = false;
	while (!validIndex)
	{
		std::cout << "Enter row: ";
		int row;
		std::cin >> row;
		std::cout << "Enter column: ";
		int column;
		std::cin >> column;

		if (table[row - 1][column - 1] == "-")
		{
			validIndex = true;
			table[row - 1][column - 1] = player;
		}
	}
}

void computerTurn()
{
	std::pair<int, std::pair<int, int>> values = minimax(table, alpha, beta, true);
	table[values.second.first][values.second.second] = computer;
}

void play(bool computerFirst)
{
	while (true)
	{
		std::string result = gameDone();
		if (result != "")
		{
			if (result == "X")
				std::cout << "X wins!\n";
			else if (result == "O")
				std::cout << "O wins!\n";
			else if (result == "T")
				std::cout << "It's a tie!\n";
			return;
		}

		if (computerFirst)
		{
			auto startt = std::chrono::steady_clock::now();
			computerTurn();
			auto endd = std::chrono::steady_clock::now();
			std::cout << "Computer time is: " << std::chrono::duration <double, std::milli>(endd - startt).count() / 1000 << " sec" << std::endl;
			computerFirst = false;
		}
		else
		{
			playerTurn();
			computerFirst = true;
		}

		printTable();
	}
}

int main()
{
	initTable();
	printTable();
	std::cout << "Enter who is going to start first\n (1 for computer, 0 for player)\n";
	int computerFirst;
	std::cin >> computerFirst;
	std::cout << "Computer = X \t Player = O" << '\n';
	play(computerFirst);

	return system("pause");
}