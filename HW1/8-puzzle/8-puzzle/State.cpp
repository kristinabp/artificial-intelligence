#include "State.h"

State::State(int n, int index, int curPathCost, State* parent)
{
	this->parent = parent;
	this->curPathCost = curPathCost;
	this->sizeDesk = sqrt(n + 1);
	this->direction = "";

	std::pair<int, int> curZeroPosition;
	for (int i = 0; i < this->sizeDesk; i++)
	{
		std::cout << "Enter " << i + 1 << " row: \n";
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

	this->zeroPosition = curZeroPosition;
	this->printState();

	if (index != -1)
		this->goalZeroPosition = { int((index - 1) / this->sizeDesk), (index - 1) % this->sizeDesk }; // sets (x, y) position from row-major ordering
	else this->goalZeroPosition = { this->sizeDesk - 1, this->sizeDesk - 1 };

	int counter = 1;
	for (int i = 0; i < this->sizeDesk; i++)
	{
		this->goalState.push_back(std::vector<int>());
		for (int j = 0; j < this->sizeDesk; j++)
		{
			if (i == this->goalZeroPosition.first && j == this->goalZeroPosition.second)
			{
				this->goalState[i].push_back(0);
			}
			else
				this->goalState[i].push_back(counter++);
		}
	}
}

State::State(std::vector<std::vector<int>> state, std::pair<int, int> zeroPosition, int curPathCost, State* parent, std::string direction, std::vector<std::vector<int>> goalState)
{
	this->direction = direction;
	this->parent = parent;
	this->state = state;
	this->curPathCost = curPathCost;
	this->zeroPosition = zeroPosition;
	this->sizeDesk = state.size();
	this->goalZeroPosition = parent->getGoalZeroPosition();
	this->goalState = goalState;
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

void State::printGoalState() const
{
	for (int i = 0; i < this->sizeDesk; i++)
	{
		for (int j = 0; j < this->sizeDesk; j++)
		{
			std::cout << this->goalState[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int State::f() const
{
	return this->curPathCost + manhhatan();
}

std::vector<State*> State::generateChildren()
{
	std::vector<State*> children;
	if (!isExternalPoint(this->zeroPosition.first - 1, this->zeroPosition.second) )
	{
		std::vector<std::vector<int>> newState = this->state;
		swap(newState, this->zeroPosition.first, this->zeroPosition.second, this->zeroPosition.first - 1, this->zeroPosition.second);
		children.push_back(new State(newState, { this->zeroPosition.first - 1, this->zeroPosition.second }, this->curPathCost + 1, this, "down", this->goalState));
	}

	if (!isExternalPoint(this->zeroPosition.first + 1, this->zeroPosition.second))
	{
		std::vector<std::vector<int>> newState = this->state;
		swap(newState, this->zeroPosition.first, this->zeroPosition.second, this->zeroPosition.first + 1, this->zeroPosition.second);
		children.push_back(new State(newState, { this->zeroPosition.first + 1, this->zeroPosition.second }, this->curPathCost + 1, this, "up", this->goalState));
	}

	if (!isExternalPoint(this->zeroPosition.first, this->zeroPosition.second - 1))
	{
		std::vector<std::vector<int>> newState = this->state;
		swap(newState, this->zeroPosition.first, this->zeroPosition.second, this->zeroPosition.first, this->zeroPosition.second - 1);
		children.push_back(new State(newState, { this->zeroPosition.first, this->zeroPosition.second -1}, this->curPathCost + 1, this, "right", this->goalState));
	}

	if (!isExternalPoint(this->zeroPosition.first, this->zeroPosition.second + 1))
	{
		std::vector<std::vector<int>> newState = this->state;
		swap(newState, this->zeroPosition.first, this->zeroPosition.second, this->zeroPosition.first, this->zeroPosition.second + 1);
		children.push_back(new State(newState, { this->zeroPosition.first, this->zeroPosition.second+1 }, this->curPathCost + 1, this, "left", this->goalState));
	}

	return children;
}

bool State::isGoalState() const
{
	return this->state == this->goalState;
}


std::pair<int, int> State::getGoalZeroPosition() const
{
	return this->goalZeroPosition;
}

int State::getCurPathCost() const
{
	return this->curPathCost;
}

std::string State::getDirection() const
{
	return this->direction;
}

int State::manhhatan() const
{
	int manhhatan = 0;
	for (int i = 0; i < this->sizeDesk; i++)
	{
		for (int j = 0; j < this->sizeDesk; j++)
		{
			if (this->state[i][j] != 0)
			{
				for (int k = 0; k < this->sizeDesk; k++)
				{
					for (int l = 0; l < this->sizeDesk; l++)
					{
						if (this->state[i][j] == goalState[k][l])
							manhhatan += abs(i - k) + abs(j - l);
					}
				}
			}
		}
	}

	return manhhatan;
}

bool State::isExternalPoint(int x, int y) const
{
	return (x < 0 || x >= this->sizeDesk ||
		y < 0 || y >= this->sizeDesk);
}

void State::swap(std::vector<std::vector<int>>& state, int x1, int y1, int x2, int y2)
{
	int temp = state[x2][y2];
	state[x2][y2] = state[x1][y1];
	state[x1][y1] = temp;
}

bool State::isSolvable()
{
	int inversions = this->countInversions();
	if (this->state == this->goalState)
		return false;
	if (this->sizeDesk % 2 == 0)
		return (inversions + this->zeroPosition.first) % 2 == 1;
	else
		return inversions % 2 == 0;
}

std::vector<std::vector<int>> State::getState() const
{
	return this->state;
}

int State::countInversions()
{
	std::vector<int> rowMajoringOrder;
	for (int i = 0; i < this->sizeDesk; i++)
	{
		for (int j = 0; j < this->sizeDesk; j++)
		{
			if (this->state[i][j] != 0)
				rowMajoringOrder.push_back(this->state[i][j]);
		}
	}

	int inversions = 0;
	for (int i = 0; i < rowMajoringOrder.size(); i++)
	{
		for (int j = i + 1; j < rowMajoringOrder.size(); j++)
			if (rowMajoringOrder[i] > rowMajoringOrder[j])
				inversions++;
	}

	return inversions;
}

bool operator>(const State& s1, const State& s2)
{
	return s1.f() > s2.f();
}