#pragma once
#ifndef _CLONEABLE_H_
#define _CLONEABLE_H_
#include <boost/shared_ptr.hpp>

/*template<class T>
class Cloneable_
{
public:
	typedef boost::shared_ptr<T> ClonePtr;
	typedef T* RawClonePtr;
	virtual ClonePtr Clone() const = 0;
	virtual RawClonePtr RawClone()
	{
		ClonePtr clone = Clone();
		clone.
	}
};*/

template<class T>
class Cloneable
{
public:
	typedef boost::shared_ptr<T> ClonePtr;
	typedef T* RawClonePtr;
	virtual ClonePtr Clone() const
	{
		return ClonePtr(RawClone());
	}
	virtual RawClonePtr RawClone() const
	{
		return nullptr;
	}
};


template<class T>
class Cloneable_
{
public:
	typedef boost::shared_ptr<T> ClonePtr;
	typedef T* RawClonePtr;
	virtual ClonePtr Clone()
	{
		return ClonePtr(RawClonePtr());
	}
	virtual RawClonePtr RawClone() = 0;
};
#endif