#pragma once
#include "collection.h"
#include "Point.h"

class Map
{
public:
	Map(const std::wstring& path);
	int Distance(const Point& a, const Point& b) const;
	int Height() const;
	bool IsFree(int x, int y) const;
	bool IsFree(const Point& p) const;
	collection<Point> Neighbors(int x, int y) const;
	collection<Point> Neighbors(const Point& p) const;
	void Show() const;
	void Show(std::ostream& out) const;
	void Show(const collection<Point>& markers) const;
	void Show(const collection<Point>& markers, std::ostream& out) const;
	int Width() const;
private:
	collection<bool> free;
	int width;
	int height;
};