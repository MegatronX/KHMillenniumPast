#pragma once
#ifndef _APPLYEFFECTCOMPONENT_H_
#define _APPLYEFFECTCOMPONENT_H_
#include <Entity.h>
#include <components/Component.h>
#include <statuseffects/StatusEffect.h>
namespace Game
{
	namespace Character
	{
		class BaseCharacter;
	}
	namespace Components
	{
		class ApplyEffectComponent : public Component
		{
		public:
			ApplyEffectComponent(Entity* owner) : Component(owner, "ApplyEffectComponent" + owner->GetName(), "ApplyEffectComponent")
			{

			}
			virtual void Apply(Character::BaseCharacter* character)
			{
				auto se = dynamic_cast<StatusEffects::StatusEffect*>(this->GetOwner());
				if (se != nullptr)
				{
					se->DispatchActivatedSignal("EffectApplied");
				}
			}

			virtual void UnApply(Character::BaseCharacter* character)
			{
				auto se = dynamic_cast<StatusEffects::StatusEffect*>(this->GetOwner());
				if (se != nullptr)
				{
					se->DispatchDeactivatedSignal("EffectUnapplied");
				}
			}
		protected:
		private:
		};
	}
}

#endif