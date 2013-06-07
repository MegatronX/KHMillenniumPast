#pragma once
#ifndef _PYTHONITEMMODULE_H_
#define _PYTHONITEMMODULE_H_
#include <scripting/Python/ScriptHelpers.h>
#include <items/ItemDatabase.h>
#include <components/Component.h>
#include <components/UseComponent.h>
#include <items/EquipComponent.h>
#include <items/Inventory.h>
#include <memory>
//#include <scripting/ComponentModule.h>
//#include <Scripting/UseComponentWrap.h>
namespace Game
{
	namespace Scripting
	{
		/*void RegisterComp(Items::Item& item, const std::string& compName, std::auto_ptr<UseComponentWrap> comp)//, void* comp)
		{
			//item.RegisterComponent(compName, comp.get());
		//	comp.release();
		}*/

		class ItemWrap : public Items::Item
		{
		public:
			ItemWrap(PyObject* self) : self(self)
			{

			}

			ItemWrap(PyObject* self, const Items::Item& ref) : self(self), Items::Item(ref)
			{

			}

			ItemWrap(PyObject* self, const std::string& name) : self(self), Item(name)
			{

			}

			ItemWrap(PyObject* self, const std::string& itemName, const std::string& description, const unsigned int itemValue) : self(self), Item(itemName, description, itemValue)
			{

			}
			ClonePtr Clone() const override
			{
				return call_method<ClonePtr>(self, "Clone");
			}
			ClonePtr CloneDefault() const
			{
				return this->Items::Item::Clone();
			}
			PyObject* self;
		private:
		};

		class EquipComponentWrap : public Items::EquipComponent
		{
		public:
			EquipComponentWrap(PyObject* self, Entity* owner) : Items::EquipComponent(owner)
			{
				
			}

			bool Equip(Character::BaseCharacter& character) override
			{
				return call_method<bool>(self, "Equip", boost::ref(character));
			}

			bool EquipDefault(Character::BaseCharacter& character)
			{
				return false;
			}

			bool UnEquip(Character::BaseCharacter& character) override
			{
				return call_method<bool>(self, "UnEquip", boost::ref(character));
			}

			bool UnEquipDefault(Character::BaseCharacter& character)
			{
				return false;
			}

			ClonePtr Clone() const override
			{
				return call_method<ClonePtr>(self, "Clone");
			}
			ClonePtr CloneDefault() const
			{
				return this->Items::EquipComponent::Clone();
			}
			PyObject* self;
		};

		BOOST_PYTHON_MODULE(ItemModule)
		{
			using namespace Items;
			class_<Item, boost::shared_ptr<ItemWrap>, bases<Entity> >("Item", init<>())
				.def(init<const Items::Item&>())
				.def(init<const std::string&>())
				.def(init<const std::string&, const std::string&, const unsigned int>())
				.def("GetValue", &Item::GetValue)
				.def("GetDescription", &Item::GetDescription, return_value_policy<reference_existing_object>())
				.def("Clone", &Item::Clone, &ItemWrap::CloneDefault)
				;
			/*class_<Items::Item, bases<Entity> >("Item")
				.def(init<Items::Item&>())
				.def(init<const std::string&>())
				//.def("GetBaseValue", &Items::Item::GetBaseValue)
				//, boost::python::return_value_policy<boost::python::reference_existing_object>())
				.def("Clone", &Items::Item::Clone, boost::python::return_value_policy<boost::python::manage_new_object>())
				.def("__eq__", &Items::Item::operator ==)
				.def("__neq__", &Items::Item::operator !=)
				.def("__copy__", &generic__copy__<Items::Item>)
				.def("__deepcopy__", &generic__deepcopy__<Items::Item>)
				;*/

			class_<Items::ItemDatabase>("ItemDatabase", no_init)
				.def("AddItem", &Items::ItemDatabase::AddItem)
				.def("GetItemCount", &Items::ItemDatabase::GetItemCount)
				//.def("EmptyDatabase", &Items::ItemDatabase::EmptyDatabase)
				//.def("GetItemByName", &Item::ItemDatabase::GetItemByName, return_value_policy<reference_existing_object>)
				//.def("GetItemByID", &Item::ItemDatabase::GetItemByID, return_value_policy<reference_existing_object>)
				//.def("GetItem", &Items::ItemDatabase::GetItem)
				;
			/*class_<std::map<std::string, int> >("ItemCountMap")
				.def(map_indexing_suite<std::map<std::string, int> >())
				;*/
			class_<boost::unordered_map<std::string, int> >("ItemCountMapUnordered")
				.def(map_indexing_suite<boost::unordered_map<std::string, int> >())
				;
			/*
			class_<std::map<std::string, boost::shared_ptr<Character::BaseCharacter> > >("BasePartyMemberMap")
			.def(map_indexing_suite<std::map<std::string, boost::shared_ptr<Character::BaseCharacter> > >())
			;
			*/
			class_<Items::InventoryComponent, bases<Components::Component> >("InventoryComponent", init<Entity*>())
				.def("AddItem", (bool (Items::InventoryComponent::*)(const std::string&, int))&Items::InventoryComponent::AddItem, boost::python::arg("count") = 1)
				.def("GetItems", &Items::InventoryComponent::GetItems, return_value_policy<reference_existing_object>())
				.def("GetItemsCopy", &Items::InventoryComponent::GetItemsCopy)
				//.def("GetStatusResistance", (float (StatusEffects::StatusEffectsManager::*)(const StatusEffects::StatusEffect*) const)&StatusEffects::StatusEffectsManager::GetStatusResistance)
				;
		}
		
	}
}

#endif

