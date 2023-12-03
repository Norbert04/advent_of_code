#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Number.hpp"
#include "Gear.hpp"

std::vector<Number> getNumbers(std::vector<std::string> input);

int main()
{
	std::vector<std::string> input;
	std::vector<Number> numbers;
	std::vector<Gear> gears;
	std::ifstream file("input.txt");
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			input.push_back(line);
			for (int i = 0; i < line.size(); i++)
			{
				Gear gear;
				gears.push_back(gear);
			}
		}
		file.close();
	}
	else
	{
		return -1;
	}

	numbers = getNumbers(input);

	int sumOfPartNumbers = 0;

	for (Number number : numbers)
	{
		if (number.isPartNumber(input, gears))
		{
			sumOfPartNumbers += number.value;
		}
	}

	std::cout << sumOfPartNumbers << "\n";

	int sumOfGearRatios = 0;

	for (int i = 0; i < gears.size(); i++)
	{
		sumOfGearRatios += gears[i].getGearRatio();
	}

	std::cout << sumOfGearRatios << "\n";
}

std::vector<Number> getNumbers(std::vector<std::string> input)
{
	std::vector<Number> numbers;
	for (int line = 0; line < input.size(); line++)
	{
		for (int i = 0; i < input[line].size(); i++)
		{
			if (isdigit(input[line][i]))
			{
				Number number;
				number.line = line;
				number.position = i;
				for (; i < input[line].size() && isdigit(input[line][i]); i++)
				{
					number.length++;
					number.value *= 10;
					number.value += input[line][i] - '0';
				}
				numbers.push_back(number);
			}
		}
	}
	return numbers;
}