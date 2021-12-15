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
	double entropyy = 0;
};

std::vector<std::vector<std::string>> data;
std::vector<FreaquencyTable> allTables;
std::vector<std::string> attributes = { "outlook", "temp", "humidity", "wind" };
std::vector<std::vector<std::string>> attrVal = { {"rainy", "overcost", "sunny"}, {"hot","mild", "cool"}, {"high", "normal"}, {"TRUE", "FALSE"} };

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

	for (int i = 1; i < 5; i++)
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
			curFreqTable.entropyy += ((curFreqTable.table[j][0] + curFreqTable.table[j][1]) * 1.0 / (curNumForClass1 + curNumForClass2) * 1.0) * entropy(curFreqTable.table[j][0], curFreqTable.table[j][1]);
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
		std::cout << "---------------------------------------------\n";
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
	readData("data.csv");
	makeFreqTables(data);
	printFreqData();
	entropyOfTarget = entropy(curNumForClass1, curNumForClass2);
	calcGain();
	for (int i = 0; i < gain.size(); i++)
	{
		std::cout << gain[i] << " ";
	}
	return system("pause");
}