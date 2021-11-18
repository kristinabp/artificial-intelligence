#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<limits>
#include<map>

std::vector<std::vector<std::string>> table;
std::string computer = "X";
std::string player = "O";
int depth = 0;
int alpha = INT32_MIN;
int beta = INT32_MAX;

bool validMove(int row, int col)
{
	if (row < 0 || row >3 || col < 0 || col>3)
		return false;
	if (table[row][col] != "")
		return false;

	return true;
}

std::string gameDone()
{
	for (int i = 0; i < 3; i++)
	{
		if (table[0][i] != "" && table[0][i] == table[1][i] &&
			table[0][i] == table[2][i])
			return table[0][i];
	}

	for (int i = 0; i < 3; i++)
	{
		if (table[i][0] != "" && table[i][0] == table[i][1] &&
			table[i][0] == table[i][2])
			return table[i][0];
	}

	if (table[0][0] != "" && table[0][0] == table[1][1] &&
		table[0][0] == table[2][2])
		return table[0][0];

	if (table[0][2] != "" && table[0][2] == table[1][1] &&
		table[0][2] == table[2][0])
		return table[0][2];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (table[i][j] == "")
				return "";
		}
	}

	return "T";
}

std::map<char, int> scores = {
								{'X', 1},
								{'O', -1},
								{'T', 0}
};

void initTable()
{
	table.resize(3);
	for(int i=0; i<3; i++)
		for (int j = 0; j < 3; j++)
		{
			table[i].push_back("");
		}
}

void printTable()
{
	for (int i = 0; i < 3; i++)
	{
		std::cout << " _  _  _\n";
		std::cout << "| ";
		for (int j = 0; j < 3; j++)
		{
			std::cout << table[i][j] << " | ";
		}

		std::cout << '\n';
	}
	std::cout << " _  _  _\n";
}

std::vector<std::pair<int,int>> generateFreeMoves(std::vector<std::vector<std::string>> curState)
{
	std::vector<std::pair<int, int>> freeMoves;
	for(int i=0; i<3; i++)
		for (int j = 0; j < 3; j++)
		{
			if (curState[i][j] == "")
				freeMoves.push_back({ i, j });
		}

	return freeMoves;
}

char checkWinner(bool isMaximizingPlayer)
{
	if (isMaximizingPlayer)
	{
		if (table[0][0] == "X" && table[0][1] == "X" && table[0][2] == "X")
			return 'X';
		if (table[1][0] == "X" && table[1][1] == "X" && table[1][2] == "X")
			return 'X';
		if (table[2][0] == "X" && table[2][1] == "X" && table[2][2] == "X")
			return 'X';
		if (table[0][0] == "X" && table[1][0] == "X" && table[2][0] == "X")
			return 'X';
		if (table[0][1] == "X" && table[1][1] == "X" && table[2][1] == "X")
			return 'X';
		if (table[0][2] == "X" && table[1][2] == "X" && table[2][2] == "X")
			return 'X';
		if (table[0][0] == "X" && table[1][1] == "X" && table[2][2] == "X")
			return 'X';
		if (table[0][2] == "X" && table[1][1] == "X" && table[2][0] == "X")
			return 'X';

		int openSpots = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (table[i][j] == "")
					openSpots++;

		if (openSpots == 0)
			return 'T';
	}
	else
	{
		if (table[0][0] == "O" && table[0][1] == "O" && table[0][2] == "O")
			return 'O';
		if (table[1][0] == "O" && table[1][1] == "O" && table[1][2] == "O")
			return 'O';
		if (table[2][0] == "O" && table[2][1] == "O" && table[2][2] == "O")
			return 'O';
		if (table[0][0] == "O" && table[1][0] == "O" && table[2][0] == "O")
			return 'O';
		if (table[0][1] == "O" && table[1][1] == "O" && table[2][1] == "O")
			return 'O';
		if (table[0][2] == "O" && table[1][2] == "O" && table[2][2] == "O")
			return 'O';
		if (table[0][0] == "O" && table[1][1] == "O" && table[2][2] == "O")
			return 'O';
		if (table[0][2] == "O" && table[1][1] == "O" && table[2][0] == "O")
			return 'O';

		int openSpots = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (table[i][j] == "")
					openSpots++;

		if (openSpots == 0)
			return 'T';
	}

	return ' ';
}

std::pair<int, std::pair<int, int>> minimax(std::vector<std::vector<std::string>>& curState, int curDepth, int _alpha, int _beta, bool isMaxPlayer)
{
	std::string result = gameDone();
	if (result == "X")
		return { 1, {0, 0} };
	else if (result == "O")
		return { -1, {0, 0} };
	else if (result == "T")
		return { 0, {0, 0} };

	int x = -1;
	int y = -1;
	if (isMaxPlayer)
	{
		int maxValue = INT32_MIN;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (table[i][j] == "")
				{
					table[i][j] = computer;
					std::pair<int, std::pair<int, int>> value = minimax(table, depth - 1, alpha, beta, false);
					if (value.first > maxValue)
					{
						maxValue = value.first;
						x = i;
						y = j;
					}
					table[i][j] = "";
				}
			}
		}
		return { maxValue, { x, y } };
	}
	else
	{
		int minValue = INT32_MAX;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (table[i][j] == "")
				{
					table[i][j] = player;
					std::pair<int, std::pair<int, int>> value = minimax(table, depth - 1, alpha, beta, true);
					if (value.first < minValue)
					{
						minValue = value.first;
						x = i;
						y = j;
					}
					table[i][j] = "";
				}
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

		if (table[row][column] == "")
		{
			validIndex = true;
			table[row][column] = player;
		}
	}
}

void computerTurn()
{
	std::pair<int, std::pair<int, int>> values = minimax(table, depth);
	table[values.second.first][values.second.second] = computer;
}

void play(bool computerFirst)
{
	if (computerFirst)
	{
		while (true)
		{
			std::string result = gameDone();
			if (result == "X")
			{
				std::cout << "Computer wins!\n";
				return;
			}
			else if (result == "O")
			{
				std::cout << "You win!\n";
				return;
			}
			else if (result == "T")
			{
				std::cout << "It's a tie!\n";
				return;
			}
		}
	}
	else
	{
		while (gameDone() == "")
		{
			playerTurn();
			computerTurn();
			printTable();
		}
	}

	std::cout << gameDone() << "wins!\n";
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

