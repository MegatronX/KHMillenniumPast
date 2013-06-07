//TODO: ENforce Max Entries behaviour. Timing Behaviour should work correctly

#pragma once
#ifndef _CACHE_H_
#define _CACHE_H_
#include <vector>
#include <list>
#include <sstream>
#include <boost\unordered_map.hpp>
#include <boost\unordered_set.hpp>
#include <boost\smart_ptr.hpp>
#include <boost\assign.hpp>
#include <sfml\System.hpp>
class Engine;
namespace Content
{
	class ContentManager;
}
namespace Cache
{
	enum GameStyle
	{
		FFV,
		FFVI,
		FFTactics,
		Main
	};
	static boost::unordered_map<std::string, GameStyle> NameToStyleMap = boost::assign::map_list_of
		("FFV", GameStyle::FFV)
		("Final Fantasy V", GameStyle::FFV)
		("FFVI", GameStyle::FFVI)
		("Final Fantasy VI", GameStyle::FFVI)
		("FFTactics", GameStyle::FFTactics)
		("FFT", GameStyle::FFTactics)
		("Final Fantasy Tactics", GameStyle::FFTactics)
		("Main", GameStyle::Main)
		("Default", GameStyle::Main);
	static boost::unordered_map<GameStyle, std::string> StyleToNameMap= boost::assign::map_list_of
		(GameStyle::FFV, "FFV")
		(GameStyle::FFVI, "FFVI")
		(GameStyle::FFTactics, "FFTactics")
		(GameStyle::Main, "Main");

	enum World
	{
		FF_V, 
		FF_VI,
		FF_T, 
		Atlantis,
		StationOfAwakening,
		Any,
	};

	enum ResourceClass
	{
		Background,
		BackColor,
		BattleBack,
		Boss,
		DDR,
		Chaser,        
		Enemy,
		Font,
		GUIBattleElement,
		GUIMenuElement,
		Guardian,
		Icon,
		MagicIcon,        
		MagicSheet,
		Music,
		OverworldSprite,
		Particle,
		QuadrupleTriad,
		Queue,
		SkillSheet,
		SoundEffect,
		SummonSprite,
		TileSet,
		TitleScreen,
		Voice,
		WorldImage,
	};

	template < class T >
	class TimerCache
	{
	public:
		typedef boost::shared_ptr<T> res_ptr;
		typedef std::pair<sf::Uint32, res_ptr > Resource;
		typedef boost::unordered_set<std::string> ResourceIndexSet;
		typedef boost::unordered_map<std::string, Resource> ResourceMap;

		TimerCache(int maxEntries, sf::Uint32 DefaultLifeTime, sf::Uint32 updatetime, res_ptr fallbackresource)
		{
			this->MaxEntries = maxEntries;
			this->ResourceLifeTime = DefaultLifeTime;
			this->UpdateTime = updatetime;
			this->DefaultResource = fallbackresource;
		}

		virtual void Update(sf::Uint32 time)
		{
			if (time - LastUpdate > UpdateTime)
			{
				LastUpdate = time;
				UpdateCache(time);
			}
		}

		virtual res_ptr RequestResource(const std::string &indexer, sf::Uint32 time, const std::string = ".png", bool forceLoad = false) = 0;
		virtual res_ptr RequestResource(const std::string &indexer, GameStyle styl, World world, ResourceClass resClass, sf::Uint32 time, sf::Uint32 lifeTime = 0, bool AsCopy = false, const std::string extention = ".png", bool forceLoad = false) = 0;

		res_ptr GetFallBack()
		{
			return DefaultResource;
		}
	protected:
		virtual void UpdateCache(sf::Uint32 time)
		{
			for (auto Resource = Resources.begin(); Resource != Resources.end(); ++Resource)
			{
				sf::Uint32 expireTime = (*Resource).second.first;
				if ((*Resource).second.first < time)
				{
					ResourceIndexSet::iterator res = ResourceSet.find((*Resource).first);
					if (res != ResourceSet.end())
						ResourceSet.erase(res);
					Resource = Resources.erase(Resource);
					if (Resource == Resources.end())
						break;
				}
			}
		}
		sf::Uint32 ResourceLifeTime;
		sf::Uint32 UpdateTime;
		sf::Uint32 LastUpdate;
		int MaxEntries;
		int CurrentEntries;
		res_ptr DefaultResource;
		ResourceIndexSet ResourceSet;
		ResourceMap Resources;
		GameStyle CurrentGameStyle;
		friend class Engine;
		friend class Content::ContentManager;
	private:


	};

}
#endif
