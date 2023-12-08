#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

#define LEFT true
#define RIGHT false

int main()
{
	std::vector<bool> instructions;
	std::unordered_map < std::string, std::pair<std::string, std::string>> nodes;
	std::vector<std::string> nodeNames;
	std::ifstream file("input.txt");
	if (file.is_open())
	{
		std::string line;

		std::getline(file, line);
		for (char ch : line)
		{
			switch (ch)
			{
			case 'L':
				instructions.push_back(LEFT);
				break;
			case 'R':
				instructions.push_back(RIGHT);
				break;
			default:
				break;
			}
		}

		std::getline(file, line);

		while (std::getline(file, line))
		{
			std::pair<std::string, std::string> temp(line.substr(7, 3), line.substr(12, 3));
			std::string node = line.substr(0, 3);
			nodeNames.push_back(node);
			nodes.insert(std::pair<std::string, std::pair<std::string, std::string>>(node, temp));
		}
		file.close();
	}
	else
	{
		return -1;
	}

	int numberOfSteps = 0;

	int currentInstructionIndex = 0;
	std::string currentElement = "AAA";

	while (currentElement != "ZZZ")
	{
		numberOfSteps++;

		if (instructions[currentInstructionIndex])
			currentElement = nodes[currentElement].first;
		else
			currentElement = nodes[currentElement].second;

		currentInstructionIndex++;
		if (currentInstructionIndex >= instructions.size())
			currentInstructionIndex = 0;
	}

	std::cout << numberOfSteps << "\n";
}