#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<random>
#include<time.h>
#include<chrono>

#define MAX_ITERATIONS 20
#define RANDOM_ITERATIONS 10

std::random_device rd;
std::vector<std::pair<double, double>> data; // { {x1,y1} , {x2, y2}, ... {xn, yn} }
std::vector<double> minDists;                // { minDistP1, minDistP2, ... minDistPn}
std::vector<std::pair<double, double>> centroids; // { {c1}, {c2} , ... {ck} }
std::vector<int> indexCentroids; // { ind(Cj)->P1, ind(Cj)->P2, ... ind(Cj)->Pn } 

void readData(std::string fileName)
{
	std::fstream inputFile;
	inputFile.open(fileName, std::ios::in);
	if (inputFile.is_open())
	{
		std::string line;
		while (std::getline(inputFile, line)) {
			std::string curNum1;
			std::string curNum2;
			int index = 0;
			while (line[index] != '\t' && line[index] != ' ')
			{
				curNum1.push_back(line[index]);
				index++;
			}
			index++;
			while (index <= line.size())
			{
				curNum2.push_back(line[index]);
				index++;
			}
			data.push_back({ std::stod(curNum1), std::stod(curNum2) });
		}
		inputFile.close();
	}
	else
	{
		std::cout << "Couldn't open " << fileName << "\n";
		inputFile.close();
	}
}

void writeData(std::string fileName)
{
	std::ofstream myfile;
	myfile.open(fileName);
	myfile << "x,y,c" << std::endl;
	for (int i = 0; i < data.size(); i++) {
		myfile << data[i].first << "," << data[i].second << "," << indexCentroids[i] << std::endl;
	}
	myfile.close();
}

void printData(std::vector<std::pair<double, double>> points)
{
	for (int i = 0; i < points.size(); i++)
	{
		std::cout << points[i].first << " " << points[i].second << "\n";
	}
}

double distance(std::pair<double, double> p1, std::pair<double, double> p2)
{
	return sqrt((p2.first - p1.first) * (p2.first - p1.first) + (p2.second - p1.second) * (p2.second - p1.second));
}

std::vector<std::pair<double, double>> initializeCentroids(int centroidsNumber)
{
	std::vector<std::pair<double, double>> c;
	std::vector<int> usedPoints;
	srand((unsigned)time(0));
	while (c.size() < centroidsNumber)
	{
		int ind = rd() % data.size();
		if (std::find(usedPoints.begin(), usedPoints.end(), ind) == usedPoints.end())
		{
			usedPoints.push_back(ind);
			c.push_back({ data[ind].first, data[ind].second });
		}
	}

	return c;
}

std::vector<std::pair<double, double>> initializeCentroidsOpt(int centroidsNumber)
{
	//K means ++
	std::vector<std::pair<double, double>> c;
	srand((unsigned)time(0));
	c.push_back({ data[rd() % data.size()] });
	while (c.size() < centroidsNumber)
	{
		std::vector<std::pair<double, std::pair<double, double>>> maxDist;
		for (int i = 0; i < data.size(); i++)
		{
			std::vector<std::pair<double, std::pair<double, double>>> minDist;
			for (int j = 0; j < c.size(); j++)
			{
				minDist.push_back({ distance(data[i], c[j]), data[i] });
			}

			std::sort(minDist.begin(), minDist.end(), [](std::pair<double, std::pair<double, double>> a, std::pair<double, std::pair<double, double>> b) {return a.first < b.first; });
			maxDist.push_back(minDist[0]);

		}
		std::sort(maxDist.begin(), maxDist.end(), [](std::pair<double, std::pair<double, double>> a, std::pair<double, std::pair<double, double>> b) {return a.first > b.first; });
		c.push_back(maxDist[0].second);
	}
	return c;
}

bool equal(std::vector<std::pair<double, double>> old, std::vector<std::pair<double, double>> current)
{
	for (int i = 0; i < old.size(); i++)
	{
		if (old[i].first != current[i].first)
		{
			return false;
		}
	}
	return true;
}

