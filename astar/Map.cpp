#include "stdafx.h"
#include "Map.h"

using namespace std;

Map::Map(const wstring& path)
	: width(126), height(126)
{
	ifstream mapfile(path);
	if (mapfile.fail()) throw exception("Couldn't open the map file.");
	free.reserve(width * height); // TODO: Input validation?
	while (!mapfile.eof())
	{
		switch (mapfile.get())
		{
		case '.':
			free.push_back(true);
			break;
		case '*':
			free.push_back(false);
			break;
		default:
			break;
		}
	}
}

int Map::Distance(const Point& a, const Point& b) const
{
	return max(abs(a.X() - b.X()), abs(a.Y() - b.Y()));
}

int Map::Height() const
{
	return height;
}

bool Map::IsFree(int x, int y) const
{
	return x >= 0 && x < width
		&& y >= 0 && y < height
		&& free[x + y * width];
}

bool Map::IsFree(const Point& p) const
{
	return IsFree(p.X(), p.Y());
}

collection<Point> Map::Neighbors(int x, int y) const
{
	collection<Point> result;
	result.reserve(8);
	if (!IsFree(x, y)) return result;
	if (IsFree(x, y - 1)) result.push_back(Point(x, y - 1));
	if (IsFree(x + 1, y - 1)) result.push_back(Point(x + 1, y - 1));
	if (IsFree(x + 1, y)) result.push_back(Point(x + 1, y));
	if (IsFree(x + 1, y + 1)) result.push_back(Point(x + 1, y + 1));
	if (IsFree(x, y + 1)) result.push_back(Point(x, y + 1));
	if (IsFree(x - 1, y + 1)) result.push_back(Point(x - 1, y + 1));
	if (IsFree(x - 1, y)) result.push_back(Point(x - 1, y));
	if (IsFree(x - 1, y - 1)) result.push_back(Point(x - 1, y - 1));
	return result;
}

collection<Point> Map::Neighbors(const Point& p) const
{
	return Neighbors(p.X(), p.Y());
}

void Map::Show() const
{
	Show(collection<Point>(), cout);
}

void Map::Show(ostream& out) const
{
	Show(collection<Point>(), out);
}

void Map::Show(const collection<Point>& markers) const
{
	Show(markers, cout);
}

void Map::Show(const collection<Point>& markers, ostream& out) const
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (markers.contains(Point(x, y))) out << '+';
			else if (IsFree(x, y)) out << '.';
			else out << '*';
		}
		out << endl;
	}
}

int Map::Width() const
{
	return width;
}