#pragma once
#ifndef _ROCKETTARGETPOSITIONTRANSFORMER_H_
#define _ROCKETTARGETPOSITIONTRANSFORMER_H_
#include "ElementTransformer.h"
#include "ElementTransformInterface.h"
#include <boost/lexical_cast.hpp>
#include <Rocket/Controls.h>
#include <Rocket/Core.h>
#include <sfml/System.hpp>

namespace Graphics
{
	namespace GameRocket
	{
		enum ElementTransformSlideType
		{
			Millisecond,
			Seconds
		};
		class TargetPositionTransformer : public ElementTransformationInterface
		{
		public:
			/*PositionTransformer(const sf::Uint32 currentTime, sf::Uint32 endTime, sf::Vector2f& SlideRate, ElementTransformSlideType rateType = Seconds)
				: ElementTransformationInterface(currentTime, endTime), CumulativeTransform(0.f, 0.f)
			{
				switch (rateType)
				{
				case Millisecond:
					{
						TransformRate = SlideRate;
					}
					break;
				case Seconds:
					{
						TransformRate = SlideRate / 1000.f;
					}
					break;
				}
			}*/
			TargetPositionTransformer(ElementTransformer* transform, sf::Vector2f& TargetPosition, const sf::Uint32 currentTime, sf::Uint32 endTime)
				: ElementTransformationInterface(transform, currentTime, endTime)
			{
				/*TargOffset = TargetOffset;
				TransformRate = TargetOffset / (static_cast<float>(endTime) - static_cast<float>(currentTime));
				//Add a 0 check here
				if (transform != nullptr)
				{
					auto left = transform->GetTarget()->GetProperty(Rocket::Core::String("left"));
					float NewOffset = 0.f;
					if (left != nullptr)
						NewOffset = left->Get<float>();
					CumulativeTransform.x = NewOffset;
					auto top = transform->GetTarget()->GetProperty(Rocket::Core::String("top"));
					NewOffset = 0.f;
					if (top != nullptr)
						NewOffset = top->Get<float>();
					CumulativeTransform.y = NewOffset;
				}*/
				
			}
			virtual void ReInitialize(const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* holder) override
			{
				ElementTransformationInterface::ReInitialize(currentTime, EndTime_, holder);
				if (!Finished)
				{
					//LastUpdate = currentTime;
					//EndTime = EndTime_;
					auto left = holder->GetTarget()->GetProperty(Rocket::Core::String("left"));
					float NewOffset = 0.f;
					if (left != nullptr)
						NewOffset = left->Get<float>();
					CumulativeTransform.x = NewOffset;
					auto top = holder->GetTarget()->GetProperty(Rocket::Core::String("top"));
					NewOffset = 0.f;
					if (top != nullptr)
						NewOffset = top->Get<float>();
					CumulativeTransform.y = NewOffset;
					
				}
				
			}
			void FullReInitialize(sf::Vector2f TargetOffset, const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* holder)
			{
				TargOffset = TargetOffset;
				TransformRate = TargetOffset / (static_cast<float>(currentTime) - static_cast<float>(EndTime_));
				ReInitialize(currentTime, EndTime_, holder);
			}
			virtual void Update(ElementTransformer* eletarget, const sf::Uint32 time) override
			{
				if (!Finished)
				{
					auto left = eletarget->GetTarget()->GetProperty(Rocket::Core::String("left"));
					sf::Uint32 Elapsed = time - LastUpdate;
					if (LastUpdate > time)
						Elapsed = 0;
					if (Elapsed > 0)
					{
						if (TransformRate.x != 0.0f)
						{
							CumulativeTransform.x += TransformRate.x * static_cast<float>(Elapsed);
							std::string newVal = boost::lexical_cast<std::string>((int)CumulativeTransform.x) + "px";
							eletarget->GetTarget()->SetProperty(Rocket::Core::String("left"), Rocket::Core::String(newVal.c_str()));
							//target->target->GetOffsetLeft()
						}
						if (TransformRate.y != 0.0f)
						{
							CumulativeTransform.y += TransformRate.y * static_cast<float>(Elapsed);
							std::string newVal = boost::lexical_cast<std::string>((int)CumulativeTransform.y) + "px";
							eletarget->GetTarget()->SetProperty(Rocket::Core::String("top"), Rocket::Core::String(newVal.c_str()));
							//CumulativeTransform.y += TransformRate.y * static_cast<float>(Elapsed);
						}
					}
					
					//auto test = eletarget->GetTarget()->GetOffsetParent();
					//eletarget->GetTarget()->SetOffset(CumulativeTransform, eletarget->GetTarget()->GetOffsetParent());
					ElementTransformationInterface::Update(eletarget, time);
				}
				
			}

			sf::Vector2f TransformRate;
			sf::Vector2f TargOffset;
			Rocket::Core::Vector2f CumulativeTransform;
			//sf::Vector2f CumulativeTransform;
			sf::Vector2f DeltaTransform;
		};
	}
}

#endif