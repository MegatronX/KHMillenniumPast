#pragma once
#ifndef _GAMEMAP_H_
#define _GAMEMAP_H_
#include <boost/shared_ptr.hpp>
#include <character/Party.h>
#include <character/BaseCharacter.h>
#include <boost/function.hpp>
#include <boost/python.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/signal.hpp>
#include <boost/signals.hpp>
#include <boost/bind.hpp>
#include <Engine.h>
#include <mapping/TileMap.h>
#include <system/input/InputModule.h>


#include <Entity.h>
#include <mapping/Exit.h>
#include <mapping/LayerTransition.h>
#include <mapping/MapObject.h>
#include <Mapping/MapCharacter.h>
#include <Mapping/MapObjectVisualizer.h>
namespace Graphics
{
	namespace Screens
	{
		class MapViewLayer;
	}
}

namespace Game
{
	namespace Mapping
	{
		struct MapCharacter;
		class MapEvent;
		class GameMap;

		typedef boost::mt19937 RNGType;
		class GameMap : public ::Mapping::TileMap, public Entity
		{
		public:
			GameMap();
			GameMap(const std::string &name, int tilesWide, int tilesHigh, int tilewidth, int tileheight);
			GameMap(const std::string &file, const std::string &name, Engine* engine);
			//GameMap(std::string &file, std::string &name);
			void SetMapCharacter(MapCharacter* character);
			void PlayMusic();
			void PauseMusic();

			float GetEncounterRate() const;
			void SetEncounterRate(const float rate);

			static boost::shared_ptr<GameMap> LoadMapFromXML(std::string &file, std::string &mapName);

			virtual void Draw(sf::RenderTarget &window, MapCharacter &mapChar, sf::View &characterView);

			virtual void Draw(sf::RenderTarget &window, sf::RenderStates states, MapCharacter &mapChar, sf::View &characterView);

			//Character::party_ptr GetPlayerParty() const;
			//void SetParty(const Character::party_ptr party);

			friend class ::Graphics::Screens::MapViewLayer;
			//virtual void ReleaseResources();

			bool IsAnEvent(int x, int y, int layer);

			//MapEvent& GetEvent(int x, int y, int layer);

			void ProcessEvents(MapCharacter& character);

			//void AddEvent(int x, int y, int layer);

			bool IsLayerTransition(int x, int y, int layer);

			//bool ProcessLayerChange(int x, int y, int layer, int &newLayer);

			void AddLayerTransition(int x, int y, int layer, int changeLayer);

			const MapExit& FindMapExit(int x, int y, int layer);

			void AddMapExit(int x, int y, int layer, const std::string& newMapName, const std::string& newMapFile, bool Active = true, int newx = 0, int newy = 0, int newlayer = 0);

			void AddMapExit(const MapExit& MExit);

			void AddObject(const std::string index, boost::shared_ptr<MapObject> obj);

			void AddEventToObject(const std::string& objIndex, boost::shared_ptr<MapEventComponent> evComp);

			const std::vector<std::string>& GetAddedSounds() const;

			virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) override;
			virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult) override;

			void SwapMapViaExit(MapExitComponent& exit);
			void SetExit(MapExitComponent* exit);
			bool ExitActive() const;
			MapExitComponent* GetActiveExit() const;

			virtual GameMap::RawClonePtr RawClone() const override;

			virtual ~GameMap();
		protected:
			void BuildExits();
			bool LoadGameMap(const std::string& filename, const std::string& name, bool clear = true);
			void BuildMap(const std::string& filename);
			//MapEvent InvalidEvent;
			bool UsePythonMove;
			bool UsePythonScriptClass;
			std::vector<std::string> addedSounds;
			sf::Texture Background;
			sf::Sprite BackSprite;
			std::vector<::Graphics::AnimatedSprite> Backgrounds;
			MapCharacter* Character;
			MapExitComponent* ActiveExit;
			//boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<std::string, boost::shared_ptr<MapEvent> > > > > NamedEvents;
			boost::unordered_map<std::string, MapEventComponent*> Events;
			boost::unordered_map<std::string, InputTriggeredMapEvent*> InputEvents;
			boost::unordered_map<std::string, boost::shared_ptr<MapObject>> MapObjects;
			//boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<std::string, boost::shared_ptr<MapObject> > > > > NamedMapObjects;
			//boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<int, boost::shared_ptr<MapObject> > > > AnonymousMapObjects;
			std::map<int, std::vector<boost::shared_ptr<MapObjectVisualizer> > > MapObjectVisualizers;

			//boost::uniform_real<float> floatRange;
			//boost::variate_generator<RNGType&, boost::uniform_real<float> > gen;//(rng, floatRange);
			/*boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<int, int> > > LayerTransitions; //x tile, y tile, layer
			boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<std::string, boost::shared_ptr<MapEvent> > > > > MapEvents;
			//boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<int, std::vector<MapEvent> > > > EventLookup;
			boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<std::string, boost::shared_ptr<MapObject> > > > > MapObjects;  //x, y, layer
			//boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<std::string, boost::shared_ptr<MapObjectVisualizer> > > > > MapObjectVisualizers;
			std::map<int, std::vector<boost::shared_ptr<MapObjectVisualizer> > > MapObjectVisualizers;
			//boost::unordered_map<int, boost::unordered_map<int, MapObjectVisualizerComponent*> > DrawableMapObjects; //Layer, ObjectID
			boost::unordered_map<int, boost::unordered_map<int, boost::unordered_map<int, ::Game::Mapping::MapExit> > > ExitLookup;*/
		private:
			float EncounterRate;
			RNGType rng;
			boost::variate_generator<RNGType&, boost::uniform_real<float> > RandomFloatGen;
		};
		typedef boost::shared_ptr<GameMap> gmap_ptr;
	}
}


#endif