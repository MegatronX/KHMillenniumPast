#pragma once
#ifndef _ACTIONMODIFIERCOMPONENT_H_
#define _ACTIONMODIFIERCOMPONENT_H_
#include <components/Component.h>
#include <actions/Action.h>
namespace Game
{
	namespace Battle
	{
		class Mechanics;
	}
	namespace Actions
	{
		class ActionModifierComponent : public Components::Component
		{
		public:
			ActionModifierComponent(Entity* owner) : Component(owner, owner != nullptr ? owner->GetName() + "ActionModiferComponent" : "NoOwnerActionModifierComponent", "ActionModiferComponent")
			{

			}
			virtual bool ModifyAction(Actions::Action& action, Battle::Mechanics& mechanics)
			{
				return false;
			}

			virtual RawClonePtr RawClone() const override
			{
				return new ActionModifierComponent(*this);
			}
		};
	}
}

#endif