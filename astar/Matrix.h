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

	void Set(const Point& p, T value)
	{
		if (p.X() >= 0 && p.X() < width
			&& p.Y() >= 0 && p.Y() < height)
			data[p.X() + p.Y() * width] = value;
		else throw exception("Matrix.h: Point out of bounds!");
	}

	int Width() const
	{
		return width;
	}

	const T operator [](const Point& p) const
	{
		if (p.X() >= 0 && p.X() < width
			&& p.Y() >= 0 && p.Y() < height)
			return data[p.X() + p.Y() * width];
		else throw exception("Matrix.h: Point out of bounds!");
	}
private:
	T* data;
	int width;
	int height;
};