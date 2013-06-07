#pragma once
#include <character/BaseCharacter.h>
#include <Components/Component.h>
#include <boost/signals2.hpp>
namespace Game
{
	namespace Battle
	{
		class BattleCharacter;
		typedef boost::signals2::signal<void (BattleCharacter* bchar, bool IsSim)> TimerOverflowSignal;
		class BattleCharacter : public Components::Component
		{
		public:
			BattleCharacter(Character::BaseCharacter* owner) : Component(owner, owner != nullptr ? owner->GetName() + "BattleCharacterComponent" : "NoOwnerBattleCharacterComponent", "BattleCharacterComponent"),
				TimerValue(0), SimeTimerValue(0), OverflowRatio(0.f), CanTakeTurn(true), InSimulation(false), sm(owner != nullptr ? owner->GetComponentAs<Character::StatsManager*>("StatManagerComponent") : nullptr)
			{
				
			}
			
			void TickTimer(int ticks = 1)
			{
#ifdef DEBUG
				if (sm != nullptr)
				{
#endif
				if (InSimulation)
				{
					SimTimerValue += sm->GetBattleStat(Character::Stat::Speed);
				}
				else
				{
					LiveTimerValue += sm->GetBattleStat(Character::Stat::Speed);
				}
#ifdef DEBUG
				}
				else
				{
					std::cerr << "Stat Manager for battle character was null \n";
				}
#endif
			}
			
			Character::BaseCharacter* GetWrapperCharacter() const
			{
				return WrappedCharacter;
			}
		private:
			Character::StatsManager* sm;
			int LiveTimerValue;
			int SimTimerValue;
			float OverflowRation;
			bool CanTakeTurn;
			bool InSimulation;
			Character::BaseCharacter* WrappedCharacter;
		};
	}
}