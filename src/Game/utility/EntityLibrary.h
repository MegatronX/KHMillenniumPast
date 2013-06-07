#pragma once
#ifndef _ENTITYLIBRARY_H_
#define _ENTITYLIBRARY_H_
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <string>
namespace Game
{
	template <class T>
	class EntityLibrary
	{
	public:
		typedef boost::shared_ptr<T> EntryPtr;
		void AddEntry(EntryPtr entry);
	private:
		boost::unordered<std::string, EntryPtr> NameToEntity;
	};
}

#endif