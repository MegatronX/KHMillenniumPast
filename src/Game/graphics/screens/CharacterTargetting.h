#pragma once
#ifndef _CHARACTERTARGETTING_H_
#define _CHARACTERTARGETTING_H_

#include <Actions/Action.h>

namespace Game
{
	namespace Graphics
	{
		class CharacterTargetting
		{
		public:
			CharacterTargetting()
			{
				
			}
		protected:
			Actions::Action* CurrentAction;
		};
	}

}

#endif