#pragma once
#ifndef _ROCKETELEMENTTRANSFORMATION_H_
#define _ROCKETELEMENTTRANSFORMATION_H_

#include <sfml/System.hpp>
#include <boost/signal.hpp>
#include <boost/signals.hpp>
#include <boost/signals2.hpp>
namespace Graphics
{
	namespace GameRocket
	{
		class ElementTransformationInterface;
		//typedef boost::signal<void (sf::Uint32 time, ElementTransformationInterface*)> TransformationCompletedSignal;
		typedef std::pair<boost::shared_ptr<ElementTransformationInterface>, sf::Uint32> TransPair;
		typedef boost::signals2::signal<void (sf::Uint32 time, ElementTransformationInterface*)> TransformationCompletedSignal;
		class TimedTransform
		{
		public:
			TimedTransform(boost::shared_ptr<ElementTransformationInterface>& transform, const sf::Uint32 activationTime = 0, const sf::Uint32 duration = 0)
				: ActivationTime(activationTime), Transform(transform), TransDuration(duration)
			{
				//Rocket::Core::Element ele(
			}
			sf::Uint32 ActivationTime;
			boost::shared_ptr<ElementTransformationInterface> Transform;
			sf::Uint32 TransDuration;
		};
		class ElementTransformationInterface
		{
		public:
			ElementTransformationInterface(ElementTransformer* target, const sf::Uint32 currentTime, const sf::Uint32 EndTime_) : LastUpdate(currentTime), EndTime(EndTime_), Finished(EndTime_ <= currentTime)
			{
				//Finished = EndTime <= LastUpdate;
			}
			ElementTransformationInterface(const ElementTransformationInterface& src) :
				LastUpdate(src.LastUpdate), EndTime(src.EndTime), Finished(src.Finished)
			{

			}
			virtual void ReInitialize(const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* holder)
			{
				LastUpdate = currentTime;
				EndTime = EndTime_;
				Finished = EndTime <= LastUpdate;
			}
			virtual void Update(ElementTransformer* target, const sf::Uint32 time)
			{
				if (time > LastUpdate)
					LastUpdate = time;
				if (time > EndTime)
				{
					Finished = true;
					DispatchFinishedEvents(time);
					if (!PostTranformTransforms.empty())
					{
						for (auto trans = PostTranformTransforms.begin(); trans != PostTranformTransforms.end(); ++trans)
						{
							(*trans).first->ReInitialize(time, time + (*trans).second, target);
							target->AddTransformation(trans->first);
							//trans = PostTranformTransforms.erase(trans);
							//target->AddTransformation(*trans);
							//(*trans)->first.ReInitialize(target(*trans));
						}
					}
				}
			}
			boost::signals2::connection AddFinishedEvent(const TransformationCompletedSignal::slot_type& event)
			{
				return TransformFinishedEvent.connect(event);
			}
			/*void AddPostTransform(ElementTransformationInterface* transform, sf::Uint32 TransformTime)
			{
				PostTranformTransforms.push_back(TransPair(boost::shared_ptr<ElementTransformationInterface>(transform), TransformTime));
			}*/
			void AddPostTransform(boost::shared_ptr<ElementTransformationInterface> transform, const sf::Uint32 TransformTime)
			{
				PostTranformTransforms.push_back(TransPair(transform, TransformTime));
			}
			void AddTimedTransform(const sf::Uint32 ActivationTime, boost::shared_ptr<ElementTransformationInterface>& transform, const sf::Uint32 TransformTime)
			{
				NonPostTransforms.push_back(TimedTransform(transform, ActivationTime, TransformTime));
			}
			void DispatchFinishedEvents(sf::Uint32 time)
			{
				TransformFinishedEvent(time, this);
			}
			bool IsFinished() const
			{
				return Finished;
			}

			ElementTransformationInterface& ElementTransformationInterface::operator=(const ElementTransformationInterface& src)
			{
				if (this == &src)
					return *this;
				this->EndTime = src.EndTime;
				this->LastUpdate = src.LastUpdate;
				this->Finished = src.Finished;
				

				//TransformFinishedEvent2
				return *this;
			}
		protected:
			sf::Uint32 LastUpdate;
			sf::Uint32 EndTime;
			bool Finished;
			//TransformationCompletedSignal TransformFinishedEvent;
			TransformationCompletedSignal TransformFinishedEvent;
			std::vector<TransPair> PostTranformTransforms;
			std::vector<TimedTransform> NonPostTransforms;
		};

		typedef boost::shared_ptr<ElementTransformationInterface> eletransform_ptr;
	}
}
#endif