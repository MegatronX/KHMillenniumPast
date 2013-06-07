#pragma once

#include <components/Component.h>
#include <vector>
#include <SFML/Graphics.hpp>
namespace Game
{
	namespace Mapping
	{
		class NPCInteractionComponent
		{
		public:
		
		protected:
			bool UseInteractionRange;
			//Interaction Range Variable
			int LeftTolerance;
			int RightTolerance;
			int TopTolerance;
			int BottomTolerance;

			bool UseInteractionPoints;
			std::vector<sf::Vector2f> InteractionPoints;
		};
	}
}