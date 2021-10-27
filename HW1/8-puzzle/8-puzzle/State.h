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
	int curPathCost;
	int sizeDesk;
	State* parent;

	int manhhatan()const;
	bool isExternalPoint(int x, int y)const;
	void swap(std::vector<std::vector<int>>& state, int x1, int y1, int x2, int y2);


public:
	State(int n, int index, int curPathCost, State* parent);
	State(std::vector<std::vector<int>> state, std::pair<int, int> zeroPosition, int curPathCost, State* parent);
	State& operator=(const State& other);
	bool operator==(const State& other) const;
	
	friend bool operator>(const State& s1, const State& s2);

	void printState()const;
	int f() const;
	std::vector<State*> generateChildren();
	bool isGoalState()const;
	State* getParent()const;
};
#endif // !STATE_H
