#pragma once
#ifndef _TARGETTINGCOMPONENT_H_
#define _TARGETTINGCOMPONENT_H_

#include <components/Component.h>
#include <boost/unordered_set.hpp>
namespace Game
{
	namespace Actions
	{
		enum TargetOption
		{
			SingleTargetAny = 1,
			SingleTargetPlayerParty = 2,
			SingleTargetAllyParty = 4,
			SingleTargetEnemyParty = 8,
			AnyParty = 16,
			EnemyParty = 32,
			PlayerParty = 64,
			AllyParty = 128,
			AllEnemyParties = 256,
			AllAllyParties = 512,
			All = 1024
		};
		const std::string TargettingComponentIndex = "TargettingComponentIndex";
		class TargettingComponent
		{
		public:
			TargettingComponent(const boost::unordered_set<TargetOption> optionSet, bool targettingLocked = false) : TargetSet(optionSet), TargettingLocked(targettingLocked)
			{

			}
			void AddTargetOption(TargetOption opt)
			{
				if (!TargettingLocked)
					TargetSet.insert(opt);
			}
			bool HasTargetOption(TargetOption opt)
			{
				return TargetSet.find(opt) != TargetSet.end();
			}

			void SetTargettingLock(bool locked)
			{
				TargettingLocked = locked;
			}

			const boost::unordered_set<TargetOption>& GetAvailableTargetting() const
			{
				return TargetSet;
			}
		protected:
			void ClearAvailableTargetting()
			{
				TargetSet.clear();
			}

			void SetTargetSet(const boost::unordered_set<TargetOption>& topt)
			{
				TargetSet = topt;
			}
		private:
			unsigned int TargetOptionSet;
			bool TargettingLocked;
			boost::unordered_set<TargetOption> TargetSet;
		};
	}
}

#endif