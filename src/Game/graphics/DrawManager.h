#pragma once
#ifndef _DRAWMANAGER_H_
#define _DRAWMANAGER_H_

#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <graphics/DrawInterface.h>
#include <graphics/AnimatedDraw.h>
#include <map>
#include <utility>
namespace Graphics
{
	template <class Drawable>
	class DrawableEntry
	{
	public:
		DrawableEntry() : ShaderSet(false)
		{

		}
		DrawableEntry(boost::shared_ptr<Drawable>& drawEntry, sf::Shader& shader) : ShaderSet(true), AttachedShader(shader)
		{

		}
		DrawableEntry(boost::shared_ptr<Drawable>& drawEntry) : ShaderSet(false)
		{

		}
		DrawableEntry(const Drawable& entry) : DrawEntry(entry), ShaderSet(false)
		{
			
		}
		DrawableEntry(const DrawableEntry& ref) : /*DrawEntry(ref.DrawEntry->Clone()),*/ ShaderSet(false)
		{
			
		}
		DrawableEntry& operator=(const DrawableEntry& ref)
		{
			if (this != &ref)
			{
				this->DrawEntry = ref.DrawEntry;
				this->ShaderSet = false;
			}
			return *this;
		}

		virtual ~DrawableEntry()
		{

		}

		boost::shared_ptr<Drawable> DrawEntry;
		sf::Shader AttachedShader;
		bool ShaderSet;
	};

	typedef std::pair< boost::unordered_map<std::string, DrawableEntry<DrawInterface>>, boost::unordered_map<std::string, DrawableEntry<AnimatedDraw>> > DrawLayerEntry;
	class DrawManager : public AnimatedDraw
	{
	public:
		DrawManager();

		//DrawManager(const DrawManager& ref);

		void Draw(sf::RenderWindow &window);

		void Draw(sf::RenderWindow &window, sf::Shader &shader);
		
		void Update(const sf::Uint32 time, const float TimeScale = 1.f) override;

		void Update(const float time, const float TimeScale = 1.f) override;

		void AddDrawable(const std::string& index, boost::shared_ptr<DrawInterface> drwIntr, int layer = 0);

		void AddAnimatedDrawable(const std::string& index, boost::shared_ptr<AnimatedDraw> animDrw, const int layer = 0);

		bool RemoveDrawable(const int layer, const std::string& index);

		bool RemoveAnimatedDrawable(const int layer, const std::string& index);

		bool RemoveAnyDrawable(const std::string& index);

		bool LoadShader(const std::string& shaderFile, const std::string& index, const int layer = 0, const sf::Shader::Type stype = sf::Shader::Fragment);

		//void SetShader(const sf::Shader& shader, const std::string& index, const int layer = 0);

		bool LoadAnimatedShader(const std::string& shaderFile, const std::string& index, const int layer = 0, const sf::Shader::Type stype = sf::Shader::Fragment);

		//void SetAnimatedShader(const sf::Shader& shader, const std::string& index, const int layer = 0);
	private:
		std::map<int, DrawableEntry<AnimatedDraw> > Drawables;
		// p1;
		//std::map<int, std::pair< boost::unordered_map<std::string, DrawableEntry<DrawInterface>>, boost::unordered_map<std::string, DrawableEntry<AnimatedDraw>> > > Drawables;
		//std::map<int, boost::unordered_map<std::string, DrawableEntry<AnimatedDraw> > > AnimatedDrawables;
	};
}

#endif