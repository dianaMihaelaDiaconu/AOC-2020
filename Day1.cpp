#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::ifstream f("input.txt");

int main()
{
	std::vector<int> entries;
	std::string entry;
	int total = 0;
	while (std::getline(f, entry))
	{
		int nr = std::atoi(entry.c_str());
		entries.push_back(nr);
	}
	for (int i = 0; i < entries.size() - 2; i++)
	{
		for (int j = i +1; j < entries.size() - 1; j++)
		{
			for (int k = j + 1; k < entries.size(); k++)
			{
				if (entries[i] + entries[j] + entries[k] == 2020)
				{
					std::cout << entries[i] * entries[j] * entries[k];
					break;
				}
			}
		}
		
	}


	return 0;
}