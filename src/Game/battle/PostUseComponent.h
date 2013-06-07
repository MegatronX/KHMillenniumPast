#pragma once
#ifndef _POSTUSECOMPONENT_H_
#define _POSTUSECOMPONENT_H_
#include <components/Component.h>
namespace Game
{
	namespace Battle
	{
		class PostUseComponent : public Components::Component
		{
		public:
			PostUseComponent(Entity* owner) : Components::Component(owner, owner!= nullptr ? "PostUseComponent" + owner->GetName() : "PostUseComponentNoOwner", "PostUseComponent")
			{

			}

			void PostUse(Actions::Action& action, Mechanics& mechanics, bool InBattle = true)
			{

			}
		private:
		};
	}
}

#endif