#include "Queen.h"

Queen::Queen(int rPos, int cPos): col(cPos), row(rPos)
{
}

int Queen::getRow() const
{
	return this->row;
}

int Queen::getCol() const
{
	return this->col;
}

int Queen::rightDiag() const
{
	return this->col - this->row;
}

int Queen::leftDiag() const
{
	return this->col + this->row;
}
