#pragma once
#ifndef _ELEMENTTRANSFORMWRAP_H_
#define _ELEMENTTRANSFORMWRAP_H_

#include <Graphics/Rocket/ElementTransformer.h>
#include <Graphics/Rocket/ElementTransformInterface.h>
#include <boost/python.hpp>
namespace Scripting
{
	class ElementTransformationInterfaceWrap : public Graphics::GameRocket::ElementTransformationInterface
	{
	public:
		ElementTransformationInterfaceWrap(PyObject* self_);
		ElementTransformationInterfaceWrap(PyObject* self_, Graphics::GameRocket::ElementTransformer* target, const sf::Uint32 currentTime, const sf::Uint32 EndTime_);
		void ReInitialize(const sf::Uint32 currentTime, const sf::Uint32 EndTime_, Graphics::GameRocket::ElementTransformer* holder) override;
		void Update(Graphics::GameRocket::ElementTransformer* target, const sf::Uint32 time) override;
		void ReInitializeDefault(const sf::Uint32 currentTime, const sf::Uint32 EndTime_, Graphics::GameRocket::ElementTransformer* holder);
		void UpdateDefault(Graphics::GameRocket::ElementTransformer* target, const sf::Uint32 time);
	private:
		PyObject* self;
	};
}

#endif
