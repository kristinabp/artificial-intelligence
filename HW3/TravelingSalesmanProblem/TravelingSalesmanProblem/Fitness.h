#ifndef FITNESS_H
#define FITNESS_H

#include "City.h"
#include <vector>

class Fitness
{
private:
	std::vector<City> route;
	double distance;
	double fitness;

	double routeDistance();

public:
	Fitness(const std::vector<City>& _route);
	double routeFitness();

	friend bool operator> (const Fitness& f1, const Fitness& f2);
};
#endif // !FITHNESS_H

