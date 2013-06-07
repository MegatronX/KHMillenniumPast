#pragma once

#include <map>
#include <string>
#include <components/Component.h>
namespace Game
{
	namespace Components
	{
		class SynthesisRecipe : public Component
		{
		public:
		private:
			std::map<std::string, int> RequiredItems;
			std::map<std::string, int> ResultingItems;
		};

	}
}