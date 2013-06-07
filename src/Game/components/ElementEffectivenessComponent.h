#pragma once
#ifndef _ELEMENTEFFECTIVENESSCOMPONENT_H_
#define _ELEMENTEFFECTIVENESSCOMPONENT_H_
#include <components/Component.h>
#include <boost/unordered_map.hpp>
#include <elements/Elements.h>
namespace Game
{
	namespace Components
	{
		class ElementEffectivenessComponent : public Component
		{
		public:
			ElementEffectivenessComponent();
			ElementEffectivenessComponent(Entity* owner);
			ElementEffectivenessComponent(Entity* owner, boost::unordered_map<Elements::Element, float>& eff);
			virtual RawClonePtr RawClone() const override;
			float GetEffectiveness(const Elements::Element element);
			float GetEffectiveness(const Elements::Element element) const;
			void SetEffectivness(const Elements::Element element, float value);
			void IncrementEffectiveness(const Elements::Element element, float adder);
			void MultiplyEffectiveness(const Elements::Element element, float mult);
			void RevertToDefault(const Elements::Element element);
			const boost::unordered_map<Elements::Element, float>& GetEffectivenessTable() const;
		private:
			const static float MaxEffectiveness;
			const static float MinEffectiveness;
			boost::unordered_map<Elements::Element, float> EffectivenessTable;
			boost::unordered_map<Elements::Element, float> DefaultEffectivenessTable;
		};
		
	}
}



#endif