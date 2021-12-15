#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<math.h>
#include<algorithm>

struct FreaquencyTable
{
	std::string attribute;
	std::vector<std::string> values;
	std::vector<std::vector<int>> table;
	double entropyy=0;
};

std::vector<std::vector<std::string>> data;
std::vector<FreaquencyTable> allTables;
std::vector<std::string> attributes = { "age", "menopause", "tumor-size", "inv-nodes",
									  "node-caps", "deg-malig", "breast", "breast-quad", "irradiat" };
std::vector<std::vector<std::string>> attrVal = { {"10-19", "20-29", "30-39", "40-49", "50-59", "60-69", "70-79", "80-89", "90- 99"},
	{"lt40", "ge40", "premeno"},
	{"0-4", "5-9", "10-14", "15-19", "20-24", "25-29", "30-34", "35-39", "40-44", "45-49", "50-54", "55-59"},
	{"0-2", "3-5", "6-8", "9-11", "12-14", "15-17", "18-20", "21-23", "24-26", "27-29", "30-32", "33-35", "36-39"},
	{"yes", "no", "?"}, {"1", "2", "3"}, {"left", "right", "?"}, {"left-up", "left-low", "right-up", "right-low", "central", "?"},
	{"yes", "no"} };

double entropyOfTarget;
int curNumForClass1 = 0;
int curNumForClass2 = 0;
std::vector<double> allEntropy;
std::vector<double> gain;

double entropy(int a, int b)
{
	if (a == 0 || b == 0)
		return 0;
	return -((a * 1.0 / (a + b) * 1.0) * log2((a * 1.0 / (a + b) * 1.0))) - ((b * 1.0 / (a + b) * 1.0) * log2((b * 1.0 / (a + b) * 1.0)));
}

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

void makeFreqTables(std::vector<std::vector<std::string>> curData)
{
	for (int i = 0; i < curData.size(); i++)
	{
		if (curData[i][0][0] == 'n')
			curNumForClass1++;
		else curNumForClass2++;
	}

	for (int i = 1; i < 10;  i++)
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
			curFreqTable.entropyy +=( (curFreqTable.table[j][0] + curFreqTable.table[j][1]) * 1.0 / (curNumForClass1 + curNumForClass2) * 1.0)* entropy(curFreqTable.table[j][0], curFreqTable.table[j][1]);
		}
		allTables.push_back(curFreqTable);
		allEntropy.push_back(curFreqTable.entropyy);
	}

}

void printFreqData()
{
	for (int i = 0; i < allTables.size(); i++)
	{
		std::cout << allTables[i].attribute << "\n";
		std::cout << allTables[i].entropyy << "\n";
		for (int j = 0; j < allTables[i].table.size(); j++)
		{
			std::cout << attrVal[i][j] << ": ";
			for (int k = 0; k < allTables[i].table[j].size(); k++)
			{
				std::cout << allTables[i].table[j][k] << " ";
			}
			std::cout << "\n";
		}
		std::cout <<"---------------------------------------------\n";
	}
}

void calcGain()
{
	for (int i = 0; i < attributes.size(); i++)
	{
		double gainn = entropyOfTarget - allTables[i].entropyy;
		gain.push_back(gainn);
	}
}

int main()
{
	readData("breast-cancer.csv");
	makeFreqTables(data);
	printFreqData();
	entropyOfTarget = entropy(curNumForClass1, curNumForClass2);
	calcGain();
	return system("pause");
}