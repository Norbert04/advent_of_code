#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

int predictNextValue(std::vector<int>& sequence);
int predictPreviousValue(std::vector<int>& sequence);

int main()
{
	std::vector <std::vector<int>> input;
	std::ifstream file("input.txt");
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::vector<int> history;
			std::istringstream historyStream(line);
			int temp;

			while (historyStream >> temp)
			{
				history.push_back(temp);
			}

			input.push_back(history);
		}
		file.close();
	}
	else
	{
		return -1;
	}

	int sumOfPredictions = 0;

	for (std::vector<int> sequence : input)
	{
		sumOfPredictions += predictNextValue(sequence);
	}

	std::cout << sumOfPredictions << "\n";

	sumOfPredictions = 0;

	for (std::vector<int> sequence : input)
	{
		sumOfPredictions += predictPreviousValue(sequence);
	}

	std::cout << sumOfPredictions << "\n";
}


int predictNextValue(std::vector<int>& sequence)
{
	std::vector<int> difference;

	for (int i = 0; i < sequence.size() - 1; i++)
	{
		difference.push_back(sequence[i + 1] - sequence[i]);
	}

	bool allZero = true;

	for (int i : difference)
	{
		if (i != 0)
			allZero = false;
	}

	if (allZero)
		return sequence.back();
	else
		return sequence.back() + predictNextValue(difference);
}

int predictPreviousValue(std::vector<int>& sequence)
{
	std::vector<int> difference;

	for (int i = 0; i < sequence.size() - 1; i++)
	{
		difference.push_back(sequence[i + 1] - sequence[i]);
	}

	bool allZero = true;

	for (int i : difference)
	{
		if (i != 0)
			allZero = false;
	}

	if (allZero)
		return sequence.front();
	else
		return sequence.front() - predictPreviousValue(difference);
}