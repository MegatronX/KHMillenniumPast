#include "ContentManager.h"
#include <contentmanagement/ResourceLoadImport.h>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
namespace Content
{

	ContentManager::ContentManager(sf::Uint32 StartTime, sf::Uint32 ResolutionTime, sf::Uint32 ImageLifeTime, sf::Uint32 FontLifeTime, sf::Uint32 AudioLifeTime) 
		: RunningTime(StartTime), PrimaryFontCache(200, FontLifeTime, 5), UpdateRate(sf::milliseconds(ResolutionTime)), UpdaterThread(boost::bind(&ContentManager::ThreadUpdater, this)) //: PrimaryImageCache(200, ImageLifeTime, 5)
	{
		UpdaterThread.launch();
		//boost::shared_ptr<sf::Image> unknown = boost::shared_ptr<sf::Image>(new sf::Image);
		//unknown->LoadFromFile("Unknown.png");

		boost::shared_ptr<sf::Texture> unknowntex = boost::shared_ptr<sf::Texture>(new sf::Texture);
		unknowntex->loadFromFile("Unknown.png");
		//boost::shared_ptr<sf::Music> music = boost::shared_ptr<sf::Music>(new sf::Music);
		//music->OpenFromFile(std::string("FleetingDream.ogg"));
		//boost::shared_ptr<sf::Sound> sound = boost::shared_ptr<sf::Sound>(new sf::Sound);
		
		//this->PrimaryImageCache = Cache::ImageCache(200, ImageLifeTime, 5, unknown);
		this->PrimaryTextureCache = Cache::TextureCache(200, ImageLifeTime, 5, unknowntex);
		//this->PrimaryAudioCache = Cache::AudioCache(50, AudioLifeTime, 5, music);
		PrimaryFontCache.DefaultResource = PrimaryFontCache.RequestResource("calibri", StartTime);
	}
	void ContentManager::UpdateCaches(sf::Uint32 time)
	{
		PrimaryTextureCache.Update(time);
	}
	/*boost::shared_ptr<sf::Image> ContentManager::RequestImage(const std::string &name, Cache::GameStyle style, Cache::World world, Cache::ResourceClass rClass, sf::Uint32 time, const std::string extension)
	{
		return PrimaryImageCache.RequestResource(name, style, world, rClass, time, -1, true, extension);
	}*/
	boost::shared_ptr<sf::Texture> ContentManager::RequestTexture(const std::string &name, Cache::GameStyle style, Cache::World world, Cache::ResourceClass rClass, sf::Uint32 time, std::string extension, bool forceLoad)
	{
		UpdateLock.lock();
		return PrimaryTextureCache.RequestResource(name, style, world, rClass, time, -1, true, extension, forceLoad);
		UpdateLock.unlock();
	}
	/*boost::shared_ptr<sf::Image> ContentManager::RequestImageDirectly(std::string &filename)
	{
		if (boost::filesystem::exists(filename))
		{
			auto retImage = Cache::ImageCache::res_ptr(new sf::Image);
			if (retImage->LoadFromFile(filename))
				return retImage;
		}
		return PrimaryImageCache.GetFallBack();
	}*/
	boost::shared_ptr<sf::Texture> ContentManager::RequestTextureDirectly(std::string &filename)
	{
		if (boost::filesystem::exists(filename))
		{
			auto retImage = Cache::TextureCache::res_ptr(new sf::Texture);
			if (retImage->loadFromFile(filename))
				return retImage;
		}
		return PrimaryTextureCache.GetFallBack();
	}
	boost::shared_ptr<sf::Font> ContentManager::RequestFont(const std::string &fontFile, sf::Uint32 time, const std::string extension)
	{
		UpdateLock.lock();
		return PrimaryFontCache.RequestResource(fontFile, time, extension);
		UpdateLock.unlock();
	
	}
/*	Graphics::animsprite_ptr ContentManager::RequestSprite(const std::string &name, const Cache::GameStyle style, const Cache::World world, const Cache::ResourceClass rClass, const sf::Uint32 time, const bool Start, const std::string extension)
	{
		auto img = PrimaryTextureCache.RequestResource(name, style, world, rClass, time, -1, true, extension);
		
		Graphics::animsprite_ptr sprite;//(new Graphics::AnimatedSprite(img));
		auto sprRows = StoredSpriteRows[style].find(name);
		if (sprRows != StoredSpriteRows[style].end() || ((sprRows = StoredSpriteRows[Cache::GameStyle::Main].find(name)) != StoredSpriteRows[Cache::GameStyle::Main].end()))
		{
			SpriteLoadDescription& desc = sprRows->second;
			if (desc.RowDescriptions.size() > 0)
				sprite = Graphics::animsprite_ptr(new Graphics::AnimatedSprite(img, desc.RowDescriptions, desc.StartingFPS, Start, Graphics::AnimType::EndlessLoop, desc.FrameCount, desc.Orientation));
			else
				sprite = Graphics::animsprite_ptr(new Graphics::AnimatedSprite(img));
			sprite->SetDefaultRow(desc.DefRow);
			sprite->SetScale(desc.StartingScale);
			if (desc.FlipX)
				sprite->FlipX(true);
			sprite->Play(desc.DefRow);
			sprite->SetPosition(desc.PosOffset);
			sprite->SetDefaultSpriteOrientation(desc.Orientation);
		}
		else
		{
			sprite = Graphics::animsprite_ptr(new Graphics::AnimatedSprite(img));
		}
		return sprite;
	}*/
	SpriteLoadDescription ContentManager::RequestSpriteLoadout(const std::string& index, Cache::GameStyle style, bool &valid)
	{
		auto sprRows = StoredSpriteRows[style].find(index);
		if (sprRows != StoredSpriteRows[style].end())
		{
			valid = true;
			return sprRows->second;
		}
		valid = false;
		return SpriteLoadDescription();
	
	}

