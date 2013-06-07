#pragma once
#ifndef _ROCKETFADERTRANSFORM_H_
#define _ROCKETFADERTRANSFORM_H_

#include "ElementTransformer.h"
#include "ElementTransformInterface.h"
#include <boost/lexical_cast.hpp>
#include <Rocket/Controls.h>
#include <Rocket/Core.h>

namespace Graphics
{
	namespace GameRocket
	{
		class FaderTransform : public ElementTransformationInterface
		{
		public:
			FaderTransform(ElementTransformer* target, const sf::Uint8 StartingAlpha, const sf::Uint8 EndingAlpha, const sf::Uint32 currentTime, const sf::Uint32 endTime) :
				ElementTransformationInterface(target, currentTime, endTime), initialAlpha(StartingAlpha), targetAlpha(EndingAlpha), settingColor(255, 255, 255, StartingAlpha), transitionAlpha(static_cast<float>(StartingAlpha))
			{
				if (!Finished)
				{
					transitionRate = static_cast<float>(EndingAlpha - StartingAlpha) / static_cast<float>(endTime - currentTime);
					if (target != nullptr)
					{
						const Rocket::Core::Property* property = target->GetTarget()->GetLocalProperty("color");
						if (property)
						{
							auto preAl = settingColor.alpha;
							settingColor = property->value.Get<Rocket::Core::Colourb>();
							settingColor.alpha = preAl;
							//holder->GetTarget()->SetPro
						}
						baseColorString = ("rgba(" + boost::lexical_cast<std::string>((unsigned int)settingColor.red) + ", " + 
							boost::lexical_cast<std::string>((unsigned int)settingColor.green) + ", " +
							boost::lexical_cast<std::string>((unsigned int)settingColor.red) + ", ");

						target->GetTarget()->SetProperty(Rocket::Core::String("color"), MakeColorString(transitionAlpha));
					}
					
				}
			}
			virtual void ReInitialize(const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* holder) override
			{
				ElementTransformationInterface::ReInitialize(currentTime, EndTime_, holder);
				if (!Finished)
				{
					transitionAlpha = initialAlpha;
					const Rocket::Core::Property* property = holder->GetTarget()->GetLocalProperty("color");
					if (property)
					{
						if (EndTime_ > currentTime)
							transitionRate = static_cast<float>(this->targetAlpha - this->initialAlpha) / static_cast<float>(EndTime_ - currentTime);
						auto preAl = settingColor.alpha;
						settingColor = property->value.Get<Rocket::Core::Colourb>();
						settingColor.alpha = preAl;
						//holder->GetTarget()->SetPro
						baseColorString = ("rgba(" + boost::lexical_cast<std::string>((unsigned int)settingColor.red) + ", " + 
							boost::lexical_cast<std::string>((unsigned int)settingColor.green) + ", " +
							boost::lexical_cast<std::string>((unsigned int)settingColor.red) + ", ");

						holder->GetTarget()->SetProperty(Rocket::Core::String("color"), MakeColorString(transitionAlpha));
					}
					
				}
				
			}
			virtual void FullReInitialize(sf::Uint8 StartingAlpha, sf::Uint8 EndingAlpha, const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* holder)
			{
				initialAlpha = StartingAlpha;
				targetAlpha = EndingAlpha;
				transitionAlpha = initialAlpha;
				transitionRate = static_cast<float>(EndingAlpha - StartingAlpha) / static_cast<float>(EndTime_ - currentTime);
				ReInitialize(currentTime, EndTime_, holder);
			}
			virtual void Update(ElementTransformer* target, const sf::Uint32 time) override
			{
				if (!Finished)
				{
					sf::Uint32 Elapsed = time - LastUpdate;
					if (LastUpdate > time)
						Elapsed = 0;
					if (time > EndTime)
					{
						transitionAlpha = targetAlpha;
					}
					else
					{
						transitionAlpha += transitionRate * static_cast<float>(Elapsed);
					}
					settingColor.alpha = static_cast<Rocket::Core::byte>(transitionAlpha);
					
					target->GetTarget()->SetProperty(Rocket::Core::String("color"), MakeColorString(transitionAlpha));
					ElementTransformationInterface::Update(target, time);
				}
				
			}
		private:
			inline Rocket::Core::String MakeColorString(float alpha)
			{
				auto al = baseColorString + boost::lexical_cast<std::string>((int)alpha) + ")";
				return Rocket::Core::String(al.c_str());
				//std::string colorString("rgba(" + settingColor.red + ", " + settingColor.);
				//Rocket::Core::String color("rgba(") + static_cast<
			}
			float transitionAlpha;
			float transitionRate;
			std::string baseColorString;
			Rocket::Core::Colourb settingColor;
			sf::Uint8 targetAlpha;
			sf::Uint8 initialAlpha;
		};
	}
}

#endif