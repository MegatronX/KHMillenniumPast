#pragma once
#ifndef _GAMESCREEN_H_
#define _GAMESCREEN_H_
#include <Graphics/screens/Screen.h>

namespace Game
{
	namespace Graphics
	{
		namespace Screens
		{
			class GameScreen : public ::Graphics::Screens::Screen
			{
			public:
				virtual ~GameScreen() {};
				GameScreen(const std::string& name, ::Engine* engine, int id) : ::Graphics::Screens::Screen(name, engine, id)
				{

				}
			private:
			};
		}
	}
}

#endif
