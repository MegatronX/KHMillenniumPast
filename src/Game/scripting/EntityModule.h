#pragma once
#ifndef _ENTITYMODULE_H_
#define _ENTITYMODULE_H_
#include <Entity.h>
#include <Scripting/Python/ScriptHelpers.h>
#include <boost/python.hpp>
using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		struct EntityWrap : public Entity
		{
		public:

			EntityWrap(PyObject* self_) : self(self_), Entity()
			{

			}
			EntityWrap(PyObject* self_, const std::string& name, const int type) : self(self_),  Entity(name, type)// ++EntityIDCounter)
			{

			}
			EntityWrap(PyObject* self_, const Entity& entity) : self(self_), Entity(entity)
			{

			}
			/*
			Entity();
			Entity(const std::string& name, const int type, const int ID = ++EntityIDCounter);
			Entity(const Entity& entity);
			*/
			Entity::ClonePtr Clone() const override
			{
				return call_method<Entity::ClonePtr>(self, "Clone");
			}
			Entity::ClonePtr CloneDefault() const
			{
				return this->Entity::Clone();
			}

			PyObject* self;
		};
		BOOST_PYTHON_MODULE(EntityModule)
		{
			enum_<EntityTypes>("EntityTypes")
				.value("ItemEntity", EntityTypes::ItemEntity)
				.value("CharacterEntity", EntityTypes::CharacterEntity)
				.value("StatusEffectEntity", EntityTypes::StatusEffectEntity)
				.value("AbilityEntity", EntityTypes::AbilityEntity)
				.value("TileMapEntity", EntityTypes::TileMapEntity)
				;
			class_<Entity, boost::shared_ptr<Entity> >("Entity")
				.def(init<>())
				.def(init<const std::string&, const int>())
				.def("GetID", &Entity::GetID)
				.def("GetName", &Entity::GetNameByVal)
				.def("GetNameHash", &Entity::GetNameHash)
				.def("GetType", &Entity::GetType)
				.def("IsType", &Entity::IsType)
				.def("GetComponent", &Entity::GetComponent, boost::python::return_value_policy<boost::python::reference_existing_object>())
				.def("RegisterComponent", &Entity::RegisterComponent, (boost::python::arg("ReplaceExisting") = true))
				.def("HasComponent", &Entity::HasComponent)
				.def("AddFlag", &Entity::AddFlag)
				.def("HasFlag", &Entity::HasFlag)
				.def("RemoveFlag", &Entity::RemoveFlag)
				.def("SetProperty", &Entity::SetProperty, (boost::python::arg("ReplaceExisting") = true))
				.def("GetProperty", &Entity::GetProperty, boost::python::return_value_policy<boost::python::reference_existing_object>())
				.def("HasProperty", &Entity::HasPropery)
				.def("RemoveProperty", &Entity::RemoveProperty)
				.def("GetValid", &Entity::GetValid)
				.def("SetValid", &Entity::SetValid)
				.def("Clone", &EntityWrap::CloneDefault)//, &EntityWrap::CloneDefault)
				.def("__eq__", &Entity::operator ==)
				.def("__neq__", &Entity::operator !=)
				.def("__copy__", &generic__copy__<Entity>)
				.def("__deepcopy__", &generic__deepcopy__<Entity>)
				;
			//class_<Items::Item, b
		}
		
	}
	
}

#endif