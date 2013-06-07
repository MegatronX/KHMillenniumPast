#include "ElementManager.h"

namespace Game
{
	namespace Elements
	{
		Elementmanager::ElementManager(Entity* owner) : ElementalDamageAffector(owner), ElementalAttackAffector(owner), ElementalAttackWeights(owner);
		{
		}

		float Elementmanager::GetOutgoingDamageMultiplier(const Element ele)
		{
			return ElementalAttackEffector.GetEffectiveness(ele);
		}

		float Elementmanager::GetIncomingDamageMultiplier(const Element ele)
		{
			return ElementalDamageAffector.GetEffectiveness(ele);
		}

		float Elementmanager::GetAttackWeight(const Element ele)
		{
			return ElementalAttackWeights.GetEffectiveness(ele);
		}
	}
}