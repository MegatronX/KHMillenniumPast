#pragma once
#ifndef _ELEMENTWEIGHTCOMPONENT_H_
#define _ELEMENTWEIGHTCOMPONENT_H_
#include <boost/unordered_map.hpp>
#include <components/Component.h>
#include <elements/Elements.h>
namespace Game
{
	namespace Components
	{
		class ElementWeightComponent : public Component
		{
		public:
			ElementWeightComponent(Entity* owner) : Component(owner, owner != nullptr ? owner->GetName() + "ElementWeightComponent" : "ElementWeightComponent", "ElementWeightComponent"), TotalWeight(0.f)
			{

			}
			ElementWeightComponent(Entity* owner, boost::unordered_map<Elements::Element, float>& eleWeight) : Component(owner, owner != nullptr ? owner->GetName() + "ElementWeightComponent" : "ElementWeightComponent", "ElementWeightComponent"), ElementWeights(eleWeight), TotalWeight(0.f)
			{

			}

			void AddWeight(const Elements::Element ele, const float weight)
			{
				ElementWeights[ele] = weight;
				TotalWeight += weight;
			}

			float GetWeight(const Elements::Element ele)
			{
				auto it = ElementWeights.find(ele);
				if (it != ElementWeights.end())
				{
					if (TotalWeight > 0)
					{
						return it->second / TotalWeight;
					}
					return it->second;
				}
				return 0;
			}

			void Moderate() 
			{
				TotalWeight = 0;
				for (auto it = ElementWeights.begin(); it != ElementWeights.end(); ++it)
				{
					TotalWeight += it->second;
				}
				if (TotalWeight > 0)
				{
					for (auto it = ElementWeights.begin(); it != ElementWeights.end(); ++it)
					{
						it->second /= TotalWeight;
					}
				}
				TotalWeight = 1.f;
			}

			const boost::unordered_map<Elements::Element, float>& GetElementWeights()
			{
				return ElementWeights;
			}

			RawClonePtr RawClone() const override
			{
				return new ElementWeightComponent(*this);
			}
		private:
			float TotalWeight;
			boost::unordered_map<Elements::Element, float> ElementWeights;
		};
	}
}

#endif