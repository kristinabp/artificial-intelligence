#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<math.h>
#include<algorithm>
#include<chrono>
#include<random>

#define ATTRIBUTES 9

struct FreaquencyTable
{
	std::string attribute;
	std::vector<std::string> values;
	std::vector<std::vector<int>> table;
	double entropyy = 0;
};

std::vector<std::string> attributes = { "age", "menopause", "tumor-size", "inv-nodes",
									  "node-caps", "deg-malig", "breast", "breast-quad", "irradiat" };
std::vector<std::vector<std::string>> attrVal = { {"10-19", "20-29", "30-39", "40-49", "50-59", "60-69", "70-79", "80-89", "90- 99"},
	{"lt40", "ge40", "premeno"},
	{"0-4", "5-9", "10-14", "15-19", "20-24", "25-29", "30-34", "35-39", "40-44", "45-49", "50-54", "55-59"},
	{"0-2", "3-5", "6-8", "9-11", "12-14", "15-17", "18-20", "21-23", "24-26", "27-29", "30-32", "33-35", "36-39"},
	{"yes", "no", "?"}, {"1", "2", "3"}, {"left", "right", "?"}, {"left_up", "left_low", "right_up", "right_low", "central", "?"},
	{"yes", "no"} };

std::vector<std::vector<std::string>> data;
std::vector<double> allEntropy;
std::vector<double> gain;

struct Node
{
	std::string attribute;
	std::vector<std::string> values;
	Node* next;
};


void readData(const std::string fileName)
{
	std::fstream file(fileName, std::ios::in);
	if (file.is_open())
	{
		std::vector<std::string> row;
		std::string line, word;
		while (std::getline(file, line))
		{
			row.clear();

			std::stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			data.push_back(row);
		}
	}
	else
		std::cout << "Could not open the file\n";

	file.close();
}

double entropy(int a, int b)
{
	if (a == 0 || b == 0)
		return 0;
	return -((a * 1.0 / (a + b) * 1.0) * log2((a * 1.0 / (a + b) * 1.0))) - ((b * 1.0 / (a + b) * 1.0) * log2((b * 1.0 / (a + b) * 1.0)));
}

std::pair < std::vector<FreaquencyTable>, double> makeFreqTables(std::vector<std::vector<std::string>> curData)
{
	std::vector<FreaquencyTable> curTable;
	int classCount1 = 0;
	int classCount2 = 0;
	for (int i = 0; i < curData.size(); i++)
	{
		if (curData[i][0][0] == 'n')
			classCount1++;
		else classCount2++;
	}

	double classEntropy = entropy(classCount1, classCount2);

	for (int i = 1; i < ATTRIBUTES + 1; i++)
	{
		FreaquencyTable curFreqTable;
		curFreqTable.attribute = attributes[i - 1];
		curFreqTable.values = attrVal[i - 1];
		curFreqTable.table.resize(curFreqTable.values.size());
		for (int j = 0; j < curFreqTable.values.size(); j++)
		{
			curFreqTable.table[j].resize(2, 0);
		}

		for (int j = 0; j < curData.size(); j++)
		{
			for (int k = 0; k < curFreqTable.values.size(); k++)
			{
				if (curData[j][i] == curFreqTable.values[k])
				{
					if (curData[j][0][0] == 'n')
					{
						curFreqTable.table[k][0]++; //index 0 is for no-recurrence-events
					}
					else
					{
						curFreqTable.table[k][1]++; // index 1 is for recurrence-events
					}
					break;
				}
			}
		}

		for (int j = 0; j < curFreqTable.values.size(); j++)
		{
			curFreqTable.entropyy += ((curFreqTable.table[j][0] + curFreqTable.table[j][1]) * 1.0 / (classCount1 + classCount2) * 1.0) * entropy(curFreqTable.table[j][0], curFreqTable.table[j][1]);
		}
		curTable.push_back(curFreqTable);
		allEntropy.push_back(curFreqTable.entropyy);
	}
	return { curTable, classEntropy };
}

void calcGain(double e, std::vector<FreaquencyTable> t)
{
	for (int i = 0; i < attributes.size(); i++)
	{
		double gainn = e - t[i].entropyy;
		gain.push_back(gainn);
	}
}

int findIndex(std::vector<double> gainn)
{
	int index = 0;
	double curBest = gainn[0];
	for (int i = 1; i < gainn.size(); i++)
	{
		if (gainn[i] > curBest)
		{
			curBest = gainn[i];
			index = i;
		}
	}

	return index;
}

void constructDesicionTree(std::vector<std::vector<std::string>> curData)
{
	std::pair< std::vector<FreaquencyTable>, double> dataInf = makeFreqTables(curData);
	std::vector<FreaquencyTable> curDataFreq = dataInf.first;
	double curEntropyOfTarget = dataInf.second;
	if (curEntropyOfTarget == 0)
		return;
	calcGain(curEntropyOfTarget, curDataFreq);
	int indexOfCurAttr = findIndex(gain);
	std::cout << "Current node attribute is: " << attributes[indexOfCurAttr] << " with gain: " << gain[indexOfCurAttr] << "\n";

	std::vector< std::vector<std::vector<std::string>>> newSubSets;
	newSubSets.resize(attrVal[indexOfCurAttr].size());
	for (int i = 0; i < curData.size(); i++)
	{
		for (int j = 0; j < attrVal[indexOfCurAttr].size(); j++)
		{
			if (curData[i][indexOfCurAttr + 1] == attrVal[indexOfCurAttr][j])
			{
				newSubSets[j].push_back(curData[i]);
			}
		}
	}

	allEntropy.clear();
	gain.clear();
}

int main()
{
	readData("breast-cancer.csv");
	constructDesicionTree(data);
	return system("pause");
}