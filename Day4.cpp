#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <map>

std::ifstream f("input.txt");

std::vector<std::map<std::string, std::string>> ReadData()
{
	std::vector<std::map<std::string, std::string>> data(1);
	std::string s;

	int count = 0;
	while (getline(f, s))
	{
		if (s.empty())
		{
			count++;
			data.push_back(std::map<std::string, std::string>());
		}

		size_t pos;
		while ((pos = s.find(' ')) != std::string::npos)
		{
			std::string entry = s.substr(0, pos);
			s.erase(0, pos + 1);

			std::regex reg(R"((\w+):(.+))");
			std::smatch matches;
			if (std::regex_search(entry, matches, reg))
			{
				data[count][matches[1]] = matches[2];
			}

		}
		std::regex reg(R"((\w+):(.+))");
		std::smatch matches;
		if (std::regex_search(s, matches, reg))
		{
			data[count][matches[1]] = matches[2];
		}
	}
	return data;
}

bool IsValid(std::map<std::string, std::string> p)
{
	std::vector<std::string> requiredFields = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
	for (auto field : requiredFields)
	{
		if (p.count(field) != 1)
		{
			return 0;
		}
	}

	return true;
}

bool IsValid2(std::map<std::string, std::string> p)
{
	std::vector<std::string> requiredFields = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
	
	auto validation = [](std::string key, std::string value)
	{
		if (key == "byr")
		{
			int year = std::stoi(value);
			return year >= 1920 && year <= 2002;
		}
		else if (key == "iyr")
		{
			int year = std::stoi(value);
			return year >= 2010 && year <= 2020;
		}
		else if (key == "eyr")
		{
			int year = std::stoi(value);
			return year >= 2020 && year <= 2030;
		}
		else if (key == "hgt")
		{
			std::regex reg(R"((\d+)(cm|in))");
			std::smatch matches;
			if (std::regex_search(value, matches, reg))
			{
				if (matches[2] == "cm")
				{
					auto num = stoi(matches[1]);
					return num >= 150 && num <= 193;
				}
				else
				{
					auto num = stoi(matches[1]);
					return num >= 59 && num <= 76;
				}
			}
			return false;
		}
		else if (key == "hcl")
		{
			return std::regex_match(value, std::regex(R"(^#([0-9a-f]){6}$)"));
		}
		else if (key == "ecl")
		{
			return value == "amb" || value == "blu" || value == "brn" || value == "gry" || value == "grn" || value == "hzl" || value == "oth";
		}
		else if (key == "pid")
		{
			return std::regex_match(value, std::regex(R"(^([0-9]){9}$)"));
		}
	};

	for (auto field : requiredFields)
	{
		if (p.count(field) != 1 || !validation(field, p[field]))
		{
			return 0;
		}
	}

	return true;
}

void CheckPassports(std::vector<std::map<std::string, std::string>> passports)
{
	
	int count = 0;
	for (auto p : passports)
	{
		if (IsValid2(p))
		{
			count++;
		}
	}
	
	std::cout << count;
}

int main()
{
	auto passports = ReadData();
	CheckPassports(passports);

	return 0;
}