#include<iostream>
#include "State.h"



int main() {
	
	int n;
	std::cout << "Enter n: ";
	std::cin >> n;

	State goalState(n);
	goalState.printState();
	int index;
	std::cout << "Enter the 0's index: ";
	std::cin >> index; // index in {1, ..., n+1}, so if index=1, the desk position of the zero will be (0,0)

	State state1(n, index);
	state1.printState();
	 

	return system("pause");
}