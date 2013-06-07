#pragma once
#ifndef _PYTHONITEMMODULE_H_
#define _PYTHONITEMMODULE_H_
#include <scripting/Python/ScriptHelpers.h>
#include <items/ItemDatabase.h>
#include <components/Component.h>
#include <components/UseComponent.h>
#include <memory>
//#include <scripting/ComponentModule.h>
#include <Scripting/UseComponentWrap.h>
namespace Game
{
	namespace Scripting
	{
		void RegisterComp(Items::Item& item, const std::string& compName, std::auto_ptr<UseComponentWrap> comp)//, void* comp)
		{
			item.RegisterComponent(compName, comp.get());
			comp.release();
		}
		BOOST_PYTHON_MODULE(ItemModule)
		{
			
			class_<Items::Item, bases<Entity> >("Item")
				.def(init<Items::Item&>())
				.def(init<const std::string&>())
				//.def("GetBaseValue", &Items::Item::GetBaseValue)
				.def("GetComponent", &Items::Item::GetComponent, boost::python::return_value_policy<boost::python::reference_existing_object>())
				.def("RegisterComponent", &RegisterComp)//, boost::python::return_value_policy<boost::python::reference_existing_object>())
				.def("Clone", &Items::Item::Clone, boost::python::return_value_policy<boost::python::manage_new_object>())
				.def("__eq__", &Items::Item::operator ==)
				.def("__neq__", &Items::Item::operator !=)
				.def("__copy__", &generic__copy__<Items::Item>)
				.def("__deepcopy__", &generic__deepcopy__<Items::Item>)
				;

			class_<Items::ItemDatabase>("ItemDatabase", no_init)
				.def("AddItem", &Items::ItemDatabase::AddItem)
				;
		}
		
	}
}

#endif

