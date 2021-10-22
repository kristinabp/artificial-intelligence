#include "State.h"

State::State(int n)
{
	this->sizeDesk = sqrt(n + 1);
	for (int i = 0; i < this->sizeDesk; i++)
	{
		this->state.push_back(std::vector<int>());
		for (int j = 0; j < this->sizeDesk; j++)
		{
			this->state[i].push_back(i*this->sizeDesk + j + 1);
		}
	}
	this->state[this->sizeDesk - 1][this->sizeDesk - 1] = 0;
	this->zeroPosition = { this->sizeDesk - 1 , this->sizeDesk - 1 };
}

State::State(int n, int index)
{
	this->sizeDesk = sqrt(n + 1);
	if (index != -1)
		this->zeroPosition = { int((index - 1) / this->sizeDesk), (index - 1) % this->sizeDesk }; // sets (x, y) position from row-major ordering
	else if (index == -1)
		this->zeroPosition = { this->sizeDesk - 1 , 0 }; // by default the position of the zero is in the left bottom

	while (true)
	{
		std::pair<int, int> curZeroPosition;
		for (int i = 0; i < this->sizeDesk; i++)
		{
			std::cout << "Enter " << i + 1 << "row: ";
			this->state.push_back(std::vector<int>());
			for (int j = 0; j < this->sizeDesk; j++)
			{
				int cur;
				std::cin >> cur;
				if (cur == 0)
					curZeroPosition = { i, j };
				this->state[i].push_back(cur);
			}
		}

		if (curZeroPosition != this->zeroPosition)
		{
			std::cout << "Wrong position of the zero. Please enter the desk again./n";
		}
		else break;
	}
	
}

State& State::operator=(const State& other)
{
	if (this != &other)
	{
		this->state = other.state;
		this->sizeDesk = other.sizeDesk;
		this->zeroPosition = other.zeroPosition;
	}

	return *this;
}

bool State::operator==(const State& other) const
{
	if (this->sizeDesk != other.sizeDesk)
		return false;

	bool equalStates = true;
	for (int i = 0; i < this->sizeDesk; i++)
	{
		for (int j = 0; j < this->sizeDesk; j++)
		{
			if (this->state[i][j] != other.state[i][j])
				equalStates = false;
		}
	}

	return equalStates;
}

void State::printState() const
{
	for (int i = 0; i < this->sizeDesk; i++)
	{
		for (int j = 0; j < this->sizeDesk; j++)
		{
			std::cout << this->state[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
