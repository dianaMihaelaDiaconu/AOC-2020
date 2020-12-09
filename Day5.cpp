#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> GetSeats()
{
	std::ifstream f("input.txt");
	char c;
	
	auto compute = [](char c, int&min, int& max)
	{
		if (c == 'l')
		{
			max = (min + max - 1) / 2;
		}
		else
		{
			min = (min + max) / 2 + 1;
		}
	};

	std::string s;

	std::vector<int> seats;
	while (f >> s)
	{
		int minRow = 0, maxRow = 127, minCol = 0, maxCol = 7;
		for (auto c : s)
		{
			if (c == 'F' || c == 'B')
			{
				compute(c == 'F' ? 'l' : 'h', minRow, maxRow);
			}
			else
			{
				compute(c == 'L' ? 'l' : 'h', minCol, maxCol);
			}
		}
		seats.push_back(minRow * 8 + minCol);
	}

	return seats;
}

int main()
{
	std::vector<int> seats = GetSeats();

	//std::cout << *std::max_element(seats.begin(), seats.end());
	
	//Part2
	std::sort(seats.begin(), seats.end());

	for (int i = 1; i < seats.size() - 1; i++)
	{
		if (seats[i] == seats[i - 1] + 2)
		{
			std::cout << seats[i] - 1;
			break;
		}
	}
}