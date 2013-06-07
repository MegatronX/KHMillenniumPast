#include "MapEvent.h"
#include "GameMap.h"
namespace Game
{
	namespace Mapping
	{
		/*
		MapEvent::MapEvent() : MapObject("MapEvent", 0, 0, 0), Valid(false)
		{

		}
		MapEvent::MapEvent(int x, int y, int layer, bool valid, const std::string& EventName) : MapObject(EventName, x, y, layer), Valid(valid)
		{
			sf::Vector3i test;
			
		}

		MapEvent::MapEvent(int x, int y, int layer, sf::IntRect area, bool valid, const std::string& EventName) : MapObject(EventName, x, y, layer), Valid(valid)
		{
			sf::Vector3i test;

		}

		void MapEvent::EventActivated(GameMap* map, MapCharacter* character)
		{
			if (Valid)
				DispatchEvents(map, character);
		}

		void MapEvent::AddEventCallback(const std::string& name, const EventHitSignal& handler)
		{
			MapEventCallbacks[name] = handler;
		}
		bool MapEvent::RemoveEventCallback(const std::string& name)
		{
			bool removed = false;
			auto ev = MapEventCallbacks.find(name);
			if (ev != MapEventCallbacks.end())
			{
				MapEventCallbacks.erase(ev);
				removed = true;
			}
			return removed;
		}
		void MapEvent::DispatchEvents(GameMap* map, MapCharacter* character)
		{
			for (auto ev = MapEventCallbacks.begin(); ev != MapEventCallbacks.end(); ++ev)
			{
				ev->second(character, map, this);
			}
		}
		*/

		MapEventComponent::MapEventComponent(MapObject* owner, const std::string& name, const bool active) : Components::Component(owner), OwnerObject(owner)
		{

		}

		/*MapEventComponent::MapEventComponent(MapObject* owner, const int x, const int y, const int layer, const bool active) : Components::Component(owner), OwnerObject(owner)
		{

		}*/

		bool MapEventComponent::InEventRange(const MapCharacter& character)
		{

			return OwnerObject != nullptr && 
				static_cast<int>(character.MapTilePosition.x) == OwnerObject->MapTilePosition.x &&
				static_cast<int>(character.MapTilePosition.y)     == OwnerObject->MapTilePosition.y &&
				static_cast<int>(character.DrawLayer)         == OwnerObject->MapTilePosition.z;
		}

		bool MapEventComponent::IsActive() const
		{
			return Active;
		}

		void MapEventComponent::SetActive(const bool active)
		{
			Active = active;
		}

		void MapEventComponent::ProcessEvent(GameMap& map, MapCharacter& playerChar)
		{

		}

		MapObject* MapEventComponent::GetOwnerMapObject()
		{
			return OwnerObject;
		}

		void MapEventComponent::AddEventCallback(const std::string& name, const EventHitSignal& handler)
		{
			MapEventCallbacks[name] = handler;
		}
		bool MapEventComponent::RemoveEventCallback(const std::string& name)
		{
			bool removed = false;
			auto ev = MapEventCallbacks.find(name);
			if (ev != MapEventCallbacks.end())
			{
				MapEventCallbacks.erase(ev);
				removed = true;
			}
			return removed;
		}
		void MapEventComponent::DispatchEvents(GameMap* map, MapCharacter* character)
		{
			for (auto ev = MapEventCallbacks.begin(); ev != MapEventCallbacks.end(); ++ev)
			{
				ev->second(character, map, this);
			}
		}

		MapEventComponent::RawClonePtr MapEventComponent::RawClone() const
		{
			return new MapEventComponent(*this);
		}

	}
}
