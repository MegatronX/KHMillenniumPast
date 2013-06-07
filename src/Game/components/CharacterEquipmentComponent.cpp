#include "CharacterEquipmentComponent.h"

namespace Game
{
	namespace Components
	{
		Items::ItemDatabase* CharacterEquipmentComponent::db = nullptr;
		void CharacterEquipmentComponent::AddLeftHandClass(const std::string& equipabbleClass)
		{
			AllowedLeftHandEquipmentClasses.insert(equipabbleClass);
		}
		bool CharacterEquipmentComponent::RemoveLeftHandClass(const std::string& equipabbleClass)
		{
			auto it = AllowedLeftHandEquipmentClasses.find(equipabbleClass);
			if (it != AllowedLeftHandEquipmentClasses.end())
			{
				AllowedLeftHandEquipmentClasses.erase(it);
				return true;
			}
			return false;
		}
		void CharacterEquipmentComponent::AddLeftHandException(const std::string& exceptionItem)
		{
			LeftHandEquipmentExceptionList.insert(exceptionItem);
		}
		bool CharacterEquipmentComponent::IsLeftHandBlackList() const
		{
			return LeftHandExceptionAsBlackList;
		}
		void CharacterEquipmentComponent::SetLeftHandBlackList(const bool blacklist)
		{
			LeftHandExceptionAsBlackList = blacklist;
		}
		bool CharacterEquipmentComponent::IsInLeftExceptionList(const std::string& itemName) const
		{
			return LeftHandEquipmentExceptionList.find(itemName) != LeftHandEquipmentExceptionList.end();
		}
		const std::string& CharacterEquipmentComponent::GetLeftHandItemName() const
		{
			return LeftHandEquipment;
		}
		const Items::Item* CharacterEquipmentComponent::GetLeftHandItem() const
		{
			Items::Item* item = nullptr;
			if (db != nullptr)
			{
				auto it = db->GetItemByName(LeftHandEquipment);
			}
			return item;
		}
		bool CharacterEquipmentComponent::SetLeftHandItem(std::string& itemName)
		{
			return false;
		}
		bool CharacterEquipmentComponent::SetLeftHandItem(Items::Item* item)
		{
			return false;
		}

		void CharacterEquipmentComponent::AddRightHandClass(const std::string& equipabbleClass)
		{
			AllowedRightHandEquipmentClasses.insert(equipabbleClass);
		}
		bool CharacterEquipmentComponent::RemoveRightHandClass(const std::string& equipabbleClass)
		{
			auto it = AllowedRightHandEquipmentClasses.find(equipabbleClass);
			if (it != AllowedRightHandEquipmentClasses.end())
			{
				AllowedRightHandEquipmentClasses.erase(it);
				return true;
			}
			return false;
		}
		void CharacterEquipmentComponent::AddRightHandException(const std::string& exceptionItem)
		{

		}
		bool CharacterEquipmentComponent::IsRightHandBlackList() const
		{
			return false;
		}
		void CharacterEquipmentComponent::SetRightHandBlackList(const bool blacklist)
		{

		}
		bool CharacterEquipmentComponent::IsInRightExceptionList(const std::string& itemName)
		{
			return false;
		}

		void CharacterEquipmentComponent::AddBodyClass(const std::string& equipabbleClass)
		{
			AllowedBodyEquipmentClasses.insert(equipabbleClass);
		}
		bool CharacterEquipmentComponent::RemoveBodyHandClass(const std::string& equipabbleClass)
		{
			auto it = AllowedBodyEquipmentClasses.find(equipabbleClass);
			if (it != AllowedBodyEquipmentClasses.end())
			{
				AllowedBodyEquipmentClasses.erase(it);
				return true;
			}
			return false;
		}
		void CharacterEquipmentComponent::AddBodyException(const std::string& exceptionItem)
		{

		}
		bool CharacterEquipmentComponent::IsBodyBlackList() const
		{
			return false;
		}
		void CharacterEquipmentComponent::SetBodyBlackList(const bool blacklist)
		{

		}
		bool CharacterEquipmentComponent::IsInBodyExceptionList(const std::string& itemName)
		{
			return false;
		}


		void CharacterEquipmentComponent::AddAccessoryClass(const std::string& equipabbleClass)
		{
			AllowedAccessoryEquipmentClasses.insert(equipabbleClass);
		}
		bool CharacterEquipmentComponent::RemoveAccessoryClass(const std::string& equipabbleClass)
		{
			auto it = AllowedAccessoryEquipmentClasses.find(equipabbleClass);
			if (it != AllowedAccessoryEquipmentClasses.end())
			{
				AllowedAccessoryEquipmentClasses.erase(it);
				return true;
			}
			return false;
		}
		void CharacterEquipmentComponent::AddAccessoryException(const std::string& exceptionItem)
		{

		}
		bool CharacterEquipmentComponent::IsAccesorryBlackList() const
		{
			return false;
		}
		void CharacterEquipmentComponent::SetAcessoryBlackList(const bool blacklist)
		{

		}
		bool CharacterEquipmentComponent::IsInAccessoryExceptionList(const std::string& itemName)
		{
			return false;
		}
		CharacterEquipmentComponent::RawClonePtr CharacterEquipmentComponent::RawClone() const
		{
			return new CharacterEquipmentComponent(*this);
		}
		void CharacterEquipmentComponent::SetItemDB(Items::ItemDatabase* db_)
		{
			db = db_;
		}
		void CharacterEquipmentComponent::SetItemDBSmrtPtr(boost::shared_ptr<Items::ItemDatabase>& db_)
		{
			db = db_.get();
		}
	}
}