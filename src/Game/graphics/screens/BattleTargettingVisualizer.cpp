#include "BattleTargettingVisualizer.h"
#include <Engine.h>
#include <Entity.h>
namespace Game
{
	namespace Graphics
	{
		BattleTargettingVisualizer::BattleTargettingVisualizer(Engine* eng, Entity* owner, Actions::TargettingComponent* targetting) : Component(owner, owner != nullptr ? owner->GetName() + "TargettingViz" : "NoOwnerTargettingViz", "TargettingVisualizer"),
			Targetting(targetting)
		{

		}
		bool BattleTargettingVisualizer::HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{
			return false;
		}
		bool BattleTargettingVisualizer::HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{
			return false;
		}
	}
}