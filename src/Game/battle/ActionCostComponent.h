#pragma once
#ifndef _ACTIONCOSTCOMPONENT_H_
#define _ACTIONCOSTCOMPONENT_H_

#include <actions/Action.h>

namespace Game
{
	namespace Actions
	{
		class ActionUsabilityComponent : public Components::Component
		{
		public:
			ActionUsabilityComponent(Entity* owner) : Components(owner, owner != nullptr ? "ActionCostComponent" + owner->GetName() : "ActionCostComponentNoOwner", "ActionCostComponent")
			{

			}

			virtual bool SatisfiesUsability(Character::BaseCharacter& character) = 0;

			virtual void EnforceUsability(Character::BaseCharacter& character) = 0;

			virtual void EnforceUsability(Character::BaseCaracter& character, Battle::Mechanics& mech)
			{
				EnforceUsability(character);
			}

			virtual ~ActionUsabilityComponent()
			{

			}
		}

		class BasicActionUsabilityComponent : public ActionUsabilityComponent
		{
			BasicActionCostComponent(Action* owner) : ActionCostComponent(owner)
			{
			}

			virtual ~BasicActionUsabilityComponent()
			{

			}
		}
	}
}

#endif