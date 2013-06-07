#pragma once
#ifndef _COUNTINGNUMBERTEXT_H_
#define _COUNTINGNUMBERTEXT_H_

#include <Graphics/AnimatedDraw.h>
#include <boost/lexical_cast.hpp>
namespace Game
{
	namespace Graphics
	{
		class CountingNumberText : public ::Graphics::AnimatedDraw
		{
		public:
			CountingNumberText(int value) : Number(value), TargetNumber(value), Counting(false), TransitionRate(0.f), RunningNumber(static_cast<float>(value)),
				NumberText(boost::lexical_cast<std::string>(value))
			{

			}
			void Draw(sf::RenderWindow& window) override
			{
				window.draw(NumberText);
			}
			void Draw(sf::RenderWindow& window, sf::Shader& shader) override
			{

			}

			void Update(const sf::Uint32 time, const float timeScale = 1.f) override
			{
				if (Counting)
				{
					sf::Uint32 Elapsed = time - LastUpdate;
					if (time < LastUpdate)
						Elapsed = 0;
					if (Elapsed > 0 && Elapsed > UpdateRate)
					{
						RunningNumber += TransitionRate * Elapsed;
						Number = static_cast<int>(RunningNumber);
						NumberText.setString(boost::lexical_cast<sf::String>(Number));
						LastUpdate = time;
					}
					if (time > TargetTime)
					{
						Counting = false;
						TransitionRate = 0.f;
						Number = TargetNumber;
						//RunningNumber = static_cast<int>
						
					}

					NumberText.setString(boost::lexical_cast<sf::String>(Number));
				}
			}

			void Count(int newValue, sf::Uint32 time, sf::Uint32 countTime, sf::Uint32 delay, sf::Uint32 updateRate = 0)
			{
				TargetNumber = newValue;
				RunningNumber = static_cast<float>(Number);
				TransitionRate = (static_cast<float>(TargetNumber) - RunningNumber) / static_cast<float>(time); 
				Counting = true;
				UpdateRate = updateRate;
				TargetTime = time + countTime;
				TransitionTime = countTime;
				LastUpdate = time;
				Delay = delay;
			}
		private:
			int Number;
			int TargetNumber;
			float RunningNumber;
			float TransitionRate;
			sf::Text NumberText;
			sf::Uint32 LastUpdate;
			sf::Uint32 UpdateRate;
			sf::Uint32 TransitionTime;
			sf::Uint32 TargetTime;
			sf::Uint32 Delay;
			bool Counting;

		};
	}
}

#endif