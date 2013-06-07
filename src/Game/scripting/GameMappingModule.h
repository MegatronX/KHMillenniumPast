#pragma once

#include <Scripting/Python/ScriptHelpers.h>
#include <Mapping/GameMap.h>
#include <Mapping/MapCharacterMovementHandler.h>
#include <Entity.h>
#include <Components/Component.h>
using namespace Game::Mapping;

namespace Scripting
{
	class MapCharacterMovementHandlerComponentWrap : public MapCharacterMovementHandlerComponent
	{
	public:
		MapCharacterMovementHandlerComponentWrap(PyObject* self_, Game::Entity* owner) : self(self_), MapCharacterMovementHandlerComponent(owner)
		{

		}
		MapCharacterMovementHandlerComponentWrap(PyObject* self_, const MapCharacterMovementHandlerComponent& cmp) : self(self_), MapCharacterMovementHandlerComponent(cmp)
		{

		}

		virtual void HandleCharacterMovement(GameMap& map, MapCharacter& mchar) override
		{
			return call_method<void>(self, "HandleCharacterMovement", boost::ref(map), boost::ref(mchar));
		}

		void HandleCharacterMovementDefault(GameMap& map, MapCharacter& mchar)
		{
			return this->MapCharacterMovementHandlerComponent::HandleCharacterMovement(map, mchar);
		}

		MapCharacterMovementHandlerComponent::ClonePtr Clone() const override
		{
			return call_method<MapCharacterMovementHandlerComponent::ClonePtr>(self, "Clone");
		}
		MapCharacterMovementHandlerComponent::ClonePtr CloneDefault() const
		{
			return this->MapCharacterMovementHandlerComponent::Clone();
		}
		PyObject* self;
	};
	/*
	class InputComponentWrap : public Components::InputComponent
	{

	bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) override
	{ 
	return call_method<bool>(self, "HandleKeyPressed", time, boost::python::ptr(inputModule), boost::ref(actionResult));
	//return call_method<bool>(self, "IsCritical", boost::ref(target), boost::ref(action), boost::ref(mechanics));
	}
	bool HandleKeyPressedDefault(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
	{ 
	return this->::Input::InputInterface::HandleKeyPressed(time, inputModule, actionResult);
	}
	bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) override
	{
	return call_method<bool>(self, "HandleKeyReleased", time, boost::python::ptr(inputModule), boost::ref(actionResult));
	}
	bool HandleKeyReleasedDefault(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
	{ 
	return this->::Input::InputInterface::HandleKeyReleased(time, inputModule, actionResult);
	}
	Components::InputComponent::ClonePtr Clone() const override
	{
	return call_method<Components::Component::ClonePtr>(self, "Clone");
	}
	Components::InputComponent::ClonePtr CloneDefault() const
	{
	return this->Components::InputComponent::Clone();
	}
	PyObject* self;
	};
	*/
	BOOST_PYTHON_MODULE(GameMappingModule)
	{
		//boost::python::scope().attr("DamageFinalizerIndex") = Battle::OutgoingAttackIndexer;

		boost::python::scope().attr("MovementComponentIndex") = MovementComponentIndex;
		//(float (StatusEffects::StatusEffectsManager::*)(const std::string&) const)&StatusEffects::StatusEffectsManager::GetStatusResistance)
		//def("", &MovementComponentIndex);
		class_<MapCharacter>("MapCharacter", init<>())
			.def("SlideMapPosition", (void (MapCharacter::*)(const sf::Vector2f &, const sf::Vector2i &, sf::Uint32, sf::Uint32))&MapCharacter::SlideMapPosition)
			.def("SlideMapPosition", (void (MapCharacter::*)(const sf::Vector2f &, sf::Uint32, sf::Uint32))&MapCharacter::SlideMapPosition)
			//.def("SlideMapPosition", &MapCharacter::SlideMapPosition)
			.def("AddFinishedEvent", &MapCharacter::AddFinishedEvent)
			.def("RemoveFinishedEvent", &MapCharacter::RemoveFinishedEvent)
			.def("DispatchFinishedEvents", &MapCharacter::DispatchFinishedEvents)
			.def_readwrite("MapPosition", &MapCharacter::MapPosition)
			.def_readwrite("MapTilePosition", &MapCharacter::MapTilePosition)
			.def_readwrite("ScreenPosition", &MapCharacter::ScreenPosition)
			//.def_readwrite("FollowInX", &MapCharacter::FollowInX)
			//.def_readwrite("FollowInY", &MapCharacter::FollowInY)
			.def_readwrite("InTransit", &MapCharacter::InTransit)
			.def_readwrite("DrawLayer", &MapCharacter::DrawLayer)
			//.def_readwrite("", &MapCharacter:)
			//.def_readwrite("", &MapCharacter:)
			;
		class_<GameMap, bases<::Mapping::TileMap, Game::Entity> >("GameMap", init<>())
			.def(init<std::string&, int, int, int, int>())
			.def(init<std::string&, std::string&, ::Engine*>())
			.def("GetEncounterRate", &GameMap::GetEncounterRate)
			.def("PauseMusic", &GameMap::PauseMusic)
			.def("PlayMusic", &GameMap::PlayMusic)
			.def("SetEncounterRate", &GameMap::SetEncounterRate)
			/*.def("", &GameMap::)
			.def("", &GameMap:)
			.def("", &GameMap:)
			.def("", &GameMap:)
			.def("", &GameMap:)*/
			;
		class_<MapCharacterMovementHandlerComponent, boost::shared_ptr<MapCharacterMovementHandlerComponentWrap>, bases<Game::Components::Component> >("MapCharacterMovementHandlerComponent",  init<Game::Entity*>())
			.def(init<const MapCharacterMovementHandlerComponent&>())
			.def("HandleCharacterMovement", &MapCharacterMovementHandlerComponentWrap::HandleCharacterMovementDefault)
			.def("CloneDefault", &MapCharacterMovementHandlerComponentWrap::CloneDefault)
			//.def("", &MapCharacterMovementHandlerComponent)
			//.def("", &MapCharacterMovementHandlerComponent)
			;
	}
}