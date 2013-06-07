#pragma once
#ifndef _CHARACTERSTATCOMPONENT_H_
#define _CHARACTERSTATCOMPONENT_H_
#include <character/Stats.h>
#include <components/Component.h>
#include <array>

namespace Game
{
	class Entity;
	namespace Character
	{
		class BaseCharacter;
		class StatsManager;
		class LevelingComponent;
	}
	namespace Components
	{
		
		//class StatComponent; 

		//typedef boost::signals2::signal<void (const std::string& compName, StatComponent*, Character::Stat stat, int oldVal, int newVal)> StatChangedSignal;
		
		template <class T = int>
		class StatComponent : public Components::Component
		{
		public:
			StatComponent() : Component(nullptr, "EmptyStatComponent", "StatsComponent")
			{
				for (int i = 0; i < Character::StatCount; ++i)
				{
					Stats[i] = 0;
				}
			}
			StatComponent(Entity* owner) :  Component(owner, owner != nullptr ? "EmptyStatComponent" + owner->GetName() : "EmptyStatComponent", "StatsComponent")
			{
				for (int i = 0; i < Character::StatCount; ++i)
				{
					Stats[i] = 0;
				}
			}
			StatComponent(Entity* owner, const T initialValue) :  Component(owner, owner != nullptr ? "EmptyStatComponent" + owner->GetName() : "EmptyStatComponent", "StatsComponent")
			{
				for (int i = 0; i < Character::StatCount; ++i)
				{
					Stats[i] = initialValue;
				}
			}
			StatComponent(Entity* owner, const T InitialStats[Character::StatCount]) : Component(owner, "NoNameStatsComponent", "StatsComponent")
			{
				for (auto i = 0; i < Stats.size(); ++i)
				{
					Stats[i] = InitialStats[i];
				}
			}
			StatComponent(Entity* owner, const std::string& name) : Component(owner, name, "StatsComponent")
			{
				for (int i = 0; i < Character::StatCount; ++i)
				{
					Stats[i] = T();
				}
			}
			StatComponent(Entity* owner, const T initialValue, const std::string& name) : Component(owner, name, "StatsComponent")
			{
				for (int i = 0; i < Character::StatCount; ++i)
				{
					Stats[i] = initialValue;
				}
			}
			StatComponent(Entity* owner, const T InitialStats[Character::StatCount], const std::string& name) : Component(owner, name, "StatsComponent"), Stats(InitialStats)
			{

			}

			/*StatComponent(const StatComponent<T>& base)
			{

			}*/

			T GetStat(const Character::Stat stat) const
			{
				return Stats[stat];
			}

			void IncrementStat(const Character::Stat stat, const T inc)
			{
				Stats[stat] += inc;
			}

			const std::array<T, Character::StatCount>& GetStats() const
			{
				return Stats;
			}

			virtual ~StatComponent()
			{

			}
			//StatComponent& operator=(const StatComponent<T>& reference);
			virtual ClonePtr Clone() const override
			{
				return ClonePtr(new StatComponent(*this));
			}

		protected:
			void SetStat(const Character::Stat stat, const T val)
			{
				Stats[stat] = val;
			}
			T& operator[](const Character::Stat stat)
			{
				return Stats[stat];
			}
			T& operator[](const int stat)
			{
				return Stats[stat];
			}

			friend class Character::LevelingComponent;
		private:
			std::array<T, Character::StatCount> Stats;

			friend class Character::BaseCharacter;
			friend class Character::StatsManager;
		};
	}
}
#endif