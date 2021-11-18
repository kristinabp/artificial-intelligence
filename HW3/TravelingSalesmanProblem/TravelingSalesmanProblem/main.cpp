#include "Fitness.h"
#include<chrono>
#include<algorithm>
#include<random>
#include<queue>

int numCities;

std::vector<City> createRoute(std::vector<City> cities)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::vector<City> route = cities;
	std::shuffle(route.begin(), route.end(), std::default_random_engine(seed));

	return route;
}

std::vector<std::vector<City>> createPopulation(int populationSize, std::vector<City> cities)
{
	std::vector<std::vector<City>> population;
	
	for (int i = 0; i < populationSize; i++)
	{
		population.push_back(createRoute(cities));
	}

	return population;
}

std::priority_queue<Fitness> rankRoutes(std::vector<std::vector<City>> population)
{
	std::priority_queue<Fitness> betterFitness;
	for (int i = 0; i < population.size(); i++)
	{
		betterFitness.push(Fitness(population[i]));
	}
	return betterFitness;
}

std::vector<Fitness> selection(std::priority_queue<Fitness> betterRoutes, int size)
{
	std::vector<Fitness> selected;
	selected.resize(size);
	std::priority_queue<Fitness> routes = betterRoutes;

	for (int i = 0; i < size; i++)
	{
		selected.push_back(routes.top());
		routes.pop();
	}

	std::vector<Fitness> otherRoutes;
	for (int i = 0; i < betterRoutes.size() - size; i++)
	{
		otherRoutes.push_back(routes.top());
		routes.pop();
	}

	srand((unsigned)time(0));
	for (int i = 0; i < betterRoutes.size() - size; i++)
	{
		int randRoute = rand() % otherRoutes.size();
		selected.push_back(otherRoutes[randRoute]);
		otherRoutes.erase(otherRoutes.begin() + randRoute);
	}

	return selected;
}

std::vector<City> crossover(Fitness parent1, Fitness parent2)
{
	std::vector<City> child;
	std::vector<City> childP1;
	std::vector<City> childP2;

}

int main()
{
	std::cin >> numCities;

	return system("pause");
}