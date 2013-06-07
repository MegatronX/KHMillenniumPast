#pragma once
#ifndef _CONTENTMANAGER_H_
#define _CONTENTMANAGER_H_
#include <caching/Cache.h>
#include <caching/TextureCache.h>
#include <caching/FontCache.h>
#include <boost\shared_ptr.hpp>
#include <sfml\Graphics.hpp>
#include <sfml\Audio.hpp>
#include <sfml\System.hpp>
#include <boost\filesystem.hpp>
#include <boost/unordered_map.hpp>
#include <boost/noncopyable.hpp>
#include <configuration\AppConfiguration.h>
#include <Graphics/Sprites/SpriteImportData.h>
//#include <contentmanagement\VariantParameter.h>
class Engine;
namespace Content
{
	enum ResourceType
	{
		ImageResource,
		AudioResource,
		ScriptResource
	};
	struct SpriteLoadDescription
	{
		SpriteLoadDescription() //: StartingScale(1.0, 1.0), StartingFPS(0), FlipX(false), PosOffset(0, 0), FrameCount(0), DefRow(Graphics::Unavailable), Orientation(Graphics::SpriteOrientation::SprRight)
		{
		}
		//std::vector<Graphics::SpriteRow> RowDescriptions;
		float StartingFPS;
		sf::Vector2f StartingScale;
		sf::Vector2f PosOffset;
		bool FlipX;
		int FrameCount;
		//Graphics::RowClass DefRow;
		//Graphics::SpriteOrientation Orientation;
	};

	struct AttackSpriteLoadDescription : public SpriteLoadDescription
	{
		AttackSpriteLoadDescription() : SpriteLoadDescription()
		{

		}
		bool HasAlphaFadeIn;
		//VariantVariable<sf::Uint8> InAlphaVals;
		sf::Uint32 alphaInTime;

		bool HasAlphaFadeOut;
		//VariantVariable<sf::Uint8> OutAlphaVals;
		sf::Uint32 alphaOutTime;

		bool Transitions;
		//VariantVariable<sf::Vector2f> PositionVals; 

		bool HasVariableFPS;
		//VariantParameter<float, float> FPSVariant;
	};

	class ContentManager : private boost::noncopyable
	{
	public:
		friend class Engine;
		ContentManager(sf::Uint32 StartTime = 0, sf::Uint32 UpdateRate = 6000, sf::Uint32 ImageLifeTime = 600000, sf::Uint32 FontLifeTime = 600000, sf::Uint32 AudioLifeTime = 600000);
		void UpdateCaches(sf::Uint32 time);
		//boost::shared_ptr<sf::Image> RequestImage(const std::string &name, Cache::GameStyle style, Cache::World world, Cache::ResourceClass rClass, sf::Uint32 time, std::string extension = ".png");
		boost::shared_ptr<sf::Texture> RequestTexture(const std::string &name, Cache::GameStyle style, Cache::World world, Cache::ResourceClass rClass, sf::Uint32 time, std::string extension = ".png", bool forceLoad = false);
		//boost::shared_ptr<sf::Image> RequestImageDirectly(std::string &filename);
		boost::shared_ptr<sf::Texture> RequestTextureDirectly(std::string &filename);
		boost::shared_ptr<sf::Font> RequestFont(const std::string &fontFile, sf::Uint32 time, const std::string extension = ".ttf");
		//boost::shared_ptr<Graphics::BaseSprite> RequestSprite_(const std::string &name, Cache::GameStyle style, Cache::World world, Cache::ResourceClass rClass, sf::Uint32 time, bool Start = false, std::string extension = ".png");
		//Graphics::animsprite_ptr RequestSprite(const std::string &name, const Cache::GameStyle style, const Cache::World world, const Cache::ResourceClass rClass, const sf::Uint32 time, const bool Start = false, const std::string extension = ".png");
		//Graphics::animsprite_ptr;
		const std::string& GetMapDirectory() const;
		const std::string& GetShaderDirectory() const;
		const std::string& GetHTMLDirectory() const;
		const std::string& GetResourcesDirectory() const;
		const std::string& GetFontDirectory() const;

		SpriteLoadDescription RequestSpriteLoadout(const std::string& index, Cache::GameStyle style, bool &valid);

		const ::Graphics::SpriteImportData& RequestSpriteImportData(const std::string& index, const Cache::GameStyle style, bool& valid);

		bool VerifyResourceExistance(const std::string& filepath);

		void LoadSpriteDescriptors(const std::string& file);

		virtual ~ContentManager();
		//boost::shared_ptr<sf::Music> RequestMusic(const std::string &fileName);
		//boost::shared_ptr<sf::Music> RequestMusicDirectly(const std::string &fileName);
		//boost::shared_ptr<sf::Sound> RequestSound(const std::string &fileName);
	protected:
		//boost::unordered_map<std::string, SpriteLoadDescription > StoredSpriteRows;
		boost::unordered_map<Cache::GameStyle, boost::unordered_map<std::string, SpriteLoadDescription> > StoredSpriteRows;
		boost::unordered_map<Cache::GameStyle, boost::unordered_map<std::string, ::Graphics::SpriteImportData> > AnimatedSpriteData;
		friend class ResourceLoadImport;
	private:
		//Cache::ImageCache PrimaryImageCache;
		//Cache::ImageCache SecondaryImageCache;
		Cache::TextureCache PrimaryTextureCache;
		Cache::FontCache PrimaryFontCache;
		//Cache::AudioCache PrimaryAudioCache;
		std::string MapDirectory;
		std::string ShaderDirectory;
		std::string HTMLDirectory;
		std::string ResourcesDirectory;
		sf::Thread UpdaterThread;
		sf::Mutex UpdateLock;
		sf::Uint32 RunningTime;
		sf::Time UpdateRate;
		void ThreadUpdater();
		void Initialize(Configuration::AppConfiguration &configuration);
		//Cache::SoundCache PrimarySoundCache;
	};
}
#endif
