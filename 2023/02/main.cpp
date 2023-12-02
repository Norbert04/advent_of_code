#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Game.hpp"

Game generateGame(std::string line);

int main()
{
	std::vector <Game> games;
	std::ifstream file("input.txt");
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			games.push_back(generateGame(line));
		}
		file.close();
	}
	else
	{
		return -1;
	}

	int sumOfGameIDs = 0;

	for (Game game : games)
	{
		if (game.isPossible(12,13,14))
		{
			sumOfGameIDs += game.id;
		}
	}

	std::cout << sumOfGameIDs << "\n";

	int sumOfPower = 0;

	for (Game game : games)
	{
		sumOfPower += game.getPower();
	}

	std::cout << sumOfPower << "\n";
}

Game generateGame(std::string line)
{
	Game game = {};
	std::string gameId, gameInformation;
	gameId = line.substr(0, line.find(':'));
	{
		std::string temp;
		for (int i = 5; isdigit(gameId[i]); i++)
		{
			temp += gameId[i];
		}
		game.id = std::stoi(temp);
	}
	gameInformation = line.substr(line.find(':') + 1, line.size());
	for (int i = 0; i < gameInformation.size(); i++)
	{
		if (isdigit(gameInformation[i]))
		{
			int lengthOfNumber = isdigit(gameInformation[i + 1]) ? 2 : 1;
			int number = std::stoi(gameInformation.substr(i, lengthOfNumber));
			switch (gameInformation[i + lengthOfNumber + 1])
			{
			case 'r':
				i += lengthOfNumber + 3;
				game.setRed(number);
				break;
			case 'g':
				i += lengthOfNumber + 5;
				game.setGreen(number);
				break;
			case 'b':
				i += lengthOfNumber + 4;
				game.setBlue(number);
				break;
			default:
				break;
			}
		}
	}

	return game;
}