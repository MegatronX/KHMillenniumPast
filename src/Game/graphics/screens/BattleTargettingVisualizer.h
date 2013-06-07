#pragma once

#include <Actions/TargettingComponent.h>
#include <graphics/AnimatedDraw.h>
#include <System\Input\InputInterface.h>
#include <battle/BattleField.h>
class Engine;
namespace Game
{
	namespace Graphics
	{
		class BattleTargettingVisualizer : public Components::Component, public ::Graphics::AnimatedDraw, public ::Input::InputInterface
		{
		public:
			BattleTargettingVisualizer(Engine* eng, Entity* owner, Actions::TargettingComponent* targetting);
			virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) override;
			virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) override;
		protected:
			Actions::TargettingComponent* Targetting;
			Actions::TargetOption CurrentTargetting;
		private:
		};
	}
}