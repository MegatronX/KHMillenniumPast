#pragma once
#ifndef _MAPOBJECTINTERACTIONCOMPONENT_H_

#include <Components/Component.h>
#include <Mapping/MapObject.h>
#include <Mapping/MapCharacter.h>
namespace Game
{
	namespace Mapping
	{
		class MapObjectInteractionComponent : public Components::Component
		{
		public:
			MapObjectInteractionComponent(MapObject* owner) : Components::Component(owner), MapObj(owner)
			{

			}

			virtual bool IsInInteractionRange(int x, int y, int layer, MapCharacter& character)
			{
				return false;
			}



		private:
			MapObject* MapObj;
		};
	}
}
#endif