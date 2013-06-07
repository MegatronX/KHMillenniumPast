#pragma once
#ifndef _PREUSECOMPONENT_H_
#define _PREUSECOMPONENT_H_
#include <components/Component.h>
#include <Entity.h>
#include <actions/Action.h>
#include <battle/mechanics/Mechanics.h>
namespace Game
{
	namespace Battle
	{
		class PreUseComponent : public Components::Component
		{
		public:
			PreUseComponent(Entity* owner) : Components::Component(owner, owner!= nullptr ? "PreUseComponent" + owner->GetName() : "PreUseComponentNoOwner", "PreUseComponent")
			{

			}

			void PreUse(Actions::Action& action, Mechanics& mechanics, bool InBattle = true)
			{

			}
		private:
		};
	}
}

#endif