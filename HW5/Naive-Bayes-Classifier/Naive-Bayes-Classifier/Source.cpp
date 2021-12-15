#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>
#include<map>
#include<math.h>
#include<algorithm>
#include<random>
#include<chrono>

struct TableOfLikelihoods
{
	std::string attribute;

	int numberOfDemocrats = 0;
	int numberOfRepublicans = 0;

	int numberOfDemocratsSaidYes = 0;
	int numberOfDemocratsSaidNo = 0;

	int numberOfRepublicansSaidYes = 0;
	int numberOfRepublicansSaidNo = 0;

	std::vector<float> probabilityOfDemocrats; //0-no, 1-yes, 2-?
	std::vector<float> probabilityOfRepublicans; //0-no, 1-yes, 2-?
};

std::vector<std::vector<char>> data;
std::vector<std::string> attributes = { "handicapped-infants", "water-project-cost-sharing",
"adoption-of-the-budget-resolution", "physician-fee-freeze", "el-salvador-aid", "religious-groups-in-schools",
"anti-satellite-test-ban", "aid-to-nicaraguan-contras", "mx-missile", "immigration",
"synfuels-corporation-cutback", "education-spending", "superfund-right-to-sue", "crime",
"duty-free-exports", "export-administration-act-south-africa" };

double probabilityOfBeingDemocrat;
double probabilityOfBeingRepublican;


void readData(const std::string fileName)
{
	std::fstream inputFile;
	inputFile.open(fileName, std::ios::in);
	if (inputFile.is_open())
	{
		std::string line;
		int curLine = 0;
		while (std::getline(inputFile, line)) {
			data.push_back({});
			std::string classs;
			int index = 0;
			while (line[index] != ',')
			{
				classs.push_back(line[index]);
				index++;
			}
			index++;

			data[curLine].push_back(classs[0]);

			while (index < line.size())
			{
				if (line[index] != ',')
					data[curLine].push_back(line[index]);
				index++;
			}

			classs.clear();
			curLine++;
		}
		inputFile.close();
	}
	else
	{
		std::cout << "Couldn't open " << fileName << "\n";
		inputFile.close();
	}
}

std::vector<TableOfLikelihoods> calculateProbabilities(std::vector<std::vector<char>> dataSet)
{
	std::vector<TableOfLikelihoods> tableOfProbabilities;
	for (int col = 1; col < 17; col++)
	{
		TableOfLikelihoods curTable;
		for (int row = 0; row < dataSet.size(); row++)
		{
			curTable.attribute = attributes[col - 1];
			if (dataSet[row][0] == 'r')
			{
				curTable.numberOfRepublicans++;
				if (dataSet[row][col] == 'y')
					curTable.numberOfRepublicansSaidYes++;
				else if (dataSet[row][col] == 'n')
					curTable.numberOfRepublicansSaidNo++;
			}
			if (dataSet[row][0] == 'd')
			{
				curTable.numberOfDemocrats++;
				if (dataSet[row][col] == 'y')
					curTable.numberOfDemocratsSaidYes++;
				else if (dataSet[row][col] == 'n')
					curTable.numberOfDemocratsSaidNo++;
			}
		}
		curTable.probabilityOfDemocrats.push_back(curTable.numberOfDemocratsSaidNo * 1.0 / curTable.numberOfDemocrats * 1.0);
		curTable.probabilityOfDemocrats.push_back(curTable.numberOfDemocratsSaidYes * 1.0 / curTable.numberOfDemocrats * 1.0);
		curTable.probabilityOfDemocrats.push_back((curTable.numberOfDemocrats - (curTable.numberOfDemocratsSaidNo + curTable.numberOfDemocratsSaidYes)) * 1.0 / curTable.numberOfDemocrats * 1.0);

		curTable.probabilityOfRepublicans.push_back(curTable.numberOfRepublicansSaidNo * 1.0 / curTable.numberOfRepublicans * 1.0);
		curTable.probabilityOfRepublicans.push_back(curTable.numberOfRepublicansSaidYes * 1.0 / curTable.numberOfRepublicans * 1.0);
		curTable.probabilityOfRepublicans.push_back((curTable.numberOfRepublicans - (curTable.numberOfRepublicansSaidNo + curTable.numberOfRepublicansSaidYes)) * 1.0 / curTable.numberOfRepublicans * 1.0);

		tableOfProbabilities.push_back(curTable);
	}

	probabilityOfBeingDemocrat = tableOfProbabilities[0].numberOfDemocrats * 1.0 / (tableOfProbabilities[0].numberOfDemocrats + tableOfProbabilities[0].numberOfRepublicans) * 1.0;
	probabilityOfBeingRepublican = tableOfProbabilities[0].numberOfRepublicans * 1.0 / (tableOfProbabilities[0].numberOfDemocrats + tableOfProbabilities[0].numberOfRepublicans) * 1.0;

	return tableOfProbabilities;
}

