#include "RocketTile.h"
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <graphics/OpenGLHelpers.h>
using namespace Rocket::Core;
namespace Graphics
{
	namespace RocketInterface
	{
		
		RocketTile::RocketTile(sf::RenderWindow& window, const std::string& htmlFile, const std::string& tileName) :
			RenderingContext(Rocket::Core::CreateContext(tileName.c_str(), Rocket::Core::Vector2i(window.GetWidth(), window.GetHeight()))), HtmlFile(htmlFile)
		{
			PrimaryDoc = RenderingContext->LoadDocument(htmlFile.c_str());
			//RenderingContext->
			if (PrimaryDoc != nullptr)
			{
				PrimaryDoc->Show();
				//PrimaryDoc->RemoveRe
			}
		}
		void RocketTile::Draw(sf::RenderWindow &window)
		{
			PushOpenGLStates(window);
			RenderingContext->Render();
			PopOpenGLStates(window);
		}
		void RocketTile::Draw(sf::RenderWindow &window, sf::Shader &shader)
		{
			RenderingContext->Render();
		}
		void RocketTile::Update(const sf::Uint32 time, const float TimeScale)
		{
			RenderingContext->Update();
		}
		void RocketTile::Update(const float time, const float TimeScale)
		{
			RenderingContext->Update();
		}
		void RocketTile::SetPage(const std::string& htmlFile)
		{
			HtmlFile = htmlFile;
			if(PrimaryDoc != nullptr)
				PrimaryDoc->Close();
			PrimaryDoc = RenderingContext->LoadDocument(htmlFile.c_str());
			if (PrimaryDoc != nullptr)
			{
				PrimaryDoc->Show();
				//PrimaryDoc->RemoveRe
			}
		}
		void RocketTile::Reload()
		{
			PrimaryDoc->Close();
			PrimaryDoc = RenderingContext->LoadDocument(HtmlFile.c_str());
			if (PrimaryDoc != nullptr)
			{
				PrimaryDoc->Show();
				//PrimaryDoc->RemoveRe
			}
		}
		RocketTile::~RocketTile()
		{
			for (auto doc = Docs.begin(); doc != Docs.end(); ++doc)
			{
				
				//(*doc)->
			}
			//PrimaryDoc->Cle
		}
	}
}