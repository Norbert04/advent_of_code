#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main()
{
	std::string numbers[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	std::vector <std::string> input;
	std::ifstream file("input.txt");
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			input.push_back(line);
		}
		file.close();
	}
	else
	{
		return -1;
	}

	int result = 0;

	for (int i = 0; i < input.size(); i++)
	{
		int first = -1;
		int last = -1;
		for (char ch : input[i])
		{
			if (isdigit(ch))
			{
				if (first != -1)
					last = ch - '0';
				else
				{
					first = ch - '0';
					last = ch - '0';
				}
			}
		}
		result += first * 10 + last;
	}

	std::cout << "Part 1: " << result << "\n";

	result = 0;

	for (int i = 0; i < input.size(); i++)
	{
		int first = -1;
		int firstPos = -1;
		int last = -1;
		int lastPos = -1;

		for (int j = 0; j < 10; j++)
		{
			std::string number = numbers[j];
			if (first == -1 && input[i].find(number) != std::string::npos)
			{
				first = j;
				lastPos = input[i].find(number);
				firstPos = lastPos;
				last = j;
			}
			if (input[i].find(number) < firstPos)
			{
				firstPos = input[i].find(number);
				first = j;
			}
			if (input[i].rfind(number) > lastPos && input[i].rfind(number) != std::string::npos)
			{
				lastPos = input[i].rfind(number);
				last = j;
			}
		}

		for (int ch = 0; ch < input[i].size(); ch++)
		{
			char currentCharacter = input[i][ch];
			if (isdigit(currentCharacter))
			{
				if (first == -1)
				{
					first = currentCharacter - '0';
					last = currentCharacter - '0';
				}
				else if (ch > lastPos)
				{
					lastPos = ch;
					last = currentCharacter - '0';
				}
				else if (ch < firstPos)
				{
					firstPos = ch;
					first = currentCharacter - '0';
				}
			}
		}
		result += first * 10 + last;
	}
	std::cout << "Part 2: " << result << "\n";
}