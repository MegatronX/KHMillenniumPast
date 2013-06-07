#pragma once
#ifndef _INPUTINTERFACE_H_
#define _INPUTINTERFACE_H_
#include <sfml/System.hpp>
#include <sfml/Window.hpp>
#include <System/Input/InputModule.h>
namespace Input
{
	class InputInterface
	{
	public:
		InputInterface(bool acceptingInputs = true) : AcceptingInputs(acceptingInputs)
		{

		}
		bool IsAcceptingInputs() const
		{
			return AcceptingInputs;
		}
		void SetAcceptingInputs(const bool value)
		{
			AcceptingInputs = value;
		}
		virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) { return false;}
		virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) { return false;}
	private:
		bool AcceptingInputs;
	};
}

#endif