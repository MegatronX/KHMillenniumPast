#pragma once
#ifndef _USECOMPONENT_H_
#define _USECOMPONENT_H_
#include <components/Component.h>
namespace Game
{
	namespace Battle
	{
		class UseComponent : public Components::Component
		{
		public:
			UseComponent(Entity* owner) : Components::Component(owner, owner!= nullptr ? "UseComponent" + owner->GetName() : "UseComponentNoOwner", "UseComponent")
			{

			}

			void Use(Actions::Action& action, Mechanics& mechanics, bool InBattle = true)
			{

			}

			virtual ~UseComponent()
			{

			}
		private:
		};
	}
}

#endif