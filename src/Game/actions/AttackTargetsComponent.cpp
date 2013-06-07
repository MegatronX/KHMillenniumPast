#include "AttackTargetsComponent.h"
#include <character/BaseCharacter.h>
#include <actions/Attack.h>
namespace Game
{
	namespace Actions
	{
		AttackTargetsComponent::AttackTargetsComponent(Attack* referenceAtk) : Component(referenceAtk, referenceAtk->GetName() + "AttackTargetComponent", "AttackTargetsComponent"), refAtk(referenceAtk)
		{

		}

		void AttackTargetsComponent::PushAttackToTargets()
		{
			if (refAtk != nullptr)
			{
				for (auto it = Targets.begin(); it != Targets.end(); ++it)
				{
					it->attack = boost::dynamic_pointer_cast<Attack>(refAtk->Clone());
				}

			}
		}
		AttackTarget& AttackTargetsComponent::GetTarget(const std::string& characterName)
		{

		}
	}
}