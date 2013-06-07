#pragma once

#include <abilities/Ability.h>
#include <boost/unordered_set.hpp>
namespace Game
{
	namespace Abilities
	{
		class AbilityLibrary
		{
		public:
			const Ability* GetAbility(const std::string& name)
			{
				auto abil = NameToAbilityMap.find(name);
				if (abil != NameToAbilityMap.end())
				{
					return abil->second.get();
				}
				return nullptr;
			}
		protected:
		private:
			boost::unordered_map<std::string, abil_ptr> NameToAbilityMap;
		};
	}
}