#pragma once
#ifndef _MAPEVENT_H_
#define _MAPEVENT_H_

#include <Entity.h>
#include <boost/function.hpp>
#include <boost/unordered_map.hpp>
#include <Entity.h>
#include <SFML/Graphics.hpp>
#include <Mapping/MapObject.h>
#include <boost/unordered_set.hpp>
#include <components/Component.h>
#include <system/Input/InputModule.h>
namespace Game
{
	namespace Mapping
	{
		struct MapCharacter;
		class GameMap;
		class MapEventComponent;
		typedef boost::function<void(MapCharacter*, GameMap*, MapEventComponent*)> EventHitSignal;

		/*class MapEvent : public MapObject
		{
		public:
			MapEvent();

			MapEvent(int x, int y, int layer, bool valid = true, const std::string& EventName = "MapEvent");

			MapEvent(int x, int y, int layer, sf::IntRect EventArea, bool valid = true, const std::string& EventName = "AreaMapEvent");

			virtual void EventActivated(GameMap* map, MapCharacter* character);

			virtual bool InActivationRange(int x, int y, int layer);

			void AddEventCallback(const std::string& name, const EventHitSignal& handler);
			bool RemoveEventCallback(const std::string& name);
			void DispatchEvents(GameMap* map, MapCharacter* character);
			
		private:
			bool KeyPressActivation;
			bool Valid;
			boost::unordered_map<std::string, EventHitSignal> MapEventCallbacks;
		};*/

		const std::string MapEventIndex = "MEv";

		class MapEventComponent : public Components::Component
		{
		public:
			MapEventComponent(MapObject* owner, const std::string& name = "DefaultEvent", bool active = false);

			//MapEventComponent(MapObject* owner, const int x, const int y, const int layer, const std::string& name = "DefaultEvent", const bool active = false);

			virtual bool InEventRange(const MapCharacter& character);

			bool IsActive() const;

			void SetActive(const bool active);

			virtual void ProcessEvent(GameMap& map, MapCharacter& playerChar);

			MapObject* GetOwnerMapObject();

			void AddEventCallback(const std::string& name, const EventHitSignal& handler);
			bool RemoveEventCallback(const std::string& name);
			void DispatchEvents(GameMap* map, MapCharacter* character);

			virtual MapEventComponent::RawClonePtr RawClone() const override;
		protected:
			bool Active;
			MapObject* OwnerObject;

			boost::unordered_map<std::string, EventHitSignal> MapEventCallbacks;
		};

		const std::string InputMapEventIndex = "IMEv";

		class InputTriggeredMapEvent : public MapEventComponent
		{
		public:
			InputTriggeredMapEvent(MapObject* owner, bool active = false) : MapEventComponent(owner, "InputTriggeredEvent", active)
			{

			}

			bool InputTriggering(const sf::Uint32 time, const ::Input::InputModule* inputModule)
			{
				return false;
			}

			virtual MapEventComponent::RawClonePtr RawClone() const override
			{
				return new InputTriggeredMapEvent(*this);
			}
		};
	}
}

#endif