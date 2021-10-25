#include<iostream>
#include "State.h"
#include<map>

int main() {
	
	State s(8, 1, 0);
	s.printState();
	s.generateChildren();
	


	return system("pause");
}