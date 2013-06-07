#pragma once
#ifndef _CHARACTERSTATCOMPONENT_H_
#define _CHARACTERSTATCOMPONENT_H_
#include <character/Stats.h>
#include <components/Component.h>
#include <boost/signal.hpp>
#include <boost/signals2.hpp>
#include <boost/function.hpp>

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
		
		class StatComponent; 

		typedef boost::signals2::signal<void (const std::string& compName, StatComponent*, Character::Stat stat, int oldVal, int newVal)> StatChangedSignal;
		
		class StatComponent : public Components::Component, public boost::signals::trackable
		{
		public:
			StatComponent(Entity* owner);
			StatComponent(Entity* owner, int initialValue);
			StatComponent(Entity* owner, int initialValues[Character::StatCount]);
			StatComponent(Entity* owner, const std::string& name);
			StatComponent(Entity* owner, int initialValue, const std::string& name);
			StatComponent(Entity* owner, const int InitialStats[Character::StatCount], const std::string& name) ;

			//NOTE that the copy constructor does NOT copy the signals
			StatComponent(const StatComponent& base);

			int GetStat(const Character::Stat stat) const;
			int GetBaseStat(const Character::Stat stat) const;
			int GetStatAdder(const Character::Stat stat) const;
			float GetStatMultiplier(const Character::Stat stat) const;

			bool SetStatAdder(const Character::Stat stat, const int value, const bool Sync = true);
			bool SetStatMultiplier(const Character::Stat stat, const float value, const bool Sync = true);

			bool IncrementStatAdder(const Character::Stat stat, const int value, const bool Sync = true);
			bool IncrementStatMultiplier(const Character::Stat stat, const float value, const bool Sync = true);

			boost::signals2::connection AddStatChangedEvent(const StatChangedSignal::slot_type& event);
			void DispatchStatChangedEvents(Character::Stat stat, int prevVal, int newVal);
			virtual ~StatComponent();
			StatComponent& operator=(const StatComponent& reference);
			virtual ClonePtr Clone() const override;

			virtual void ResetStat(const Character::Stat stat);
			void ResetAllStats();
		protected:
			
			bool SetStat(const Character::Stat stat, const int value, const bool Sync = true);
			bool SetBaseStat(const Character::Stat stat, const int value, const bool Sync = true);
			StatChangedSignal StatChangedEvent;
			int& operator[](const Character::Stat stat);
			int& operator[](const int stat);

			friend class Character::LevelingComponent;
		private:
			int Stats[Character::StatCount] ;
			float Multipliers[Character::StatCount];
			int StatAdders[Character::StatCount];
			int EffectiveStats[Character::StatCount];
			friend class Character::BaseCharacter;
			friend class Character::StatsManager;
		};
	}
}
#endif