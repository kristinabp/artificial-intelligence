#include "Fitness.h"

double Fitness::routeDistance()
{
    if (this->distance == 0)
    {
        int pathDistance = 0;
        for (int i = 0; i < this->route.size() - 1; i++)
        {
            City fromCity = this->route[i];
            City toCity = this->route[i + 1];
            pathDistance += fromCity.distance(toCity);
            this->distance = pathDistance;
        }
    }

    return this->distance;
}

Fitness::Fitness(const std::vector<City>& _route): route(_route)
{
	this->distance = 0;
	this->fitness = 0;
}

double Fitness::routeFitness()
{
    if (this->fitness == 0)
        this->fitness = 1 / routeDistance();
    return this->fitness;
}

bool operator>(const Fitness& f1, const Fitness& f2)
{
    return f1.fitness > f2.fitness;
}
