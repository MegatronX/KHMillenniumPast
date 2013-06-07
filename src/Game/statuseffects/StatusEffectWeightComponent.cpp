#include "StatusEffectWeightComponent.h"

namespace Game
{
	namespace StatusEffects
	{

		void StatusEffectWeightComponent::AddWeight(const std::string& SEName, const float weight, const bool AbsoluteWeight)
		{
			if (AbsoluteWeight && weight > 0.f)
			{
				if (weight >= 1.0f)
				{
					SEWeights.clear();
					SEWeights[SEName] = weight;
					TotalWeight = weight;
				}
				else if (weight >= 0.01f || weight <= -0.01f)
				{
					TotalWeight = TotalWeight / (1.0 - weight);
					SEWeights[SEName] = TotalWeight * weight;
				}
			}
			else if (!AbsoluteWeight)
			{
				SEWeights[SEName] += weight;
				TotalWeight += weight;
			}
		}
		void StatusEffectWeightComponent::ClearWeight(const std::string& SEName)
		{
			auto it = SEWeights.find(SEName);
			if (it != SEWeights.end())
			{
				SEWeights.erase(it);
			}
		}
		float StatusEffectWeightComponent::GetTotalWeight() const
		{
			return TotalWeight;
		}
		const boost::unordered_map<std::string, float>& StatusEffectWeightComponent::GetSEWeights() const
		{
			return SEWeights;
		}
		void StatusEffectWeightComponent::Moderate()
		{
			for (auto it = SEWeights.begin(); it != SEWeights.end(); ++it)
			{
				it->second /= TotalWeight;
			}
			TotalWeight = 1.0f;
		}
		void StatusEffectWeightComponent::SetRate(const std::string& SEName, float value)
		{
			SEWeights[SEName] = value;
		}
	}
}