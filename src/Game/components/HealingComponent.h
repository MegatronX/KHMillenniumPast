#pragma once
#ifndef _HEALINGCOMPONENT_H_
#define _HEALINGCOMPONENT_H_
#include <components/Component.h>
#include <components/StatAffectorComponent.h>
#include <character/Stats.h>
namespace Game
{
	namespace Components
	{
		class HealingComponent : public Component
		{
		public:
			HealingComponent(Entity* owner) : Component(owner, "", "HealingComponent"), HPComponent(Character::Stat::HP), MPComponent(Character::Stat::MP), SPComponent(Character::Stat::SP)//, HPComponent(), MPComponent(), SP
			{
				
			}
			HealingComponent(Character::Stat stat, float statHeal, StatAffectorType type) 
				: Component("HPHealing", "HealingComponent"), HPComponent(Character::Stat::HP), MPComponent(Character::Stat::MP), SPComponent(Character::Stat::SP)
			{
				switch (stat)
				{
				case Character::Stat::HP:
					HPComponent.SetValid(true);
					HPComponent.SetValid(statHeal);
					break;
				case Character::Stat::MP:
					MPComponent.SetValid(true);
					MPComponent.SetValid(statHeal);
					break;
				case Character::Stat::SP:
					SPComponent.SetValid(true);
					SPComponent.SetValid(statHeal);
					break;
				}
			}
			HealingComponent(float HPHeal, StatAffectorType HPType, bool HPValid, 
							 float MPHeal, StatAffectorType MPType, bool MPValid, 
							 float SPHeal, StatAffectorType SPType, bool SPValid)
				: Component("StatHealing", "HealingComponent"), HPComponent(Character::Stat::HP, HPHeal, HPValid, HPType), MPComponent(Character::Stat::MP, MPHeal, MPValid, MPType), 
				SPComponent(Character::Stat::SP, HPHeal, SPValid, SPType)
			{

			}
			/*HealingComponent(float HPHeal, float MPHeal, float SPHeal, bool HPValid = true, bool MPHeal = true, bool SPHeal = false, const std::string& name = "HealComponent")
				//: HPComponent(Character::Stat::HP, HPHeal)
			{

			}*/
			bool IsHPComponentValid() const
			{
				return HPComponent.IsValid();
			}
			const StatAffectorComponent& GetHPComponent() const
			{
				return HPComponent;
			}
			bool IsMPComponentValid() const
			{
				return MPComponent.IsValid();
			}
			const StatAffectorComponent& GetMPComponent() const
			{
				return MPComponent;
			}
			bool IsSPComponentValid() const
			{
				return SPComponent.IsValid();
			}
			const StatAffectorComponent& GetSPComponent() const
			{
				return SPComponent;
			}
			virtual ClonePtr Clone() const override
			{
				return ClonePtr(new HealingComponent(*this));
			}
		protected:
		private:
			StatAffectorComponent HPComponent;
			StatAffectorComponent MPComponent;
			StatAffectorComponent SPComponent;
		};
	}
}

#endif