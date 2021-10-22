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
	std::pair<int, int> zeroPosition;
	int sizeDesk;


public:
	State(int n);
	State(int n, int index);
	State& operator=(const State& other);
	bool operator==(const State& other) const;

	void printState()const;

};
#endif // !STATE_H
