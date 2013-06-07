#pragma once
#ifndef _ELEMENTMANAGEMENT_H_
#define _ELEMENTMANAGEMENT_H_

#include <Components/ElementEffectivenessComponent.h>

namespace Game
{
	namespace Actions
	{
		class Action;
	}
	namespace Elements
	{
		class ElementManager : public Components::Component
		{
		public:
			ElementManager(Entity* owner);
			
			float GetOutgoingDamageMultiplier(const Element ele);

			float GetIncomingDamageMultiplier(const Element ele);

			float GetAttackWeight(const Element ele);

		private:
			Components::ElementEffectivenessComponent ElementalDamageAffector;
			Components::ElementEffectivenessComponent ElementalAttackAffector;
			Components::ElementEffectivenessComponent ElementalAttackWeights;
		}
	}
}

#endif