#pragma once
#ifndef _EQUIPMNG_H_
#define _EQUIPMNG_H_

#include <Items/Item.h>
#include <Components/Component.h>
namespace Game
{
	
	namespace Character
	{
		class EquipmentManager : public Components::Component
		{
		public:
			EquipmentManager(BaseCharacter* owner) : Components(owner), Holder(owner)
			{
			}

			//If armor and slot are valid, equips armor into given alot and returns armor
			//previously equipped in that slot (or nullptr item_ptr if no armor was previously
			//in that slot. If slot is outside ArmorSlot enum, fails to add unless
			//AllowAdditionalArmorSlots is true
			
			const item_ptr GetMainHand() const
			{
				return MainHand;
			}
			const Items::WeaponComponent* GetMainHandWeapon() const
			{
				return MainHand->GetComponentAs<Items::WeaponComponent>(Items::WeaponComponentIndex);
			}
			const item_ptr GetOffHand() const
			{
				return OffHand;
			}
			const Items::WeaponComponent* GetOffHandWeapon() const
			{
				return OffHand->GetComponentAs<Items::WeaponComponent>(Items::WeaponComponentIndex);
			}

			std::pair<const Items::WeaponComponent*> GetWeaponSet const
			{
				std::pair<const Items::WeaponComponent*> weapComp;
				weapComp.first = GetMainHandWeapon();
				weapComp.second = GetOffHandWeapon();
				return weapComp;
			}

			item_ptr EquipArmor(const ArmorSlot slot, item_ptr armor)
			{
				//Validate Armor
				if (!EquipmentManager::ValidAsArmor(armor))
					return armor;
				//Need another layer of validation to ensure character can actually equip the armor
				return EquipArmor(static_cast<unsigned int>(slot), armor);
			}

			item_ptr EquipToMainHand(item_ptr weapon)
			{
				if (!EquipmentManager::ValidAsWeapon(weapon, Holder))
					return weapon;
				return SetEquip(MainHand, weapon);
			}

			item_ptr EquipToOffHand(item_ptr weapon)
			{
				if (!EquipmentManager::ValidAsWeapon(weapon, Holder))
					return weapon;
				return SetEquip(OffHand, weapon);
			}

			static bool ValidAsArmor(item_ptr armor, Character::BaseCharacter* holder)
			{
				if (armor.get() != nullptr && armor->GetComponentAs<Items::ArmorComponent*>(Items::ArmorComponentIndex) != nullptr)
				{
					auto vtion = armor->GetComponentAs<EquipmentValidationComponent*>(Items::EquipmentValidationComponentIndex);
					return vtion != nullptr && vtion->ValidForCharacter(holder);
				}
				return false;
			}
			static bool ValidAsWeapon(item_ptr weapon, Character::BaseCharacter* holder)
			{
				if (weapon.get() != nullptr && weapon->GetComponentAs<Items::WeaponComponent*>(Items::WeaponComponentIndex) != nullptr)
				{
					auto vtion = weapon->GetComponentAs<Items::EquipmentValidationComponent*>(Items::EquipmentValidationComponentIndex);
					return vtion != nullptr && vtion->ValidForCharacter(holder);
				}
				return false;
			}
			static bool ValidAsAccessory(item_ptr acc, Character::BaseCharacter* holder)
			{
				if (acc.get() != nullptr && acc->GetComponentAs<Items::AccessoryComponent*>(Items::AccessoryComponentIndex) != nullptr)
				{
					auto vtion = acc->GetComponentAs<Items::EquipmentValidationComponent*>(Items::EquipmentValidationComponentIndex);
					return vtion != nullptr && vtion->ValidForCharacter(holder);
				}
				return false;
			}
		protected:
			item_ptr SetEquip(item_ptr& slot, item_ptr equip)
			{
				if (equip.get() != nullptr)
				{
					auto temp = slot;
					slot = equip;
					auto eqComp = temp->GetComponentAs<EquipComponent*>(EquipComponentIndex);
					if (eComp != nullptr)
					{
						eComp->UnEquip(*Holder, this);
					}
					eqComp = equip->GetComponentAs<EquipComponent*>(EquipComponentIndex);
					if (eqComp != nullptr)
					{
						eqComp->Equip(*Holder, this)
					}
					return temp;
				}
				return equip;
				
			}
			item_ptr EquipArmor(const unsigned int slotNum, item_ptr armor)
			{
				if (slotNum > (Armor.size() - 1) && AllowAdditionalArmorSlots)
				{
					Armor.resize(slotNum + 1);
				}
				else
				{
#if DEBUG_ || DEBUG
					std::cerr << "Attempting to add armor to slot num " << slotNum << " while armor expansion not allowed.\n";
#endif
					return armor;
				}
				return SetEquip(ArmorSlots[slotNum], armor);
			}
			void SetOwner(BaseCharacter* owner)
			{
				Holder = owner;
			}
		private:
			BaseCharacter* Holder;
			//Weapons/shields/other hand based equipment
			item_ptr MainHand;
			item_ptr OffHand;

			//Armor
			bool AllowAdditionalArmorSlots;
			std::vector<item_ptr> ArmorSlots;

			//Accessories
			unsigned int AcessorySlots;
			std::vector<item_ptr> Accessories;

			
		};
	}
}

#endif