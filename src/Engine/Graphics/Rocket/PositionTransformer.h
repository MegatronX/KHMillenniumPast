#pragma once
#ifndef _ROCKETPOSITIONTRANSFORMER_H_
#define _ROCKETPOSITIONTRANSFORMER_H_
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
		class PositionTransformer : public ElementTransformationInterface
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
			PositionTransformer(ElementTransformer* transform, const sf::Vector2f& Target, const sf::Uint32 currentTime, const sf::Uint32 endTime, bool TransformIsOffset = true)
				: ElementTransformationInterface(transform, currentTime, endTime), IsOffset(TransformIsOffset)
			{
				if (TransformIsOffset)
				{
					TargOffset = Target;
					TransformRate = TargOffset / (static_cast<float>(endTime) - static_cast<float>(currentTime));
					//Add a 0 check here
					if (transform != nullptr)
					{
						auto left = transform->GetTarget()->GetProperty(Rocket::Core::String("left"));
						sf::Vector2f NewOffset(0.f, 0.f);
						if (left != nullptr)
							NewOffset.x = left->Get<float>();
						CumulativeTransform.x = NewOffset.x;
						auto top = transform->GetTarget()->GetProperty(Rocket::Core::String("top"));
						if (top != nullptr)
							NewOffset.y = top->Get<float>();
						CumulativeTransform.y = NewOffset.y;
						TargetPosition = NewOffset + TargOffset;
					}
				}
				else
				{
					if (transform != nullptr)
					{
						auto left = transform->GetTarget()->GetProperty(Rocket::Core::String("left"));
						sf::Vector2f NewOffset(0.f, 0.f);
						if (left != nullptr)
							NewOffset.x = left->Get<float>();
						CumulativeTransform.x = NewOffset.x;
						auto top = transform->GetTarget()->GetProperty(Rocket::Core::String("top"));
						if (top != nullptr)
							NewOffset.y = top->Get<float>();
						CumulativeTransform.y = NewOffset.y;
						TargetPosition = Target;
						TargOffset.x = Target.x - CumulativeTransform.x;// - Target;
						TargOffset.y = Target.y - CumulativeTransform.y;
						TransformRate = TargOffset / (static_cast<float>(endTime) - static_cast<float>(currentTime));
					}
				}
				
			}
			virtual void ReInitialize(const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* transform) override
			{
				ElementTransformationInterface::ReInitialize(currentTime, EndTime_, transform);
				if (!Finished)
				{
					if (IsOffset)
					{
						TransformRate = TargOffset / (static_cast<float>(EndTime_) - static_cast<float>(currentTime));
						//Add a 0 check here
						if (transform != nullptr)
						{
							auto left = transform->GetTarget()->GetProperty(Rocket::Core::String("left"));
							sf::Vector2f NewOffset(0.f, 0.f);
							if (left != nullptr)
								NewOffset.x = left->Get<float>();
							CumulativeTransform.x = NewOffset.x;
							auto top = transform->GetTarget()->GetProperty(Rocket::Core::String("top"));
							if (top != nullptr)
								NewOffset.y = top->Get<float>();
							CumulativeTransform.y = NewOffset.y;
							TargetPosition = NewOffset + TargOffset;
						}
					}
					else
					{
						if (transform != nullptr)
						{
							auto left = transform->GetTarget()->GetProperty(Rocket::Core::String("left"));
							sf::Vector2f NewOffset(0.f, 0.f);
							if (left != nullptr)
								NewOffset.x = left->Get<float>();
							CumulativeTransform.x = NewOffset.x;
							auto top = transform->GetTarget()->GetProperty(Rocket::Core::String("top"));
							if (top != nullptr)
								NewOffset.y = top->Get<float>();
							CumulativeTransform.y = NewOffset.y;
							TargOffset.x = TargetPosition.x - CumulativeTransform.x;// - Target;
							TargOffset.y = TargetPosition.y - CumulativeTransform.y;
							TransformRate = TargOffset / (static_cast<float>(EndTime_) - static_cast<float>(currentTime));
						}
					}
				}
				
			}
			void FullReInitialize(const sf::Vector2f& Target, const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* transform)
			{

				if (IsOffset)
				{
					TargOffset = Target;
					TransformRate = TargOffset / (static_cast<float>(EndTime_) - static_cast<float>(currentTime));
					//Add a 0 check here
					if (transform != nullptr)
					{
						auto left = transform->GetTarget()->GetProperty(Rocket::Core::String("left"));
						sf::Vector2f NewOffset(0.f, 0.f);
						if (left != nullptr)
							NewOffset.x = left->Get<float>();
						CumulativeTransform.x = NewOffset.x;
						auto top = transform->GetTarget()->GetProperty(Rocket::Core::String("top"));
						if (top != nullptr)
							NewOffset.y = top->Get<float>();
						CumulativeTransform.y = NewOffset.y;
						TargetPosition = NewOffset + TargOffset;
					}
				}
				else
				{
					if (transform != nullptr)
					{
						auto left = transform->GetTarget()->GetProperty(Rocket::Core::String("left"));
						sf::Vector2f NewOffset(0.f, 0.f);
						if (left != nullptr)
							NewOffset.x = left->Get<float>();
						CumulativeTransform.x = NewOffset.x;
						auto top = transform->GetTarget()->GetProperty(Rocket::Core::String("top"));
						if (top != nullptr)
							NewOffset.y = top->Get<float>();
						CumulativeTransform.y = NewOffset.y;
						TargetPosition = Target;
						TargOffset.x = Target.x - CumulativeTransform.x;// - Target;
						TargOffset.y = Target.y - CumulativeTransform.y;
						TransformRate = TargOffset / (static_cast<float>(EndTime_) - static_cast<float>(currentTime));
					}
				}

				ReInitialize(currentTime, EndTime_, transform);
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
					if (Finished)
					{
						if (TransformRate.x != 0.0f)
						{
							std::string newVal = boost::lexical_cast<std::string>((int)TargetPosition.x) + "px";
							eletarget->GetTarget()->SetProperty(Rocket::Core::String("left"), Rocket::Core::String(newVal.c_str()));
							//target->target->GetOffsetLeft()
						}
						if (TransformRate.y != 0.0f)
						{
							std::string newVal = boost::lexical_cast<std::string>((int)TargetPosition.y) + "px";
							eletarget->GetTarget()->SetProperty(Rocket::Core::String("top"), Rocket::Core::String(newVal.c_str()));
							//CumulativeTransform.y += TransformRate.y * static_cast<float>(Elapsed);
						}
					}
				}
				
			}

			bool IsOffset;
			sf::Vector2f TransformRate;
			sf::Vector2f TargOffset;
			sf::Vector2f TargetPosition;
			Rocket::Core::Vector2f CumulativeTransform;
			//sf::Vector2f CumulativeTransform;
			sf::Vector2f DeltaTransform;
		};
	}
}

#endif