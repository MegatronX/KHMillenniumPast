#include "Ability.h"
#include <character/BaseCharacter.h>
namespace Game
{
	namespace Abilities
	{
		 // = boost::unordered_map<std::string, boost::unordered_map<std::string, int> >();
		Ability::Ability(Character::BaseCharacter* owner, const std::string& name, int priority) : StatusEffect(owner, name, true, 0, 0)
		{

		}
		Ability::RawClonePtr Ability::RawClone() const
		{
			return new Ability(*this);
		}
		int Ability::GetAPCost() const
		{
			auto character = GetHolder();
			if (character != nullptr)
			{
/*				auto overrides = APCostOverrides.find(character->GetName());
				if (overrides != APCostOverrides.end())
				{
					auto abilityOverride = (*overrides).second.find(this->GetName());
					if (abilityOverride != (*overrides).second.end())
					{
						return abilityOverride->second;
					}
				}*/
			}
			return APCost;
		}
		int Ability::GetInstances() const
		{
			return Instances;
		}
		int Ability::GetLevel() const
		{
			return Level;
		}
		Ability::~Ability()
		{
		}
	}
}