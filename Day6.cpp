#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <set>

std::ifstream f("input.txt");
using groupForm = std::vector<std::string>;

std::vector< groupForm > readData()
{
	std::vector< groupForm > data(1);

	std::string s;
	int count = 0;
	while (getline(f, s))
	{
		if (s.empty())
		{
			count++;
			data.push_back(groupForm());
		}
		else
		{
			data[count].push_back(s);
		}
	}

	return data;
}

size_t GetUniqueCount(groupForm gf)
{
	std::set<char> answers;
	for (auto form : gf)
	{
		answers.insert(form.begin(), form.end());
	}
	return answers.size();
}

void Part1(std::vector< groupForm > forms)
{
	size_t sum = 0;
	for (auto group : forms)
	{
		sum += GetUniqueCount(group);
	}

	std::cout << sum;
}

size_t GetCommonCount(groupForm gf)
{
	std::set<char> answers;
	answers.insert(gf[0].begin(), gf[0].end());
	for (size_t i = 1; i < gf.size(); i++)
	{
		std::set<char> current;
		current.insert(gf[i].begin(), gf[i].end());
		std::set<char> tmp;
		auto it = std::set_intersection(answers.begin(), answers.end(), current.begin(), current.end(), std::inserter(tmp, tmp.begin()));
		answers = tmp;
	}
	return answers.size();
}

void Part2(std::vector< groupForm > forms)
{
	size_t sum = 0;
	for (auto group : forms)
	{
		sum += GetCommonCount(group);
	}

	std::cout << sum;
}

int main()
{
	std::vector< groupForm > forms = readData();

	Part2(forms);
	return 0;
}