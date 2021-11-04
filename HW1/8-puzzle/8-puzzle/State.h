#ifndef STATE_H
#define STATE_H

#include<iostream>
#include<vector>
#include<utility>
#include<math.h>

class State
{
private:
	std::vector<std::vector<int>> state;
	std::vector<std::vector<int>> goalState;
	std::pair<int, int> zeroPosition;
	std::pair<int, int> goalZeroPosition;
	std::string direction;
	int curPathCost;
	int sizeDesk;
	State* parent;

	int manhhatan()const;
	bool isExternalPoint(int x, int y)const;
	void swap(std::vector<std::vector<int>>& state, int x1, int y1, int x2, int y2);
	int countInversions();

public:
	State(int n, int index, int curPathCost, State* parent);
	State(std::vector<std::vector<int>> state, std::pair<int, int> zeroPosition, int curPathCost, State* parent, std::string direction);
	State& operator=(const State& other);
	bool operator==(const State& other) const;
	
	friend bool operator>(const State& s1, const State& s2);

	void printState()const;
	void printGoalState()const;
	int f() const;
	std::vector<State*> generateChildren();
	bool isGoalState()const;
	std::pair<int, int> getGoalZeroPosition()const;
	int getCurPathCost()const;
	std::string getDirection()const;
	bool isSolvable();
	std::vector<std::vector<int>> getState()const;
};
#endif // !STATE_H
