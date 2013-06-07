#pragma once
#ifndef _DAMAGESPLITCOMPONENT_H_
#define _DAMAGESPLITCOMPONENT_H_

#include <components/Component.h>
#include <actions/Action.h>
#include <cmath>
namespace Game
{
	namespace Battle
	{
		class DamageSplitComponent : public Components::Component
		{
		public:
			DamageSplitComponent(Entity* owner) : Components::Component(owner, owner != nullptr ? owner->GetName() + "DamageSplitComponent" : "NoOwnerDamageSplitComponent", "DamageSplitComponent")
			{

			}

			virtual float DetermineDamageSplit(Actions::Action& action, int TargetCount = 1, bool inBattle = true)
			{
				if (TargetCount < 2)
					return 1.f;
				else
					return 1.f / std::sqrt(float(TargetCount));
			}

			virtual RawClonePtr RawClone() const override
			{
				return new DamageSplitComponent(*this);
			}

			virtual ~DamageSplitComponent()
			{

			}
		private:
		};
	}
}

#endif