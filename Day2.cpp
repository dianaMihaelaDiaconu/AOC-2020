#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>

std::ifstream f("input.txt");

std::vector<std::string> readEntries()
{
	std::string entry;
	std::vector<std::string> entries;
	while (std::getline(f, entry))
	{
		entries.push_back(entry);
	}

	return entries;
}

void Part1(std::vector<std::string> entries)
{
	int count = 0;
	for (auto entry : entries)
	{
		std::smatch matches;
		std::regex reg(R"((\d+)-(\d+)\s(\w):\s(\w+))");
		if (std::regex_search(entry, matches, reg))
		{
			char letter = static_cast<std::string>(matches[3])[0];
			int min = stoi(matches[1]);
			int max = stoi(matches[2]);
			std::string pass = matches[4];

			int letterCount = std::count(pass.begin(), pass.end(), letter);
			if (letterCount >= min && letterCount <= max)
			{
				count++;
			}
		}
	}
	std::cout << count;
}

void Part2(std::vector<std::string> entries)
{
	int count = 0;
	for (auto entry : entries)
	{
		std::smatch matches;
		std::regex reg(R"((\d+)-(\d+)\s(\w):\s(\w+))");
		if (std::regex_search(entry, matches, reg))
		{
			char letter = static_cast<std::string>(matches[3])[0];
			int index1 = stoi(matches[1]) - 1;
			int index2 = stoi(matches[2]) - 1;
			std::string pass = matches[4];

			if ((pass.at(index1) == letter && pass.at(index2) != letter) || (pass.at(index1) != letter && pass.at(index2) == letter))
			{
				count++;
			}
		}
	}
	std::cout << count;
}

int main()
{
	std::vector<std::string> entries = readEntries();
	//Part1(entries);
	Part2(entries);
	
	

	return 0;
}