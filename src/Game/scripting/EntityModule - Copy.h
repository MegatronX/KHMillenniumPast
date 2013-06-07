#pragma once
#ifndef _ENTITYMODULE_H_
#define _ENTITYMODULE_H_
#include <Entity.h>
namespace Game
{
	namespace Scripting
	{
		BOOST_PYTHON_MODULE(EntityModule)
		{
			enum_<EntityTypes>("EntityTypes")
				.value("ItemEntity", EntityTypes::ItemEntity)
				.value("CharacterEntity", EntityTypes::CharacterEntity)
				.value("StatusEffectEntity", EntityTypes::StatusEffectEntity)
				.value("AbilityEntity", EntityTypes::AbilityEntity)
				.value("TileMapEntity", EntityTypes::TileMapEntity)
				;
			class_<Entity>("Entity")
				.def(init<const std::string&, const int>())
				.def("", &Entity::GetID)
				.def("", &Entity::GetName, boost::python::return_value_policy<boost::python::reference_existing_object>())
				.def("", &Entity::GetNameHash)
				.def("", &Entity::GetType)
				.def("", &Entity::IsType)
				.def("__eq__", &Entity::operator ==)
				.def("__neq__", &Entity::operator !=)
				;
		}
		
	}
	
}

#endif