#pragma once
#ifndef _OBJECTACTIVATIONCOMPONENT_H_
#define _OBJECTACTIVATIONCOMPONENT_H_
#include <components/Component.h>
namespace Game
{
	namespace Mapping
	{
		class ObjectActivationComponent : public Components::Component
		{
			ObjectActivationComponent(Entity* owner)
			{

			}

			bool InActivationRange(int x, int y, int layer)
			{

			}
		}
	}
}

#endif