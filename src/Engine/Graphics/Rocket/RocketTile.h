#pragma once
#ifndef _ROCKETTILE_H_
#define _ROCKETTILE_H_

#include <graphics/HTMLInterface/libRocket/LibRocketRenderInterace.h>
#include <graphics/HTMLInterface/libRocket/RocketSystemInterface.h>
#include <graphics/AnimatedDraw.h>
#include <Rocket/Core.h>
namespace Graphics
{
	namespace RocketInterface
	{
		class RocketTile : public AnimatedDraw
		{
		public:
			RocketTile(sf::RenderWindow& window, const std::string& htmlFile, const std::string& tileName);
			virtual void Draw(sf::RenderWindow &window) override;
			virtual void Draw(sf::RenderWindow &window, sf::Shader &shader) override;
			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0f) override;
			virtual void Update(const float time, const float TimeScale = 1.0f) override;
			virtual void SetPage(const std::string& htmlFile);
			virtual void Reload();
			virtual ~RocketTile();
		protected:
			Rocket::Core::Context* RenderingContext;
			Rocket::Core::ElementDocument* PrimaryDoc;
			std::vector<Rocket::Core::ElementDocument*> Docs;

			std::string HtmlFile;
		private:
			
		};
	}
}
#endif