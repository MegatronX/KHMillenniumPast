#include "LightingSystem.h"
#include <LTBL/Light/ConvexHull.h>
#include <LTBL/Light/EmissiveLight.h>
#include <LTBL/Light/Light_Point.h>
#include <Engine.h>
namespace Graphics
{
	LightingSystem::LightingSystem()
	{

	}
	LightingSystem::LightingSystem(sf::RenderWindow* window, Engine* engine, const std::string& lightpic, const std::string& shaderFile) :
		PrimaryLightSystem(AABB(Vec2f(0.f, 0.f), Vec2f(static_cast<float>(engine->GetResolution().x), static_cast<float>(engine->GetResolution().y))), window, 
			engine->GetContentManager().GetShaderDirectory() + lightpic, engine->GetContentManager().GetShaderDirectory() + shaderFile)
	{
		PrimaryLightSystem.m_useBloom = true;
		PrimaryLightSystem.m_ambientColor = sf::Color::Black;
	}

	ltbl::LightSystem* LightingSystem::GetPrimaryLightSystem()
	{
		return &PrimaryLightSystem;
	}
	ltbl::LightSystem* LightingSystem::GetSeconadryLightSystem(const std::string& index)
	{
		auto sys = SecondaryLightSystems.find(index);
		if (sys != SecondaryLightSystems.end())
		{
			return (sys->second).get();
		}
#ifdef _DEBUG
		std::cerr << "Could not find secondary system " << index << ", returning primary system\n";
#endif
		return GetPrimaryLightSystem();
	}

	void LightingSystem::AddLightToPrimary(ltbl::Light* light)
	{
		PrimaryLightSystem.AddLight(light);
	}
	void LightingSystem::AddLightPointToPrimary(const float intensity, const Vec2f& center, const float radius, const float size, const float angle, float spreadAngle, float bleed, float linearlizeFactor, bool alwaysUpdate)
	{
		auto lp = new ltbl::Light_Point();
		lp->m_intensity = intensity;
		lp->m_center = center;
		lp->m_radius = radius;
		lp->m_size = size;
		lp->m_spreadAngle = angle;
		lp->m_softSpreadAngle = spreadAngle;
		lp->CalculateAABB();
		lp->m_bleed = bleed;
		lp->m_linearizeFactor = linearlizeFactor;
		
		PrimaryLightSystem.AddLight(lp);
		
		lp->SetAlwaysUpdate(alwaysUpdate);
	}

	void LightingSystem::AddConvexHullToPrimary(ltbl::ConvexHull* hull, bool renderLightOver)
	{
		hull->CalculateNormals();
		hull->CalculateAABB();
		hull->m_renderLightOverHull = renderLightOver;
		PrimaryLightSystem.AddConvexHull(hull);
	}

	void LightingSystem::AddConvexHullToPrimary(const std::string& file, bool renderLightOver, const Vec2f& center)
	{
		auto hull = new ltbl::ConvexHull();
		if (!hull->LoadShape(file.c_str()))
		{
			delete hull;
		}
		else
		{
			hull->SetWorldCenter(center);
			AddConvexHullToPrimary(hull, renderLightOver);
		}
	}
	void LightingSystem::AddConvexHullToPrimary(const std::vector<Vec2f>& ccwpoints, bool renderLightOver, const Vec2f& center)
	{
		auto hull = new ltbl::ConvexHull();
		hull->m_vertices = ccwpoints;
		hull->SetWorldCenter(center);
		AddConvexHullToPrimary(hull, renderLightOver);
	}
	void LightingSystem::Draw(sf::RenderTarget &window, sf::RenderStates states)
	{
		PrimaryLightSystem.RenderLights();
		PrimaryLightSystem.RenderLightTexture();
	}
	void LightingSystem::Draw(sf::RenderTarget &window)
	{
		PrimaryLightSystem.RenderLights();
		PrimaryLightSystem.RenderLightTexture();
	}

	void LightingSystem::Update(const sf::Uint32 time, const float TimeScale)
	{

	}
}