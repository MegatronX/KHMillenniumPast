#pragma once

#include <components/Component.h>
#include <system/Input/InputInterface.h>

namespace Game
{
	namespace Components
	{
		class InputComponent : public Component, public ::Input::InputInterface
		{
		public:
			InputComponent(Entity* owner) : Component(owner, owner != nullptr ? owner->GetName() + "InputComponent" : "NoNameInputComponent", "InputComponent")
			{

			}

			InputComponent::RawClonePtr RawClone() const override
			{
				return new InputComponent(*this);
			}
		protected:

		};
	}
}