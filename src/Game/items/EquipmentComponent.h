#pragma once
#ifndef _EQUIPMENTCOMPONENT_H_
#define _EQUIPMENTCOMPONENT_H_
#include <items/EquipComponent.h>
#include <character/StatsManager.h>
namespace Game
{
	namespace Items
	{
		const static std::string StatAdderIndex = "StatAdderComponent";
		const static std::string StatMultIndex = "StatMultComponent";
		const static std::string StatusEffectAdderIndex = "StatusAdderComponent";
		const static std::string ElementEffectAdderIndex = "ElementAdderComponent";
		const static std::string EquipmentComponentIndex = "EquipComponent";
		class EquipmentComponent : public EquipComponent
		{
		public:
			EquipmentComponent(Entity* owner);
			virtual bool Equip(Character::BaseCharacter& character) override;
			virtual bool UnEquip(Character::BaseCharacter& character) override;
		protected:
			//boost::unordered_map<Character::Stat, int> StatAdders;
			//boost::unordered_map<Character::Stat, float> StatMultipliers;
		private:
		};
	}
}

#endif
