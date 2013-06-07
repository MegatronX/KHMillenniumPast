#pragma once
#ifndef _BLANKTRANSFORMER_H_
#define _BLANKTRANSFORMER_H_

#include "ElementTransformer.h"
#include "ElementTransformInterface.h"
#include <boost/lexical_cast.hpp>
#include <Rocket/Controls.h>
#include <Rocket/Core.h>

namespace Graphics
{
	namespace GameRocket
	{
		struct TargetProperty
		{
			Rocket::Core::String targetProperty;

		};

		class BlankTransformer : public ElementTransformationInterface
		{
		public:
			virtual void ReInitialize(const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* holder) override
			{

			}
			virtual void Update(ElementTransformer* target, const sf::Uint32 time) override
			{

			}
		private:

		};
	}
}

#endif