char findClass(std::vector<char> testData, std::vector<TableOfLikelihoods> trainDataProb)
{
	double probabilityRep = 0;
	double probabilityDem = 0;

	for (int i = 1; i < testData.size(); i++)
	{
		if (testData[i] == 'y')
		{
			probabilityRep += log(trainDataProb[i-1].probabilityOfRepublicans[1]);
			probabilityDem += log(trainDataProb[i-1].probabilityOfDemocrats[1]);
		}
		else if (testData[i] == 'n')
		{
			probabilityRep += log(trainDataProb[i-1].probabilityOfRepublicans[0]);
			probabilityDem += log(trainDataProb[i-1].probabilityOfDemocrats[0]);
		}
		else
		{
			probabilityRep += log(trainDataProb[i-1].probabilityOfRepublicans[2]);
			probabilityDem += log(trainDataProb[i-1].probabilityOfDemocrats[2]);
		}
	}

	if (probabilityDem > probabilityRep)
		return 'd';
	else
		return 'r';
}

void handleMissingValues()
{
	//Imputation method for categorical columns 
	for (int col = 1; col < 17; col++)
	{
		int countYes = 0;
		int countNo = 0;
		std::vector<int> missingValueIndixes;
		for (int row = 0; row < data.size(); row++)
		{

			if (data[row][col] == 'y')
				countYes++;
			else if (data[row][col] == 'n')
				countNo++;
			else
				missingValueIndixes.push_back(row);
		}

		for (int i = 0; i < missingValueIndixes.size(); i++)
		{
			data[missingValueIndixes[i]][col] = countYes > countNo ? 'y' : 'n';
		}
	}
}


void kFoldCrossValidation(int k)
{
	std::vector<int> shuffledIndexesOfTheData;

	double allAcc = 0;

	for (int i = 0; i < data.size(); i++)
	{
		shuffledIndexesOfTheData.push_back(i);
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(shuffledIndexesOfTheData.begin(), shuffledIndexesOfTheData.end(), std::default_random_engine(seed));

	std::vector<std::vector<int>> folds;
	folds.resize(k);
	int foldSize = 0;
	int foldIndex = 0;
	for (int i = 0; i < shuffledIndexesOfTheData.size(); i++)
	{
		folds[foldIndex].push_back(shuffledIndexesOfTheData[i]);
		if (foldSize == (shuffledIndexesOfTheData.size() / k + 1))
		{
			foldSize = 0;
			foldIndex++;
		}
		foldSize++;
	}

	for (int i = 0; i < k; i++)
	{
		std::vector<int> testDataInd = folds[i];
		std::vector<std::vector<int>> trainDataInd;
		for (int j = 0; j < k; j++)
		{
			if (j != i)
			{
				trainDataInd.push_back(folds[j]);
			}
		}

		std::vector<std::vector<char>> trainingData;
		for (int j = 0; j < trainDataInd.size(); j++)
		{
			for (int l = 0; l < trainDataInd[j].size(); l++)
			{
				trainingData.push_back(data[trainDataInd[j][l]]);
			}
		}

		std::vector<std::vector<char>> testingData;
		for (int j = 0; j < testDataInd.size(); j++)
		{
			testingData.push_back(data[testDataInd[j]]);
		}

		std::vector<TableOfLikelihoods> probabilities = calculateProbabilities(trainingData);

		int countRightGuesses = 0;
		for (int j = 0; j < testingData.size(); j++)
		{
			char curClass = findClass(testingData[j], probabilities);
			if (curClass == testingData[j][0])
				countRightGuesses++;
		}
		allAcc += countRightGuesses * 1.0 / testingData.size() * 1.0 * 100;
		std::cout << "Accuracy of " << i+1 << " training is " << countRightGuesses * 1.0 / testingData.size() * 1.0 * 100 << "\n";
	}
	std::cout << "Accuracy of all trainings is " << allAcc/k << "\n";
}

void printData()
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			std::cout << data[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

int main()
{
	readData("house-votes-84.data");
	handleMissingValues();
	kFoldCrossValidation(10);

	return system("pause");
}