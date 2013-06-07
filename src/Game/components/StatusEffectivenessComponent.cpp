#include "StatusEffectivenessComponent.h"
#include <Entity.h>
namespace Game
{
	namespace Components
	{
		const float StatusEffectivenessComponent::MaxEffectiveness = 2.f;
		const float StatusEffectivenessComponent::MinEffectiveness = -0.5f;
		StatusEffectivenessComponent::StatusEffectivenessComponent()
		{

		}
		StatusEffectivenessComponent::StatusEffectivenessComponent(Entity* owner, const boost::unordered_map<std::string, float>& effTable) : Component(owner, "StatusEffectivenessComponent" + owner->GetName(), "StatusEffectivenessComponent"), EffectivenessTable(effTable), DefaultEffectivenessTable(effTable)
		{

		}
		StatusEffectivenessComponent::RawClonePtr StatusEffectivenessComponent::RawClone() const
		{
			return new StatusEffectivenessComponent(*this);
		}
		float StatusEffectivenessComponent::GetEffectiveness(const std::string& statusEffect)
		{
			auto finder = EffectivenessTable.find(statusEffect);
			if (finder != EffectivenessTable.end())
			{
				float eff = finder->second;
				if (eff < MinEffectiveness)
					eff = MinEffectiveness;
				else if (eff > MaxEffectiveness)
					eff = MaxEffectiveness;
				return eff;
			}
			float eff = 1.f;
			EffectivenessTable[statusEffect] = eff;
			return eff;
		}
		float StatusEffectivenessComponent::GetEffectiveness(const std::string& statusEffect) const
		{
			auto finder = EffectivenessTable.find(statusEffect);
			if (finder != EffectivenessTable.end())
			{
				float eff = finder->second;
				if (eff < MinEffectiveness)
					eff = MinEffectiveness;
				else if (eff > MaxEffectiveness)
					eff = MaxEffectiveness;
				return eff;
			}
			return 1.f;
		}
		void StatusEffectivenessComponent::SetEffectivness(const std::string& statusEffect, const float value)
		{
			EffectivenessTable[statusEffect] = value;
		}
		void StatusEffectivenessComponent::IncrementEffectiveness(const std::string& statusEffect, const float adder)
		{
			auto finder = EffectivenessTable.find(statusEffect);
			if (finder != EffectivenessTable.end())
			{
				finder->second += adder;
			}
			else
			{
				EffectivenessTable[statusEffect] = 1.f + adder;
			}
		}
		void StatusEffectivenessComponent::MultiplyEffectiveness(const std::string& statusEffect, const float mult)
		{
			auto finder = EffectivenessTable.find(statusEffect);
			if (finder != EffectivenessTable.end())
			{
				finder->second *= mult;
			}
			else
			{
				EffectivenessTable[statusEffect] = 1.f * mult;
			}
		}
		void StatusEffectivenessComponent::RevertToDefault(const std::string& statusEffect)
		{
			auto finder = EffectivenessTable.find(statusEffect);
			auto defaultfinder = DefaultEffectivenessTable.find(statusEffect);
			if (defaultfinder != DefaultEffectivenessTable.end())
			{
				finder->second = defaultfinder->second;
			}
			else
			{
				finder->second = 1.f;
			}
		}
		const boost::unordered_map<std::string, float>& StatusEffectivenessComponent::GetEffectivenessTable() const
		{
			return EffectivenessTable;
		}
	}
}