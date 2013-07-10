#pragma once

class Point
{
public:
	Point();
	Point(int x, int y);
	int X() const;
	int Y() const;
	bool operator ==(const Point& other) const;
	bool operator !=(const Point& other) const;
private:
	int x;
	int y;
};