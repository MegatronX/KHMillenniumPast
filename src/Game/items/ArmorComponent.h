#pragma once
#ifndef _ARMORCOMPONENT_H_
#define _ARMORCOMPONENT_H_

#include <items/EquipComponent.h>
#include <character/StatsManager.h>

namespace Game
{
	namespace Items
	{
		const static std::string ArmorComponentIndex = "ArmorComponentIndex";
		class ArmorComponent : public EquipComponent
		{
		public:
			ArmorComponent(Entity* owner);


			virtual bool Equip(Character::BaseCharacter& character);
			virtual bool UnEquip(Character::BaseCharacter& character);

			virtual int GetArmorRating();
			virtual int GetArmorRatingForCharacter(Character::BaseCharacter& character);
		protected:
			int BaseArmorRating;
			//int Base
		private:
		};
	}
}

#endif