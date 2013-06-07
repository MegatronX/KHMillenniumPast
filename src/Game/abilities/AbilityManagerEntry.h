#pragma once
#ifndef _ABILITYMANAGERENTRY_H_
#define _ABILITYMANAGERENTRY_H_
#include <abilities/Ability.h>
#include <abilities/AbilityLibrary.h>
#include <components/Component.h>
namespace Game
{
	namespace Abilities
	{
		class AbilityManagerEntry
		{
		public:
			AbilityManagerEntry(abil_ptr abil);


		protected:
		private:
			int AvailableInstanceCount;
			int ActiveInstanceCount;
			int LearaningInstanceCount;
			abil_ptr EnteredAbility;
		};
	}
}

#endif