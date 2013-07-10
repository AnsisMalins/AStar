#include "stdafx.h"
#include "Point.h"

Point::Point()
	: x(0), y(0)
{
}

Point::Point(int x, int y)
	: x(x), y (y)
{
}

int Point::X() const
{
	return x;
}

int Point::Y() const
{
	return y;
}

bool Point::operator ==(const Point& other) const
{
	return x == other.x && y == other.y;
}

bool Point::operator !=(const Point& other) const
{
	return x != other.x || y != other.y;
}