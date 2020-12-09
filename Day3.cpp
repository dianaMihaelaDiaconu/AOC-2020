#include <fstream>
#include <iostream>
#include <vector>
#include <string>
std::ifstream f("input.txt");

std::vector<short> grid;
int rows = 0, columns = 0;

struct Point
{
	int x;
	int y;
	Point(int x, int y)
	: x(x), y(y)
	{
	}

	Point& operator += (const Point p)
	{
		x += p.x;
		y += p.y;
		return *this;
	}
};

void readGrid()
{
	char c;
	std::string line;
	while (std::getline(f, line))
	{
		rows++;
		for( auto i = line.begin(); i < line.end(); i++)
			grid.push_back(*i == '.' ? 0 : 1);
	}
	columns = grid.size() / rows;
}

short getElemAt(Point p)
{
	return grid[p.x * columns + p.y];
}

bool isTree(Point p)
{
	return getElemAt(p) == 1;
}

int CheckSlope(std::pair<int, int> slope)
{
	Point pos = Point(0, 0);
	int treeCount = 0;
	while (pos.x < rows)
	{
		if (isTree(pos))
		{
			treeCount++;
		}
		pos += Point(slope.second, slope.first);
		pos.y = pos.y % columns;
	}

	return treeCount;
}

void Part1()
{
	std::cout << CheckSlope({ 3, 1 });
}

void Part2()
{
	std::vector < std::pair<int, int>> slopes = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };
	long long total = 1;
	for (auto s : slopes)
	{
		total *= CheckSlope(s);
	}

	std::cout << total;
}

int main()
{
	readGrid();
	Part2();
}