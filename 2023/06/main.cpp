#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

struct Race
{
	uint64_t time = 0;
	uint64_t recordDistance = 0;
};

int getNumberOfWinningTimes(Race race);

int main()
{
	std::vector <Race> races;
	Race racePart2;
	std::ifstream file("input.txt");
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		std::string temp = "Time: ";
		std::istringstream times(line.substr(temp.size(), line.size()));

		int time;
		while (times >> time)
		{
			Race race;
			race.time = time;
			races.push_back(race);

			racePart2.time *= pow(10, ((int)log10(time) + 1));
			racePart2.time += time;
		}

		std::getline(file, line);
		temp = "Distance: ";
		std::istringstream distances(line.substr(temp.size(), line.size()));

		int distance;
		int i = 0;
		while (distances >> distance)
		{
			races[i].recordDistance = distance;
			++i;

			racePart2.recordDistance *= pow(10, ((int)log10(distance) + 1));
			racePart2.recordDistance += distance;
		}

		file.close();
	}
	else
	{
		return -1;
	}

	uint64_t marginOfError = 1;

	for (Race race : races)
	{
		marginOfError *= getNumberOfWinningTimes(race);
	}

	std::cout << marginOfError << "\n";

	std::cout << getNumberOfWinningTimes(racePart2) << "\n";
}

int getNumberOfWinningTimes(Race race)
{
	// maximal distance when pressing the button for half of the allowed time.
	double optimalTime = (double)race.time / 2;
	uint64_t minimalWinningTime = 1;
	while (minimalWinningTime < optimalTime &&
		(race.time - minimalWinningTime) * minimalWinningTime <= race.recordDistance)
		++minimalWinningTime;
	return (int)((optimalTime - minimalWinningTime) * 2) + 1;
}