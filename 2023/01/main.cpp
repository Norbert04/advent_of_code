#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

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
			if (first == -1 && input[i].find(numbers[j]) != std::string::npos)
			{
				first = j;
				lastPos = input[i].find(numbers[j]);
				firstPos = lastPos;
				last = j;
			}
			if (input[i].find(numbers[j]) < firstPos)
			{
				firstPos = input[i].find(numbers[j]);
				first = j;
			}
			if (input[i].rfind(numbers[j]) > lastPos && input[i].rfind(numbers[j]) != std::string::npos)
			{
				lastPos = input[i].rfind(numbers[j]);
				last = j;
			}
		}

		for (int ch = 0; ch < input[i].size(); ch++)
		{
			if (isdigit(input[i][ch]))
			{
				if (first == -1)
				{
					first = input[i][ch] - '0';
					last = input[i][ch] - '0';
				}
				else if (ch > lastPos)
				{
					last = input[i][ch] - '0';
					lastPos = ch;
				}
				else if (ch < firstPos)
				{
					firstPos = ch;
					first = input[i][ch] - '0';
				}
			}
		}
		result += first * 10 + last;
	}
	std::cout << "Part 2: " << result << "\n";
}