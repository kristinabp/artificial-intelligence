#ifndef QUEEN_H
#define QUEEN_H

#include <iostream>

class Queen
{
private:
	int row;
	int col;

public:
	Queen(int rPos, int cPos);

	int getRow()const;
	int getCol()const;
	int rightDiag()const;
	int leftDiag()const;
};
#endif // !QUEEN_H

