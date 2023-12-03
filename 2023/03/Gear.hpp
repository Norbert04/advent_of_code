#pragma once

struct Gear
{
	int partNumberCount = 0;
	std::vector<int> partNumbers;
	int getGearRatio()
	{
		//returns 0 if it is no gear
		return partNumberCount == 2 ? partNumbers[0] * partNumbers[1] : 0;
	}
};
