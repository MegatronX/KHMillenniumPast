#pragma once
#ifndef _TEXTURECACHE_H_
#define _TEXTURECACHE_H_
#include <caching\Cache.h>
#include <sfml\Graphics.hpp>
#include <sstream>
#include <string>
#include <configuration\AppConfiguration.h>
#include <boost\filesystem.hpp>
#include <Caching/PathCollection.h>
namespace Cache
{
	class TextureCache : public Cache::TimerCache<sf::Texture>
	{
	public:
		TextureCache();
		TextureCache(int maxentries, sf::Uint32 defaultLife, sf::Uint32 updatetime, res_ptr fallback);
		res_ptr RequestResource(const std::string &indexer, sf::Uint32 time, const std::string extension = ".png", bool forceLoad = false) override;
		res_ptr RequestResource(const std::string &indexer, sf::Uint32 time, Cache::ResourceClass resClass, const std::string extension = ".png", bool forceLoad = false);
		res_ptr RequestResource(const std::string &indexer, Cache::GameStyle style, Cache::World world, Cache::ResourceClass resClass, sf::Uint32 time, sf::Uint32 lifeTime = 0, bool AsCopy = false, const std::string = ".png", bool forceLoad = false) override;
		virtual void InitializePaths(Configuration::AppConfiguration &configuration);
		//const PathCollection& GetPathCollection(const Cache::World world);
	protected:
		//Main String Collection
		std::string TileSetDirectory;
		PathCollection MainPaths;
		PathCollection FFVPaths;
		PathCollection FFVIPaths;
	};
}
#endif
