#pragma once

struct Game
{
	int id;
	int maxRed = 0;
	int maxGreen = 0;
	int maxBlue = 0;

	bool isPossible(int red, int green, int blue)
	{
		return maxRed <= red && maxGreen <= green && maxBlue <= blue;
	}

	void setRed(int value)
	{
		if (value > maxRed)
		{
			maxRed = value;
		}
	}

	void setGreen(int value)
	{
		if (value > maxGreen)
		{
			maxGreen = value;
		}
	}

	void setBlue(int value)
	{
		if (value > maxBlue)
		{
			maxBlue = value;
		}
	}

	int getPower()
	{
		return maxRed * maxGreen * maxBlue;
	}
};

