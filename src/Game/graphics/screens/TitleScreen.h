#pragma once
#include "BasicRMLScreen.h"
class Engine;
namespace Game
{

	namespace Graphics
	{
		namespace Screens
		{
			class TitleScreen : public GameRocket::BasicRMLScreen
			{
			public:
				TitleScreen(Engine* engine);
				virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& action) override;
				virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& action) override;
				void HandleGameReadyEvent();
			private:
				void MakeAnimationSequence();
				bool ready;
			};
		}
	}
}