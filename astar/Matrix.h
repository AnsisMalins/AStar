#pragma once
#include "Point.h"

template <typename T>
class Matrix
{
public:
	Matrix()
		: width(0), height(0)
	{
		data = NULL;
	}

	~Matrix()
	{
		if (data != NULL) delete [] data;
	}

	Matrix(int width, int height)
		: data(new T[width * height]), width(width), height(height)
	{
		memset(data, 0, width * height * sizeof(T));
	}

	int Height() const
	{
		return height;
	}

	int Width() const
	{
		return width;
	}

	T& operator [](const Point& p)
	{
		return data[p.X() + p.Y() * width];
	}

	const T& operator [](const Point& p) const
	{
		return data[p.X() + p.Y() * width];
	}
private:
	T* data;
	int width;
	int height;
};