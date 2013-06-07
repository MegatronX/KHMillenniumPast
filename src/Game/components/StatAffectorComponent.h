#pragma once
#ifndef _STATAFFECTOR_H_
#define _STATAFFECTOR_H_
#include <components/Component.h>
#include <character/Stats.h>

namespace Game
{
	namespace Components
	{
		enum StatAffectorType
		{
			Absolute,
			AbsolutePercent,
			RelativePercent
		};
		class StatAffectorComponent : public Component
		{
		public:
			StatAffectorComponent() : Component("", "StatAffector", false)
			{

			}
			StatAffectorComponent(Character::Stat stat) : Component("", "StatAffector", false), stat(stat)
			{

			}
			StatAffectorComponent(const Character::Stat targstat, const float targvalue, bool valid = true, const StatAffectorType targtype = Absolute, const std::string& name = "StatAffectorDefault")
				: Component(name, "StatAffector", valid), stat(targstat), value(targvalue), type(targtype)
			{

			}
			Character::Stat GetStat() const
			{
				return stat;
			}
			float GetValue() const
			{
				return value;
			}
			StatAffectorType GetType() const
			{
				return type;
			}
			virtual ClonePtr Clone() const
			{
				return ClonePtr(new StatAffectorComponent(*this));
			}
		protected:
			void SetType(const StatAffectorType Type)
			{
				type = Type;
			}
			void SetValue(const float val)
			{
				value = val;
			}
			void SetStat(Character::Stat targetstat)
			{
				stat = targetstat;
			}
		private:
			Character::Stat stat;
			StatAffectorType type;
			float value;
		};
	}
}

#endif