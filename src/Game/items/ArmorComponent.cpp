#include "ArmorComponent.h"

namespace Game
{
	using namespace Character;
	namespace Items
	{
		ArmorComponent::ArmorComponent(Entity* owner) : EquipComponent(owner)
		{

		}


		bool ArmorComponent::Equip(Character::BaseCharacter& character)
		{
			return false;
		}
		bool ArmorComponent::UnEquip(Character::BaseCharacter& character)
		{
			return false;
		}

		int ArmorComponent::GetArmorRating()
		{
			return BaseArmorRating;
		}
		int ArmorComponent::GetArmorRatingForCharacter(Character::BaseCharacter& character)
		{
			return BaseArmorRating;
		}
	}
}