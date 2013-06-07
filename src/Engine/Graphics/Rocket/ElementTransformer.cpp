#include "ElementTransformer.h"
#include "ElementTransformInterface.h"
namespace Graphics
{
	namespace GameRocket
	{
		ElementTransformer::ElementTransformer(Rocket::Core::Element* targetEle) : target(targetEle)
		{
		}
		ElementTransformer::ElementTransformer(std::vector<ElementTransformationInterface*>& initialTransforms, Rocket::Core::Element* targetEle) : target(targetEle)
		{
			for (auto transform = initialTransforms.begin(); transform != initialTransforms.end(); ++transform)
			{
				transformations.push_back(eletransform_ptr(*transform));
			}
		}
		ElementTransformer::ElementTransformer(std::vector<eletransform_ptr>& initialTransforms) : transformations(initialTransforms)
		{

		}
		Rocket::Core::Element* ElementTransformer::GetTarget() const
		{
			return target;
		}
		void ElementTransformer::SetTarget(Rocket::Core::Element* targetEle)
		{
			target = targetEle;
		}
		void ElementTransformer::Update(const sf::Uint32 time)
		{
			//UpdateLock.Lock();
			Updating = true;
			for (auto transform = transformations.begin(); transform != transformations.end();)
			{
				(*transform)->Update(this, time);
				if ((*transform)->IsFinished())
				{
					transform = transformations.erase(transform);
				}
				else
				{
					++transform;
				}
			}
			if (!readytransformations.empty())
			{
				transformations.insert(transformations.end(), readytransformations.begin(), readytransformations.end());
				readytransformations.clear();
			}
			if (transformations.empty())
			{
				//Dispatch emptied
			}
			Updating = false;
			//UpdateLock.Unlock();
		}
		/*void ElementTransformer::AddTransformation(ElementTransformationInterface* transform)
		{
			if (Updating)
				readytransformations.push_back(eletransform_ptr(transform));
			else
				transformations.push_back(eletransform_ptr(transform));
		}*/
		void ElementTransformer::AddTransformation(eletransform_ptr transform)
		{
			if (Updating)
				readytransformations.push_back(transform);
			else
				transformations.push_back(transform);
		}
	}
}