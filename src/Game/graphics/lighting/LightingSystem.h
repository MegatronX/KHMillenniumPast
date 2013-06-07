#pragma once
#ifndef _LIGHTINGSYSTEM_H_
#define _LIGHTINGSYSTEM_H_

#include <Graphics/AnimatedDraw.h>
#include <LTBL/Light/LightSystem.h>
#include <LTBL/Light/Light.h>
#include <LTBL/Utils.h>
#include <boost/unordered_map.hpp>
class Engine;
namespace Graphics
{
	class LightingSystem : public AnimatedDraw
	{
	public:
		LightingSystem();
		LightingSystem(sf::RenderWindow* Win, Engine* engine);
		LightingSystem(sf::RenderWindow* Win, Engine* engine, const std::string& lightpic, const std::string& shaderFile);
		ltbl::LightSystem* GetPrimaryLightSystem();
		ltbl::LightSystem* GetSeconadryLightSystem(const std::string& index);

		void AddLightToPrimary(ltbl::Light* light);
		void AddLightPointToPrimary(const float intensity = 2.f, const Vec2f& center = Vec2f(400, 300), const float radius = 300.f, const float size = 15.f, const float angle = ltbl::pifTimes2, float spreadAngle = 0.f, float bleed = 0.4f, float linearlizeFactor = 0.2f, bool alwaysUpdate = true);
		
		void AddConvexHullToPrimary(ltbl::ConvexHull* hull, bool renderLightOver = true);
		void AddConvexHullToPrimary(const std::string& file, bool renderLightOver = true, const Vec2f& center = Vec2f(400.f, 300.f));
		void AddConvexHullToPrimary(const std::vector<Vec2f>& ccwpoints, bool renderLightOver = true, const Vec2f& center = Vec2f(400.f, 300.f));
		virtual void Draw(sf::RenderTarget &window, sf::RenderStates states);
		virtual void Draw(sf::RenderTarget &window);

		virtual void Update(const sf::Uint32 time, const float TimeScale = 1.f);
	protected:
		sf::View* PrimaryView;
		ltbl::LightSystem PrimaryLightSystem;
		boost::unordered_map<std::string, boost::shared_ptr<ltbl::LightSystem> > SecondaryLightSystems;

		friend class Engine;
	};
}

#endif