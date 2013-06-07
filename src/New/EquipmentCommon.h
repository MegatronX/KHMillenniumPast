#pragma once
#ifndef _EQUIPCOM_H_
#define _EQUIPCOM_H_

namespace Game
{
	namespace Items
	{
		enum ArmorSlot
		{
			Head = 0,
			Chest = 1,
			Arms = 2,
			Legs = 3,
			//These may be optional
			Hands = 4,
			Feet = 5
		};
		const static int ArmorSlotcount = 6;

		enum EquipContext
		{
			MainHand,
			OffHand,
			ArmorHead,
			ArmorChest,
			ArmorLegs,
			ArmorHands,
			ArmorFeet,
			Accessory
		};
		const static int EquipmentContextCount = 8;
	
	}
}


#endif