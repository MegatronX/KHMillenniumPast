#pragma once
#ifndef _MAPNPC_H_
#define _MAPNPC_H_

#include <Mapping/MapEvent.h>
namespace Game
{
	namespace Mapping
	{
		class MapNPCComponent : public MapEventComponent
		{
		public:
		private:
		};

		class UpdatingMapNPC : public MapNPCComponent
		{
		public:
		private:
		};

		class PathWalkingNPC : UpdatingMapNPC
		{
		public:
		private:
			std::vector<sf::Vector2f> NPCPath;
		};

		class RandomWalkingNPC : UpdatingMapNPC
		{
		public:
		private:
			bool ObeyCollisionLayers;

		};
	}
}

#endif