bool shouldStop(std::vector<std::pair<double, double>> old, std::vector<std::pair<double, double>> current, int iter)
{
	if (iter > MAX_ITERATIONS)
		return true;
	if (equal(old, current))
		return true;
	else return false;
}

void assignPointsToCentroids(std::vector<std::pair<double, double>> curCentroids)
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < curCentroids.size(); j++)
		{
			double curMinDist = distance(curCentroids[j], data[i]);
			if (curMinDist < minDists[i])
			{
				minDists[i] = curMinDist;
				indexCentroids[i] = j;
			}
		}
	}
}

void updateCentroids()
{
	for (int i = 0; i < centroids.size(); i++)
	{
		double sumX = 0.0;
		double sumY = 0.0;
		int counter = 0;
		for (int j = 0; j < data.size(); j++)
		{
			if (centroids[indexCentroids[j]].first == centroids[i].first && centroids[indexCentroids[j]].second == centroids[i].second)
			{
				sumX += data[j].first;
				sumY += data[j].second;
				counter++;
			}
		}

		centroids[i] = { sumX / counter, sumY / counter };
	}
}

void updatePoints()
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < centroids.size(); j++)
		{
			double curMinDist = distance(centroids[j], data[i]);
			if (curMinDist < minDists[i])
			{
				minDists[i] = curMinDist;
				indexCentroids[i] = j;
			}
		}
	}
}

void kMeansClusterization(int k)
{
	//centroids = initializeCentroids(k);
	centroids = initializeCentroidsOpt(k);
	int iterations = 0;
	std::vector<std::pair<double, double>> oldCentroids(k, { -1,-1 });
	while (!(shouldStop(oldCentroids, centroids, iterations)))
	{
		oldCentroids = centroids;
		iterations++;

		assignPointsToCentroids(centroids);
		updateCentroids();
		updatePoints();
	}
}

double intraClusterDistance()
{
	std::vector<double> sumWithinClusters;
	sumWithinClusters.resize(centroids.size(), 0.0);
	for (int i = 0; i < indexCentroids.size(); i++)
	{
		sumWithinClusters[indexCentroids[i]] += distance(data[i], centroids[indexCentroids[i]]);
	}

	double inertia = 0.0;
	for (int i = 0; i < sumWithinClusters.size(); i++)
	{
		inertia += sumWithinClusters[i];
	}

	return inertia;
}

void kMeansRandomRestart(int clusters)
{
	kMeansClusterization(clusters);
	double curBestDistance = intraClusterDistance();
	std::vector<std::pair<double, double>> curBestCentroids = centroids;
	std::vector<int> curBestInd = indexCentroids;
	centroids.clear();
	minDists.clear();
	indexCentroids.clear();

	minDists.resize(data.size(), INT32_MAX);
	indexCentroids.resize(data.size(), -1);

	for (int i = 0; i < RANDOM_ITERATIONS; i++)
	{
		kMeansClusterization(clusters);
		double curDistance = intraClusterDistance();
		std::vector<std::pair<double, double>> curCentroids = centroids;
		if (curDistance < curBestDistance)
		{
			curBestDistance = curDistance;
			curBestCentroids = curCentroids;
			curBestInd = indexCentroids;
		}
		centroids.clear();
		minDists.clear();
		indexCentroids.clear();

		minDists.resize(data.size(), INT32_MAX);
		indexCentroids.resize(data.size(), -1);
	}

	indexCentroids = curBestInd;
	writeData("output.csv");

}

int main()
{
	std::string inputFile;
	std::cin >> inputFile;
	int clusters;
	std::cin >> clusters;

	readData(inputFile);
	minDists.resize(data.size(), INT32_MAX);
	indexCentroids.resize(data.size(), -1);
	kMeansRandomRestart(clusters);
	//kMeansClusterization(clusters);

	return system("pause");
}