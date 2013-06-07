#pragma once
#ifndef _CHARACTEREQUIPMENTCOMPONENT_H_
#define _CHARACTEREQUIPMENTCOMPONENT_H_
#include <components/Component.h>
#include <boost/unordered_set.hpp>
#include <items/ItemDatabase.h>
namespace Game
{

	namespace Components
	{
		class CharacterEquipmentComponent : public Component
		{
		public:
			void AddLeftHandClass(const std::string& equipabbleClass);
			bool RemoveLeftHandClass(const std::string& equipabbleClass);
			void AddLeftHandException(const std::string& exceptionItem);
			bool IsLeftHandBlackList() const;
			void SetLeftHandBlackList(const bool blacklist = true);
			bool IsInLeftExceptionList(const std::string& itemName) const;
			const std::string& GetLeftHandItemName() const;
			const Items::Item* GetLeftHandItem() const;
			bool SetLeftHandItem(std::string& itemName);
			bool SetLeftHandItem(Items::Item* item);

			void AddRightHandClass(const std::string& equipabbleClass);
			bool RemoveRightHandClass(const std::string& equipabbleClass);
			void AddRightHandException(const std::string& exceptionItem);
			bool IsRightHandBlackList() const;
			void SetRightHandBlackList(const bool blacklist = true);
			bool IsInRightExceptionList(const std::string& itemName);

			void AddBodyClass(const std::string& equipabbleClass);
			bool RemoveBodyHandClass(const std::string& equipabbleClass);
			void AddBodyException(const std::string& exceptionItem);
			bool IsBodyBlackList() const;
			void SetBodyBlackList(const bool blacklist = true);
			bool IsInBodyExceptionList(const std::string& itemName);

			void AddAccessoryClass(const std::string& equipabbleClass);
			bool RemoveAccessoryClass(const std::string& equipabbleClass);
			void AddAccessoryException(const std::string& exceptionItem);
			bool IsAccesorryBlackList() const;
			void SetAcessoryBlackList(const bool blacklist = true);
			bool IsInAccessoryExceptionList(const std::string& itemName);

			virtual RawClonePtr RawClone() const override;
			static void SetItemDB(Items::ItemDatabase* db);
			static void SetItemDBSmrtPtr(boost::shared_ptr<Items::ItemDatabase>& db);
		private:
			static Items::ItemDatabase* db;
			std::string LeftHandEquipment;
			boost::unordered_set<std::string> AllowedLeftHandEquipmentClasses;
			boost::unordered_set<std::string> LeftHandEquipmentExceptionList;
			//if true, LeftHandEquipmentExceptionList acts as a black list, otherwise, whitelist
			bool LeftHandExceptionAsBlackList; //If true, 

			std::string RightHandEquipment;
			boost::unordered_set<std::string> AllowedRightHandEquipmentClasses;
			boost::unordered_set<std::string> RightHandEquipmentExceptionList;
			//if true, RightHandEquipmentExceptionList acts as a black list, otherwise, whitelist
			bool RightExceptionAsBlackList;


			std::string BodyEquipment;
			boost::unordered_set<std::string> AllowedBodyEquipmentClasses;
			boost::unordered_set<std::string> BodyEquipmentExceptionList;
			bool BodyExceptionAsBlackList;

			std::string HeadEquipment;
			boost::unordered_set<std::string> AllowedHeadEquipmentClasses;
			boost::unordered_set<std::string> HeadEquipmentExceptionList;
			bool HeadExceptionAsBlackList;

			std::vector<std::string> AccessoryEquipment;
			boost::unordered_set<std::string> AllowedAccessoryEquipmentClasses;
			boost::unordered_set<std::string> AccessoryEquipmentExceptionList;
			bool AccessoryExceptionAsBlackList;
			int AcessorySlots;
		};
	}
}

#endif