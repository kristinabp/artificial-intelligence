#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <math.h>
class City
{
private:
	double x;
	double y;

public:
	City(double _x, double _y);

	double distance(const City& other);
	void print()const;
};
#endif // !CITY_H

