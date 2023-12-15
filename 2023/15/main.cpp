#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

int getHashValue(std::string& str);

int main()
{
	std::vector <std::string> steps;
	std::ifstream file("input.txt");
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		std::replace_if(line.begin(), line.end(), [](const char& c) {return c == ','; }, ' ');
		std::istringstream temp(line);
		std::string step;
		while (temp >> step)
		{
			steps.push_back(step);
		}
		file.close();
	}
	else
	{
		return -1;
	}

	int sumOfResults = 0;

	for (std::string step : steps)
	{
		sumOfResults += getHashValue(step);
	}

	std::cout << sumOfResults << "\n";
}

int getHashValue(std::string& str)
{
	int currentValue = 0;
	for (char ch : str)
	{
		currentValue += (int)ch;
		currentValue *= 17;
		currentValue %= 256;
	}
	return currentValue;
}