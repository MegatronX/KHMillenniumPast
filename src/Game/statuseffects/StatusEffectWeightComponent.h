#pragma once
#ifndef _SEWEIGHTCOMPONENT_H_
#define _SEWEIGHTCOMPONENT_H_
#include <components/Component.h>
#include <boost/unordered_map.hpp>

namespace Game
{
	namespace StatusEffects
	{
		class StatusEffectWeightComponent : public Components::Component
		{
		public:
			StatusEffectWeightComponent(Entity* owner);
			
			void AddWeight(const std::string& SEName, const float weight, const bool AbsoluteWeight = false);
			void ClearWeight(const std::string& SEName);
			float GetTotalWeight() const;
			const boost::unordered_map<std::string, float>& GetSEWeights() const;
			void Moderate();

			
		protected:
			void SetRate(const std::string& SEName, float value);
		private:
			boost::unordered_map<std::string, float> SEWeights;
			float TotalWeight;
		};
	}
}

#endif