#pragma once

template<typename T>
class collection : public std::vector<T>
{
public:
	bool contains(const T& item) const
	{
		for (const_iterator i = begin(); i != end(); ++i)
			if (*i == item) return true;
		return false;
	}

	bool remove(const T& item)
	{
		for (const_iterator i = begin(); i != end(); ++i)
		{
			if (*i == item)
			{
				erase(i);
				return true;
			}
		}
		return false;
	}
};