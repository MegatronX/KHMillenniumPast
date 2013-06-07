#include "ElementEffectivenessComponent.h"
#include "Entity.h"
namespace Game
{
	namespace Components
	{
		const float ElementEffectivenessComponent::MaxEffectiveness = 4.f;
		const float ElementEffectivenessComponent::MinEffectiveness = -2.f;
		ElementEffectivenessComponent::ElementEffectivenessComponent() 
		{

		}
		ElementEffectivenessComponent::ElementEffectivenessComponent(Entity* owner) : Component(owner)
		{

		}
		ElementEffectivenessComponent::ElementEffectivenessComponent(Entity* owner, boost::unordered_map<Elements::Element, float>& eff) : Component(owner, "ElementEffectivenessComponent" + owner->GetName(), "ElementEffectivenessComponent"), EffectivenessTable(eff), DefaultEffectivenessTable(eff)
		{

		}
		ElementEffectivenessComponent::RawClonePtr ElementEffectivenessComponent::RawClone() const
		{
			return new ElementEffectivenessComponent(*this);
		}
		float ElementEffectivenessComponent::GetEffectiveness(const Elements::Element element)
		{
			auto finder = EffectivenessTable.find(element);
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
			EffectivenessTable[element] = eff;
			return eff;
		}
		float ElementEffectivenessComponent::GetEffectiveness(const Elements::Element element) const
		{
			auto finder = EffectivenessTable.find(element);
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
		void ElementEffectivenessComponent::SetEffectivness(const Elements::Element element, float value)
		{
			EffectivenessTable[element] = value;
		}
		void ElementEffectivenessComponent::IncrementEffectiveness(const Elements::Element element, float adder)
		{
			auto finder = EffectivenessTable.find(element);
			if (finder != EffectivenessTable.end())
			{
				finder->second += adder;
			}
			else
			{
				EffectivenessTable[element] = 1.f + adder;
			}
		}
		void ElementEffectivenessComponent::MultiplyEffectiveness(const Elements::Element element, float mult)
		{
			auto finder = EffectivenessTable.find(element);
			if (finder != EffectivenessTable.end())
			{
				finder->second *= mult;
			}
			else
			{
				EffectivenessTable[element] = 1.f * mult;
			}
		}
		void ElementEffectivenessComponent::RevertToDefault(const Elements::Element element)
		{
			auto finder = EffectivenessTable.find(element);
			auto defaultfinder = DefaultEffectivenessTable.find(element);
			if (defaultfinder != DefaultEffectivenessTable.end())
			{
				finder->second = defaultfinder->second;
			}
			else
			{
				finder->second = 1.f;
			}
		}
		const boost::unordered_map<Elements::Element, float>& ElementEffectivenessComponent::GetEffectivenessTable() const
		{
			return EffectivenessTable;
		}
	}
}