	::Graphics::SpriteImportData impData;

	const ::Graphics::SpriteImportData& ContentManager::RequestSpriteImportData(const std::string& index, const Cache::GameStyle style, bool& valid)
	{
		valid = false;
		auto styleInfo = AnimatedSpriteData.find(style);
		if (styleInfo != AnimatedSpriteData.end())
		{
			auto sprRows = styleInfo->second.find(index);
			if (sprRows != styleInfo->second.end())
			{
				valid = true;
				return sprRows->second;
			}
		}
		return impData;
	}

	const std::string& ContentManager::GetMapDirectory() const
	{
		return MapDirectory;
	}
	const std::string& ContentManager::GetShaderDirectory() const
	{
		return ShaderDirectory;
	}
	const std::string& ContentManager::GetHTMLDirectory() const
	{
		return HTMLDirectory;
	}
	const std::string& ContentManager::GetResourcesDirectory() const
	{
		return ResourcesDirectory;
	
	}
	const std::string& ContentManager::GetFontDirectory() const
	{
		return this->PrimaryFontCache.GetFontDirectory();
	}

	bool ContentManager::VerifyResourceExistance(const std::string& filepath)
	{
		return boost::filesystem::exists(filepath);
	}

	void ContentManager::LoadSpriteDescriptors(const std::string& file)
	{
		using namespace std;
		using namespace pugi;
		xml_document doc;
		xml_parse_result result = doc.load_file(file.c_str());
		if (!result)
			std::cerr << "Descriptions Failed To Load. Error: " << result.description();
		else
		{
			xml_node root = doc.child("Resources");
			xml_node sprroot = root.child("Sprites");
			for (auto sprNode = sprroot.child("Sprite"); sprroot; sprroot = sprroot.next_sibling("Sprite"))
			{
				xml_node rows = sprNode.child("Rows");
				for (auto row = rows.child("Row"); row; row = row.next_sibling("Row"))
				{
					int frameCount = row.attribute("framecount").as_int();
					std::string index(row.attribute("index").value());
					for (auto frame = row.child("Frame"); frame; frame = frame.next_sibling("Frame"))
					{

					}
				}
			}
		}
	}


	ContentManager::~ContentManager()
	{
		UpdaterThread.terminate();
	}
	void ContentManager::ThreadUpdater()
	{
		RunningTime += UpdateRate.asMilliseconds();
		UpdateLock.lock();
		UpdateCaches(RunningTime);
		UpdateLock.unlock();
		sf::sleep(UpdateRate);
	}
	void ContentManager::Initialize(Configuration::AppConfiguration &configuration)
	{
		PrimaryTextureCache.InitializePaths(configuration);
		PrimaryFontCache.InitializePaths(configuration);
		ResourcesDirectory = configuration.GetApplicationSetting("ResourcesBaseDirectory");
		MapDirectory = ResourcesDirectory + configuration.GetApplicationSetting("MapSubDir");
	    ShaderDirectory = ResourcesDirectory + configuration.GetApplicationSetting("ShaderSubDir");
		HTMLDirectory = configuration.GetApplicationSetting("HTMLDirectory");
		ResourceLoadImport::ProcessImports(ResourcesDirectory + std::string("LoadDescriptions.xml"), *this);
	}
	/*boost::shared_ptr<sf::Sound> ContentManager::RequestSound(const std::string &fileName)
	{
		return Cache::SoundCache::res_ptr();
	}*/
}