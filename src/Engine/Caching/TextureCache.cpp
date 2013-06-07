#include "TextureCache.h"
#include <iostream>
namespace Cache
{
	TextureCache::TextureCache() : Cache::TimerCache<sf::Texture>(50, 50, 50, res_ptr())
	{

	}

	TextureCache::TextureCache(int maxentries, sf::Uint32 defaultLife, sf::Uint32 updatetime, res_ptr fallback)
		: Cache::TimerCache<sf::Texture>(maxentries, defaultLife, updatetime, fallback)
	{
		this->MaxEntries = maxentries;
		this->ResourceLifeTime = defaultLife;
		this->UpdateTime = updatetime;
		this->DefaultResource = fallback;
		this->LastUpdate = 0;
		CurrentEntries = 0;
	}
	TextureCache::res_ptr TextureCache::RequestResource(const std::string &indexer, sf::Uint32 time, const std::string extension, bool forceLoad)
	{
		return DefaultResource;
	}
	TextureCache::res_ptr TextureCache::RequestResource(const std::string &indexer, sf::Uint32 time, Cache::ResourceClass resClass, const std::string extension, bool forceLoad)
	{
		return RequestResource(indexer, Cache::GameStyle::Main, Cache::World::Any, resClass, time, 0, false, extension);
	}
	TextureCache::res_ptr TextureCache::RequestResource(const std::string &indexer, Cache::GameStyle style, Cache::World world, Cache::ResourceClass resClass, sf::Uint32 time, sf::Uint32 lifeTime, bool AsCopy, const std::string extension, bool forceLoad)
	{
		std::stringstream indexFormer;
		indexFormer << indexer << style << resClass;
		std::string LookupIndex = indexFormer.str();
		auto res = ResourceSet.find(LookupIndex);
		if (res != ResourceSet.end() && !forceLoad)
		{
			auto WantedResource = Resources[LookupIndex];
			if (lifeTime <= 0)
				WantedResource.first = time + ResourceLifeTime;
			else
				WantedResource.first = time + lifeTime;
			if (AsCopy)
			{
				auto ResourceCopy = res_ptr(new sf::Texture(*(WantedResource.second)));
				return ResourceCopy;
			}
			else
				return WantedResource.second;
		}
		else
		{
			std::string path;
			PathCollection* activeCollection;
			switch (style)
			{
			case FFV:
				activeCollection = &FFVPaths;
				break;
			case FFVI:
				activeCollection = &FFVIPaths;
				break;
			default:
				activeCollection = &MainPaths;
				break;
			}
			//build path needs to be added here

			switch (resClass)
			{
			case BackColor:
				path = activeCollection->BackColorsDirectory + indexer + extension;
				break;
			case Background:
				path = activeCollection->Backgrounds + indexer + extension;
				break;
			case BattleBack:
				path = activeCollection->BattleBacks + indexer + extension;
				break;
			case Boss:
				path = activeCollection->BossSubDirectory + indexer + extension;
				break;
			case Chaser:
				path = activeCollection->ChasersSubDirectory + indexer + extension;
				break;
			case DDR:
				path = activeCollection->DDRSpriteDirectory + indexer + extension;
				break;
			case Enemy:
				path = activeCollection->EnemySubDirectory + indexer + extension;
				break;
			case Guardian:
				path = activeCollection->GuardianSubDirectory + indexer + extension;
				break;
			case GUIBattleElement:
				path = activeCollection->GUIBattleSubDirectory + indexer + extension;
				break;
			case GUIMenuElement:
				path = activeCollection->GUIMenuSubDirectory + indexer + extension;
				break;
			case Icon:
				break;
			case MagicIcon:
				break;
			case MagicSheet:
				path = activeCollection->MagicSheetSpriteDirectory + indexer + extension;
				break;
			case OverworldSprite:
				path = activeCollection->OverworldSpriteDirectory + indexer + extension;
				break;
			case Particle:
				path = activeCollection->ParticleDirectory + indexer + extension;
				break;
			case QuadrupleTriad:
				path = activeCollection->QuadrupleTriadDirectory + indexer + extension;
				break;
			case Queue:
				path = activeCollection->QueueSubDirectory + indexer + extension;
				break;
			case SkillSheet:
				break;
			case SummonSprite:
				break;
			case WorldImage:
				path = activeCollection->WorldSubDirectory + indexer + extension;
				break;
			case TitleScreen:
				path = activeCollection->TitleScreenSubDirectory + indexer + extension;
				break;
			case TileSet:
				path = TileSetDirectory + indexer + extension;
				break;
			}

			if (boost::filesystem::exists(path))
			{

				res_ptr newTexture = res_ptr(new sf::Texture());
				Resource NewRes;
				if (lifeTime == 0)
					NewRes.first = time + ResourceLifeTime;
				else
					NewRes.first = time + lifeTime;
				if(newTexture->loadFromFile(path))
				{
					NewRes.second = newTexture;
				}
				else
				{
					NewRes.second = DefaultResource;
				}
				ResourceSet.insert(LookupIndex);
				Resources[LookupIndex] = NewRes;
				return NewRes.second;
			}
			else
			{
				std::cerr << "Could not find resource: " + path << std::endl;
				return DefaultResource;
			}
		}
	}
	void TextureCache::InitializePaths(Configuration::AppConfiguration &configuration)
	{
		using namespace Configuration;
		using namespace Cache;
		std::string SpriteDirectory = configuration.GetApplicationSetting("ResourcesBaseDirectory") + 
			configuration.GetApplicationSetting("GraphicsSubDir") +
			configuration.GetApplicationSetting("SpriteSubDir");
		this->TileSetDirectory = configuration.GetApplicationSetting("ResourcesBaseDirectory") + 
			configuration.GetApplicationSetting("GraphicsSubDir") +
			configuration.GetApplicationSetting("TileSetDir");
		/*switch (CurrentGameStyle)
		{
		case FFTactics:
			break;
		case FFV:
			SpriteDirectory += configuration.GetApplicationSetting("FFVSpriteDir");
			break;
		case FFVI:
			break;
		case Main:
			SpriteDirectory += configuration.GetApplicationSetting("MainGameSpriteDir");
			break;
		}*/

		// +
		//	Appconfiguration.GetApplicationSetting("MainGameSpriteDir")];
		std::string MainSpriteDirectory(SpriteDirectory + configuration.GetApplicationSetting("MainGameSpriteDir"));
		MainPaths.SpriteDirectory = MainSpriteDirectory;
		MainPaths.BossSubDirectory = MainSpriteDirectory + configuration.GetApplicationSetting("BossSubDir");
		MainPaths.ChasersSubDirectory = MainSpriteDirectory + configuration.GetApplicationSetting("ChasersSubDir");
		MainPaths.EnemySubDirectory = MainSpriteDirectory + configuration.GetApplicationSetting("EnemySubDir");
		MainPaths.GuardianSubDirectory = MainSpriteDirectory + configuration.GetApplicationSetting("GuardianSubDir");
		MainPaths.NPCSubDirectory = MainSpriteDirectory + configuration.GetApplicationSetting("NPCSubDir");
		MainPaths.WeaponsSubDirectory = MainSpriteDirectory + configuration.GetApplicationSetting("GuardianSubDir");
		MainPaths.TitleScreenSubDirectory = configuration.GetApplicationSetting("ResourcesBaseDirectory") + configuration.GetApplicationSetting("GraphicsSubDir") + configuration.GetApplicationSetting("TitleScreenSubDir");// + Appconfiguration.GetApplicationSetting()]
		MainPaths.GUISubDirectory = configuration.GetApplicationSetting("ResourcesBaseDirectory") + configuration.GetApplicationSetting("GraphicsSubDir") + configuration.GetApplicationSetting("SpriteSubDir") + configuration.GetApplicationSetting("GUISubDir") + configuration.GetApplicationSetting("MainGameSpriteDir");
		MainPaths.GUIBattleSubDirectory = MainPaths.GUISubDirectory + configuration.GetApplicationSetting("GUIBattleSubDir");
		MainPaths.GUIMenuSubDirectory = MainPaths.GUISubDirectory + configuration.GetApplicationSetting("GUIMenuSubDir");
		MainPaths.QueueSubDirectory = MainPaths.GUIBattleSubDirectory + configuration.GetApplicationSetting("QueueSubDir");
		MainPaths.QuadrupleTriadDirectory = SpriteDirectory + configuration.GetApplicationSetting("QuadrupleTriadDirectory");
		MainPaths.WorldSubDirectory = SpriteDirectory + configuration.GetApplicationSetting("WorldDirectory");
		MainPaths.OverworldSpriteDirectory = SpriteDirectory + configuration.GetApplicationSetting("OverworldSpriteDir");
		MainPaths.BackColorsDirectory = configuration.GetApplicationSetting("ResourcesBaseDirectory") + configuration.GetApplicationSetting("GraphicsSubDir") + configuration.GetApplicationSetting("BackColorsSubDir");
		MainPaths.MagicSheetSpriteDirectory = MainPaths.SpriteDirectory + configuration.GetApplicationSetting("MagicSheetSubDir");
		MainPaths.MagicSheetSpriteDirectory = MainPaths.SpriteDirectory + configuration.GetApplicationSetting("SkillSheetSubDir");
		MainPaths.BattleBacks = MainPaths.SpriteDirectory + configuration.GetApplicationSetting("BattleBacksSubDir");
		MainPaths.Backgrounds = configuration.GetApplicationSetting("ResourcesBaseDirectory") + configuration.GetApplicationSetting("GraphicsSubDir") + configuration.GetApplicationSetting("BackgroundsSubDir");
		MainPaths.MinigameSpriteDirectory = SpriteDirectory + configuration.GetApplicationSetting("MinigameSubDir");
		MainPaths.DDRSpriteDirectory = MainPaths.MinigameSpriteDirectory + configuration.GetApplicationSetting("DDRSubDir");
		MainPaths.ParticleDirectory = MainPaths.SpriteDirectory + configuration.GetApplicationSetting("ParticleSubDir");
		//MainPaths.GUIBattleQueueSubDirectory = 

		std::string FFVSpriteDirectory(SpriteDirectory + configuration.GetApplicationSetting("FFVGameSpriteDir"));
		FFVPaths.SpriteDirectory = FFVSpriteDirectory;
		FFVPaths.BossSubDirectory = FFVSpriteDirectory + configuration.GetApplicationSetting("BossSubDir");
		FFVPaths.ChasersSubDirectory = FFVSpriteDirectory + configuration.GetApplicationSetting("ChasersSubDir");
		FFVPaths.EnemySubDirectory = FFVSpriteDirectory + configuration.GetApplicationSetting("EnemySubDir");
		FFVPaths.GuardianSubDirectory = FFVSpriteDirectory + configuration.GetApplicationSetting("GuardianSubDir");
		FFVPaths.NPCSubDirectory = FFVSpriteDirectory + configuration.GetApplicationSetting("NPCSubDir");
		FFVPaths.WeaponsSubDirectory = FFVSpriteDirectory + configuration.GetApplicationSetting("GuardianSubDir");
		FFVPaths.TitleScreenSubDirectory = configuration.GetApplicationSetting("ResourcesBaseDirectory") + configuration.GetApplicationSetting("GraphicsSubDir") + configuration.GetApplicationSetting("TitleScreenSubDir");// + Appconfiguration.GetApplicationSetting()]
		FFVPaths.GUISubDirectory = configuration.GetApplicationSetting("ResourcesBaseDirectory") + configuration.GetApplicationSetting("GraphicsSubDir") + configuration.GetApplicationSetting("SpriteSubDir") + configuration.GetApplicationSetting("GUISubDir") + configuration.GetApplicationSetting("MainGameSpriteDir");
		FFVPaths.GUIBattleSubDirectory = FFVPaths.GUISubDirectory + configuration.GetApplicationSetting("GUIBattleSubDir");
		FFVPaths.GUIMenuSubDirectory = FFVPaths.GUISubDirectory + configuration.GetApplicationSetting("GUIMenuSubDir");
		FFVPaths.QueueSubDirectory = FFVPaths.GUIBattleSubDirectory + configuration.GetApplicationSetting("QueueSubDir");
		FFVPaths.QuadrupleTriadDirectory = FFVSpriteDirectory + configuration.GetApplicationSetting("QuadrupleTriadDirectory");
		FFVPaths.WorldSubDirectory = FFVSpriteDirectory + configuration.GetApplicationSetting("WorldDirectory");
		FFVPaths.OverworldSpriteDirectory = FFVSpriteDirectory + configuration.GetApplicationSetting("OverworldSpriteDir");
		FFVPaths.MagicSheetSpriteDirectory = FFVPaths.SpriteDirectory + configuration.GetApplicationSetting("MagicSheetSubDir");
		FFVPaths.MagicSheetSpriteDirectory = FFVPaths.SpriteDirectory + configuration.GetApplicationSetting("SkillSheetSubDir");
		FFVPaths.BattleBacks = FFVPaths.SpriteDirectory + configuration.GetApplicationSetting("BattleBacksSubDir");
		FFVPaths.MinigameSpriteDirectory = MainPaths.MinigameSpriteDirectory;
		FFVPaths.DDRSpriteDirectory = MainPaths.DDRSpriteDirectory;
		FFVPaths.ParticleDirectory = MainPaths.ParticleDirectory;

		std::string FFVISpriteDirectory(SpriteDirectory + configuration.GetApplicationSetting("FFVGameSpriteDir"));
		FFVIPaths.SpriteDirectory = FFVISpriteDirectory;
		FFVIPaths.BossSubDirectory = FFVISpriteDirectory + configuration.GetApplicationSetting("BossSubDir");
		FFVIPaths.ChasersSubDirectory = FFVISpriteDirectory + configuration.GetApplicationSetting("ChasersSubDir");
		FFVIPaths.EnemySubDirectory = FFVISpriteDirectory + configuration.GetApplicationSetting("EnemySubDir");
		FFVIPaths.GuardianSubDirectory = FFVISpriteDirectory + configuration.GetApplicationSetting("GuardianSubDir");
		FFVIPaths.NPCSubDirectory = FFVISpriteDirectory + configuration.GetApplicationSetting("NPCSubDir");
		FFVIPaths.WeaponsSubDirectory = FFVISpriteDirectory + configuration.GetApplicationSetting("GuardianSubDir");
		FFVIPaths.TitleScreenSubDirectory = configuration.GetApplicationSetting("ResourcesBaseDirectory") + configuration.GetApplicationSetting("GraphicsSubDir") + configuration.GetApplicationSetting("TitleScreenSubDir");// + Appconfiguration.GetApplicationSetting()]
		FFVIPaths.GUISubDirectory = configuration.GetApplicationSetting("ResourcesBaseDirectory") + configuration.GetApplicationSetting("GraphicsSubDir") + configuration.GetApplicationSetting("SpriteSubDir") + configuration.GetApplicationSetting("GUISubDir") + configuration.GetApplicationSetting("MainGameSpriteDir");
		FFVIPaths.GUIBattleSubDirectory = FFVIPaths.GUISubDirectory + configuration.GetApplicationSetting("GUIBattleSubDir");
		FFVIPaths.GUIMenuSubDirectory = FFVIPaths.GUISubDirectory + configuration.GetApplicationSetting("GUIMenuSubDir");
		FFVIPaths.QueueSubDirectory = FFVIPaths.GUIBattleSubDirectory + configuration.GetApplicationSetting("QueueSubDir");
		FFVIPaths.QuadrupleTriadDirectory = FFVISpriteDirectory + configuration.GetApplicationSetting("QuadrupleTriadDirectory");
		FFVIPaths.WorldSubDirectory = FFVISpriteDirectory + configuration.GetApplicationSetting("WorldDirectory");
		FFVIPaths.OverworldSpriteDirectory = FFVISpriteDirectory + configuration.GetApplicationSetting("OverworldSpriteDir");
		FFVIPaths.MagicSheetSpriteDirectory = MainPaths.SpriteDirectory + configuration.GetApplicationSetting("MagicSheetSubDir");
		FFVIPaths.MagicSheetSpriteDirectory = MainPaths.SpriteDirectory + configuration.GetApplicationSetting("SkillSheetSubDir");
		FFVIPaths.BattleBacks = FFVIPaths.SpriteDirectory + configuration.GetApplicationSetting("BattleBacksSubDir");
		FFVIPaths.MinigameSpriteDirectory = MainPaths.MinigameSpriteDirectory;
		FFVIPaths.DDRSpriteDirectory = MainPaths.DDRSpriteDirectory;
		FFVIPaths.ParticleDirectory = MainPaths.ParticleDirectory;
	}
}