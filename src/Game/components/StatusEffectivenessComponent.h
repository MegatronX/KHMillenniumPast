#pragma once
#ifndef _STATUSEFFECTIVENESSCOMPONENT_H_
#define _STATUSEFFECTIVENESSCOMPONENT_H_
#include <components/Component.h>
#include <boost/unordered_map.hpp>

namespace Game
{
	namespace Components
	{
		class StatusEffectivenessComponent : public Component
		{
		public:
			StatusEffectivenessComponent();
			StatusEffectivenessComponent(Entity* owner, const boost::unordered_map<std::string, float>& effTable = boost::unordered_map<std::string, float>());
			virtual RawClonePtr RawClone() const override;
			float GetEffectiveness(const std::string& statusEffect);
			float GetEffectiveness(const std::string& statusEffect) const;
			void SetEffectivness(const std::string& statusEffect, const float value);
			void IncrementEffectiveness(const std::string& statusEffect, const float adder);
			void MultiplyEffectiveness(const std::string& statusEffect, const float mult);
			void RevertToDefault(const std::string& statusEffect);
			const boost::unordered_map<std::string, float>& GetEffectivenessTable() const;
		private:
			const static float MaxEffectiveness;
			const static float MinEffectiveness;
			boost::unordered_map<std::string, float> EffectivenessTable;
			boost::unordered_map<std::string, float> DefaultEffectivenessTable;
		};
		
	}
}



#endif