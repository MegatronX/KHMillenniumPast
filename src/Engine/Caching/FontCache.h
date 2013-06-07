/*
Caches fonts 
*/

#pragma once
#ifndef _FONTCACHE_H_
#define _FONTCACHE_H_
#include <caching\Cache.h>
#include <sfml\Graphics.hpp>
#include <sstream>
#include <string>
#include <configuration\AppConfiguration.h>
#include <boost\filesystem.hpp>

namespace Cache
{
	class FontCache : public TimerCache<sf::Font>
	{
	public:
		FontCache(int maxEntries, sf::Uint32 DefaultLife, sf::Uint32 UpdateTime);
		virtual res_ptr RequestResource(const std::string &indexer, sf::Uint32 time, const std::string extention = ".ttf", bool forceLoad = false) override;
		void InitializePaths(Configuration::AppConfiguration &configuration);
		const std::string& GetFontDirectory() const;
	protected:
		std::string fontDirectory;
		virtual res_ptr RequestResource(const std::string &indexer, GameStyle style, World world, ResourceClass resClass, sf::Uint32 time, sf::Uint32 lifeTime = 0, bool AsCopy = false, const std::string extension = ".ttf", bool forceLoad = false) override;
	private:
	};
}

#endif