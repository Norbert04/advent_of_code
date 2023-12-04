#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

int main()
{
	std::vector<int> numberOfPoints;
	std::vector<int> numberOfWinningNumbers;
	std::ifstream file("input.txt");
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::istringstream winning(line.substr(9, line.find('|') - 9));
			std::vector<int> winningPoints;
			std::string temp;
			int winningNumbers = 0;
			while (winning >> temp)
			{
				winningPoints.push_back(std::stoi(temp));
			}
			std::istringstream numbers(line.substr(line.find('|') + 1, line.size()));
			while (numbers >> temp)
			{
				if (std::find(winningPoints.begin(), winningPoints.end(), std::stoi(temp)) != winningPoints.end())
				{
					winningNumbers++;
				}
			}
			int points = winningNumbers == 0 ? 0 : (int)pow(2, winningNumbers - 1);
			numberOfPoints.push_back(points);
			numberOfWinningNumbers.push_back(winningNumbers);
		}
		file.close();
	}
	else
	{
		return -1;
	}

	int sumOfPoints = 0;

	for (int i : numberOfPoints)
	{
		sumOfPoints += i;
	}

	std::cout << sumOfPoints << "\n";

	std::vector<int> numberOfCards;
	numberOfCards.resize(numberOfWinningNumbers.size());
	for (int i = 0; i < numberOfWinningNumbers.size(); i++)
	{
		numberOfCards[i] = 1;
	}
	for (int i = 0; i < numberOfWinningNumbers.size(); i++)
	{
		for (int k = 0; k < numberOfCards[i]; k++)
		{
			for (int j = 1; j <= numberOfWinningNumbers[i] && i + j < numberOfWinningNumbers.size(); j++)
			{
				numberOfCards[i + j]++;
			}
		}
	}

	int solution2 = 0;
	for (int i : numberOfCards)
	{
		solution2 += i;
	}
	std::cout << solution2 << "\n";
}