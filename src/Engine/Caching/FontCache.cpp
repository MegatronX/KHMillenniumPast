#include "FontCache.h"

namespace Cache
{
	FontCache::FontCache(int maxEntries, sf::Uint32 DefaultLife, sf::Uint32 UpdateTime) : TimerCache<sf::Font>(maxEntries, DefaultLife, UpdateTime, res_ptr())//, res_ptr(new sf::Font(sf::Font::getDefaultFont())))
	{
		this->CurrentEntries = 0;
		this->LastUpdate = 0;
	}
	FontCache::res_ptr FontCache::RequestResource(const std::string &indexer, sf::Uint32 time, const std::string extension, bool forceLoad)
	{
		auto res = ResourceSet.find(indexer);
		if (res != ResourceSet.end() && !forceLoad)
		{
			auto WantedResource = Resources[indexer];
			WantedResource.first = time + ResourceLifeTime;
			return WantedResource.second;
		}
		else
		{
			std::string path(fontDirectory);
			path += indexer + extension;
			if (boost::filesystem::exists(path))
			{
				res_ptr newFont = res_ptr(new sf::Font());
				Resource newResource;
				newResource.first = time + ResourceLifeTime;
				if(newFont->loadFromFile(path))
				{
					newResource.second = newFont;
				}
				else
				{
					newResource.second = DefaultResource;
				}
				ResourceSet.insert(indexer);
				Resources[indexer] = newResource;
				return newResource.second;
			}
			else
			{
				return DefaultResource;
			}
		}
	}
	FontCache::res_ptr FontCache::RequestResource(const std::string &indexer, GameStyle style, World world, ResourceClass resClass, sf::Uint32 time, sf::Uint32 lifeTime, bool AsCopy, const std::string extension, bool forceLoad)
	{
		return RequestResource(indexer, time, extension);
	}
	
	const std::string& FontCache::GetFontDirectory() const
	{
		return fontDirectory;
	}
	
	void FontCache::InitializePaths(Configuration::AppConfiguration &configuration)
	{
		fontDirectory = configuration.GetApplicationSetting("ResourcesBaseDirectory") + 
			configuration.GetApplicationSetting("FontSubDir");
	}
}