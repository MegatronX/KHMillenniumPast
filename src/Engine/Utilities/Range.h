#pragma once
#ifndef _RANGE_H_
#define _RANGE_H_
#include <map>
#include <boost/unordered_map.hpp>
template <class T = int>
class Range
{
public:
	explicit Range(T item) : Low(item), High(item)
	{

	}
	Range(T low, T high) : Low(low), High(high)
	{

	}

	bool operator<(const Range<T>& rhs) const
	{
		if (Low < rhs.Low)
		{
			assert(High < rhs.Low);
			return true;
		}
		return false;
	}

	T GetLow() 
	{
		return Low;
	}

	T GetHigh()
	{
		return High;
	}

	template <class U>
	static U Find(T item, std::map<Range<T>, U>& mapping)
	{
		auto it = mapping.lower_bound(Range<T>(item));
		return (it != mapping.end() && it->first.GetLow() <= item ? return it->second : 0);
	}

	/*template <class U = int>
	static U Find(T item, boost::unordered_map<Range<T>, U>& mapping)
	{
		auto it = mapping.lower_bound(Range<T>(item));
		return (it != mapping.end() && it->first.GetLow() <= item ? return it->second : 0);
	}*/
private:
	T Low;
	T High;
};

#endif