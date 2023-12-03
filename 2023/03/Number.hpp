#pragma once
#include "Gear.hpp"

bool isSymbol(std::vector<std::string>& input, int line, int position, std::vector<Gear>& gears, int partNumberValue)
{
	if (line <0 || position<0 ||
		line > input.size() - 1 || position>input[line].size() - 1)
	{
		return false;
	}
	if (input[line][position] == '*')
	{
		int gearPosition = line * input[line].size() + position;
		gears[gearPosition].partNumberCount++;
		gears[gearPosition].partNumbers.push_back(partNumberValue);
	}
	return input[line][position] != '.' && !isdigit(input[line][position]);
}

struct Number
{
	int value = 0;
	int line = 0;
	int position = 0;
	int length = 0;

	bool isPartNumber(std::vector<std::string>& input, std::vector<Gear>& gears)
	{
		for (int digit = 0; digit < length; digit++)
		{
			int digitPos = position + digit;
			if (isSymbol(input, line, digitPos - 1, gears, value) ||
				isSymbol(input, line, digitPos + 1, gears, value) ||
				isSymbol(input, line - 1, digitPos, gears, value) ||
				isSymbol(input, line + 1, digitPos, gears, value) ||
				isSymbol(input, line - 1, digitPos - 1, gears, value) ||
				isSymbol(input, line + 1, digitPos - 1, gears, value) ||
				isSymbol(input, line - 1, digitPos + 1, gears, value) ||
				isSymbol(input, line + 1, digitPos + 1, gears, value))
				return true;
		}
		return false;
	}
};
