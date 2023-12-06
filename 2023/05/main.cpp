#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

enum Map { seedSoil, soilFertilizer, fertilizerWater, waterLight, lightTemperature, temperatureHumidity, humidityLocation };

struct range
{
	unsigned int sourceStart = 0;
	unsigned int destinationStart = 0;
	unsigned int length = 0;
};

unsigned int convert(unsigned int value, std::vector<range> map);

int main()
{
	std::unordered_map<Map, std::vector<range>> conversions;
	std::vector <unsigned int> seeds;
	std::ifstream file("input.txt");
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		std::string temp = "seeds:";
		Map currentMap;
		std::istringstream seedValues(line.substr(temp.size(), line.size()));
		while (seedValues >> temp)
		{
			seeds.push_back(std::stoul(temp));
		}
		while (std::getline(file, line))
		{
			if (line != "")
			{
				if (line == "seed-to-soil map:")
					currentMap = seedSoil;
				else if (line == "soil-to-fertilizer map:")
					currentMap = soilFertilizer;
				else if (line == "fertilizer-to-water map:")
					currentMap = fertilizerWater;
				else if (line == "water-to-light map:")
					currentMap = waterLight;
				else if (line == "light-to-temperature map:")
					currentMap = lightTemperature;
				else if (line == "temperature-to-humidity map:")
					currentMap = temperatureHumidity;
				else if (line == "humidity-to-location map:")
					currentMap = humidityLocation;
				else
				{
					range currentRange;
					std::istringstream rangeStream(line);
					rangeStream >> currentRange.destinationStart;
					rangeStream >> currentRange.sourceStart;
					rangeStream >> currentRange.length;

					conversions[currentMap].push_back(currentRange);
				}
			}
		}
		file.close();
	}
	else
	{
		return -1;
	}

	unsigned int lowerstLocationNumber = UINT32_MAX;

	for (unsigned int seed : seeds)
	{
		unsigned int soil = convert(seed, conversions[seedSoil]);
		unsigned int fertilizer = convert(soil, conversions[soilFertilizer]);
		unsigned int water = convert(fertilizer, conversions[fertilizerWater]);
		unsigned int light = convert(water, conversions[waterLight]);
		unsigned int temperature = convert(light, conversions[lightTemperature]);
		unsigned int humidity = convert(temperature, conversions[temperatureHumidity]);
		unsigned int location = convert(humidity, conversions[humidityLocation]);
		if (location < lowerstLocationNumber)
		{
			lowerstLocationNumber = location;
		}
	}
	std::cout << lowerstLocationNumber << "\n";
}

unsigned int convert(unsigned int value, std::vector<range> map)
{
	for (range currentRange : map)
	{
		if (value > currentRange.sourceStart && value < currentRange.sourceStart + currentRange.length)
		{
			return value + (currentRange.destinationStart - currentRange.sourceStart);
		}
	}
	return value;
}