#ifndef FROGSPUZZLE_H
#define FROGSPUZZLE_H

#include<iostream>
#include<vector>


class FrogsPuzzle {
private:
	std::vector<char> board;
	int n;
	int boardSize;
	
public:
	FrogsPuzzle(int n);

	void solution(std::vector<char> board, int n);
	void printBoard(std::vector<char> board);
	void jump(std::vector<char> board, int pos, bool l, bool r);
	int findStartIndex(bool isLeftMove, std::vector<char> board);
	void swap(std::vector<char> board, bool isJump, int startIndex, bool isLeftMoove);


};
#endif // !FROGSPUZZLE_H
