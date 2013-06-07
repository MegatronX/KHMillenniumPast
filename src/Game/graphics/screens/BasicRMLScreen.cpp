#include "BasicRMLScreen.h"
#include <Engine.h>
namespace Game
{
	namespace Graphics
	{
		namespace GameRocket
		{
			//sf::Text test("Test");
			BasicRMLScreen::BasicRMLScreen(const std::string& name, const std::string& rmlDoc, Engine* engine, int id) : Screens::GameScreen(name, engine, id)
			{
				pageContext = Rocket::Core::CreateContext(Rocket::Core::String(name.c_str()), Rocket::Core::Vector2i(engine->GetResolution().x, engine->GetResolution().y));
				Doc = pageContext->LoadDocument(Rocket::Core::String(rmlDoc.c_str()));
				if (Doc != nullptr)
					Doc->Show();
			}
			BasicRMLScreen::BasicRMLScreen(const std::string& name, const std::string& rmlDoc, Engine& engine, int id) : Screens::GameScreen(name, &engine, id)
			{
				pageContext = Rocket::Core::CreateContext(Rocket::Core::String(name.c_str()), Rocket::Core::Vector2i(engine.GetResolution().x, engine.GetResolution().y));
				Doc = pageContext->LoadDocument(Rocket::Core::String(rmlDoc.c_str()));
				if (Doc != nullptr)
					Doc->Show();
			}
			BasicRMLScreen::~BasicRMLScreen()
			{
				if (Doc != nullptr)
					Doc->GetContext()->UnloadDocument((Doc));
				pageContext->RemoveReference();
				
			}

			void BasicRMLScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
			{
				GameScreen::draw(target, states);
			}
			void BasicRMLScreen::Draw(sf::RenderTarget &window, sf::RenderStates states)
			{
				GameScreen::Draw(window, states);
				pageContext->Render();
			}
			void BasicRMLScreen::Draw(sf::RenderTarget &window)
			{
				GameScreen::Draw(window);
				pageContext->Render();
				
			}
			void BasicRMLScreen::Update(const sf::Uint32 time, const float TimeScale)
			{
				GameScreen::Update(time, TimeScale);
				pageContext->Update();
				for (auto trans = ActiveTransforms.begin(); trans != ActiveTransforms.end(); ++trans)
				{
					if (time > trans->second.second)
						trans->second.first->Update(time);
				}
			}
			/*void BasicRMLScreen::Update(const float time, const float TimeScale)
			{
				pageContext->Update();
			}*/
			bool BasicRMLScreen::HandleKeyPressed(const sf::Uint32 time, const Input::InputModule* inputModule, ::Input::InputActionResult& action)
			{
				return false;
			}
			bool BasicRMLScreen::HandleKeyReleased(const sf::Uint32 time, const Input::InputModule* inputModule, ::Input::InputActionResult& action)
			{
				return false;
			}
			Rocket::Core::Context*  BasicRMLScreen::GetPageContext() const
			{
				return pageContext;
			}
			Rocket::Core::ElementDocument*  BasicRMLScreen::GetDocument() const
			{
				return Doc;
			}
			void BasicRMLScreen::AddNewTransform(const std::string& name, std::vector<::Graphics::GameRocket::ElementTransformationInterface*>& transforms, sf::Uint32 delay)
			{
				ActiveTransforms[name] = TransformPair(boost::shared_ptr<::Graphics::GameRocket::ElementTransformer>(new ::Graphics::GameRocket::ElementTransformer(transforms)), engine->GetTime() + delay);
			}
			void BasicRMLScreen::AddNewTransform(const std::string& name, ::Graphics::GameRocket::ElementTransformer* transformer, sf::Uint32 delay)
			{
				ActiveTransforms[name] = TransformPair(boost::shared_ptr<::Graphics::GameRocket::ElementTransformer>(transformer), engine->GetTime() + delay);
			}
			void BasicRMLScreen::AddNewTransform(const std::string& name, boost::shared_ptr<::Graphics::GameRocket::ElementTransformer>& transformer, sf::Uint32 delay)
			{
				ActiveTransforms[name] = TransformPair(transformer, engine->GetTime() + delay);
			}
			bool BasicRMLScreen::RemoveTransform(const std::string& name)
			{
				bool Removed = false;
				auto finder = ActiveTransforms.find(name);
				if (finder != ActiveTransforms.end())
				{
					Removed = true;
					ActiveTransforms.erase(finder);
				}
				return Removed;
			}
			void BasicRMLScreen::ClearTransforms()
			{
				ActiveTransforms.clear();
			}
		}
	}
}