#include<iostream>
#include<vector>
#include<random>
#include<time.h>
#include<algorithm>
#include<set>
#include<iomanip>
#include<string>

#define GEN_SIZE 500
#define MAX_GENERATIONS 100
#define ELITE_GENS 250

int n;
std::vector<std::vector<int>> population;
std::vector<std::pair<std::pair<double, double>, std::string>> cities; 
std::vector<double> pathFitness;
std::vector<double> probability;
std::random_device rd;

void generateRandomPoints(int size)
{
	double x;
	double y;
	for (int i = 1; i <= size; i++)
	{
		x = (double)rd() / size;
		y = (double)rd() / size;

		cities.push_back({ { x,y }, std::to_string(i) });
	}
}

void generateInitialPopulation()
{
	std::vector<bool> used;
	population.resize(GEN_SIZE);
	int current = 0;
	while (current < GEN_SIZE)
	{
		used.assign(n, false);
		for (int j = 0; j < n; j++)
		{
			int node = rd() % n;
			while (used[node] == true)
				node = (node + 1) % n;
			population[current].push_back(node);
			used[node] = true;
		}
		current++;
	}
}

double calculateDistance(std::pair<std::pair<double, double>, std::string>& city1, std::pair<std::pair<double, double>, std::string>& city2)
{
	double xDis = abs(city1.first.first - city2.first.first);
	double yDis = abs(city1.first.second - city2.first.second);
	return sqrt(pow(xDis, 2) + pow(yDis, 2));
}

double calculatePathDistance(std::vector<int>& path)
{
	double distance = 0;
	for (int i = 0; i < path.size()-1; i++)
	{
		distance += calculateDistance(cities[path[i]], cities[path[i + 1]]);
	}

	return distance;
}

double getFitness(std::vector<int>& path)
{
	double distance = calculatePathDistance(path);
	return 1 / distance;
}

bool compareFitness(std::vector<int>& path1, std::vector<int>& path2)
{
	return getFitness(path1) > getFitness(path2);
}

void printPopulation()
{
	for (int i = 0; i < population.size(); i++)
	{
		for (int j = 0; j < population[i].size(); j++)
		{
			std::cout << cities[population[i][j]].second << ' ';
		}
		std::cout << getFitness(population[i]);
		std::cout << '\n';
	}
}

double currentSolution(std::vector<int>& path, int pathIndex, bool isFirst, bool print)
{
	double distance = calculatePathDistance(path);
	if (print)
	{
		if (isFirst)
			std::cout << pathIndex + 1 << "st generation best distance is " << std::fixed << std::setprecision(12) << distance << '\n';
		else
			std::cout << pathIndex + 1 << "th generation best distance is " << std::fixed << std::setprecision(12) << distance << '\n';
	}
	return distance;
}

void onePointCrossover(std::vector<int>& parent1, std::vector<int>& parent2, std::vector<std::vector<int>>& newPopulation)
{
	//srand((unsigned)time(NULL));
	int randPoint =rd() % parent1.size() + 1;
	std::vector<int> child1;
	std::vector<int> child2;

	for (int i = 0; i < randPoint; i++)
	{
		child1.push_back(parent2[i]);
		child2.push_back(parent1[i]);
	}

	int curPosition = randPoint;
	while (child1.size() < parent1.size())
	{
		if (std::find(child1.begin(), child1.end(), parent1[curPosition]) != child1.end())
		{
			curPosition++;
		}
		else
		{
			child1.push_back(parent1[curPosition]);
			curPosition++;
		}

		if (curPosition >= parent1.size())
			curPosition = 0;
	}

	curPosition = randPoint;
	while (child2.size() < parent2.size())
	{
		if (std::find(child2.begin(), child2.end(), parent2[curPosition]) != child2.end())
		{
			curPosition++;
		}
		else {
            child2.push_back(parent2[curPosition]);
			curPosition++;
		}
		if (curPosition >= parent2.size())
			curPosition = 0;
		
	}

	newPopulation.push_back(child1);
	newPopulation.push_back(child2);
}

void crossover(std::vector<std::vector<int>>& newPopulation, std::vector<std::vector<int>>& elitePopulation)
{
	int childSize = 0;
	//from elite number of parents we generate elite number of children
	//srand((unsigned)time(NULL));
	while (childSize < ELITE_GENS)
	{
		int randomParent1 = rd() % 100;
		int randomParent2 = rd() % 100;
		while(randomParent1 == randomParent2)
		{ 
			randomParent2 = rd() % 100;
		}
		double curParent = 0;
		int indexPar1 = 0;
		while (randomParent1 >= curParent)
		{
			curParent += probability[indexPar1];
			indexPar1++;
		}

		curParent = 0;
		int indexPar2 = 0;
		while (randomParent2 >= curParent)
		{
			curParent += probability[indexPar2];
			indexPar2++;
		}

		onePointCrossover(elitePopulation[indexPar1-1], elitePopulation[indexPar2-1], newPopulation);
		childSize+=2;
	}
}

void mutation(std::vector<std::vector<int>>& newPopulation)
{
	//swap mutation -> we swap to genes
	//srand((unsigned)time(NULL));
	int randNum = rd() % 100;
	int numberOfMutations = rd() % newPopulation.size();
	if (randNum == 1)
	{
		for (int i = 0; i < numberOfMutations; i++)
		{
			//srand((unsigned)time(NULL));
			int indexPath = rd() % n;
			int randPos1 = rd() % n;
			int randPos2 = rd() % n;
			while (randPos2 == randPos1)
			{
				randPos2 = rd() % n;
			}

			int old = population[indexPath][randPos1];
			population[indexPath][randPos1] = population[indexPath][randPos2];
			population[indexPath][randPos2] = old;

		}
	}

}


int main()
{
	cities.push_back({ { 0.000190032, -0.000285946 }, "Aberystwyth" });
	cities.push_back({ {383.458, -0.000608756}, "Brighton" });
	cities.push_back({ {-27.0206, -282.758}, "Edinburgh" });
	cities.push_back({ {335.751, -269.577}, "Exeter" });
	cities.push_back({ {69.4331, -246.78}, "Glasgow" });
	cities.push_back({ {168.521, 31.4012}, "Inverness" });
	cities.push_back({ {320.35, -160.9}, "Liverpool" });
	cities.push_back({ {179.933, -318.031}, "London" });
	cities.push_back({ {492.671, -131.563}, "Newcastle" });
	cities.push_back({ {112.198, -110.561}, "Nottingham" });
	cities.push_back({ {306.32, -108.09}, "Oxford" });
	cities.push_back({ {217.343, -447.089}, "Stratford" });
	n = 12;

	/*std::cin >> n;
	generateRandomPoints(n);*/
	generateInitialPopulation();

	std::sort(population.begin(), population.end(), compareFitness);
	double bestDistance = currentSolution(population[0], 0, true, true);
	bool earlyFound = false;

	for (int i = 0; i < MAX_GENERATIONS; i++)
	{
		std::vector<std::vector<int>> eliteGens;
		eliteGens.resize(ELITE_GENS);
		for (int j = 0; j < ELITE_GENS; j++)
		{
			eliteGens[j] = population[j];
		}

		//calculate probability and save probability for each path
		probability.resize(ELITE_GENS);
		double allFitness = 0;
		for (int j = 0; j < ELITE_GENS; j++)
		{
			double curFitness = getFitness(eliteGens[j]);
			allFitness += curFitness;
			pathFitness.push_back(curFitness);
		}

		for (int j = 0; j < ELITE_GENS; j++)
		{
			probability[j] = pathFitness[j] / allFitness * 100;
		}

		// generate childs 
		std::vector<std::vector<int>> newGen;
		crossover(newGen, eliteGens);
		mutation(newGen);

		population.insert(population.end(), newGen.begin(), newGen.end());
		std::sort(population.begin(), population.end(), compareFitness);
		population.erase(population.begin() + population.size() - ELITE_GENS, population.end());

		double curDistance = currentSolution(population[0], i, false, false);

		if ((i == 5) || (i == 7) || (i == 50))
		{
			double curDistance = currentSolution(population[0], i, false, true);
		}

		if (curDistance == 1595.738522033024)
		{
			double curDistance = currentSolution(population[0], i, false, true);
			earlyFound = true;
			break;
		}
		pathFitness.clear();
		probability.clear();
	}
	if (!earlyFound)
		currentSolution(population[0], 99, false, true);

	for (int i = 0; i < population[0].size(); i++)
	{
		std::cout << cities[population[0][i]].second << '\n';
	}

	return system("pause");
}