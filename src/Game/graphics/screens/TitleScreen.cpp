#include "TitleScreen.h"
#include <Engine.h>
#include <Graphics/Rocket/ElementTransformer.h>
#include <Graphics/Rocket/FaderTransform.h>
#include <Graphics/Rocket/PositionTransformer.h>
using namespace Graphics::GameRocket;
namespace Game
{
	namespace Graphics
	{
		namespace Screens
		{
			TitleScreen::TitleScreen(Engine* engine) : GameRocket::BasicRMLScreen("Title Screen", "Titlescreen.rml", engine, engine->GetUID())
			{
				engine->GetSoundSystem().AddSound("Dearly Beloved", "Dearly Beloved");
				engine->GetSoundSystem().Play("Dearly Beloved");
				MakeAnimationSequence();
			}
			bool TitleScreen::HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& action)
			{
				return false;
			}
			bool TitleScreen::HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& action)
			{
				return false;
			}
			void TitleScreen::HandleGameReadyEvent()
			{
				ready = true;
			}
			void InspiredByFader(sf::Uint32 time, ElementTransformationInterface* intr)
			{
				
			}
			void TitleScreen::MakeAnimationSequence()
			{
				auto scripter = engine->GetPythonScripter();
				scripter.AddScriptObject<TitleScreen>("TitleScreen", *this, scripter.GetModule("GameScreensModule"));
				scripter.RunFile("TitleScreen.py");
				int x = 10;
				/*sf::Uint32 CumulativeTime = 0;
				auto doc = GetDocument();
				FaderTransform* LogoFadeIn = new FaderTransform(nullptr, 0, 255, engine->GetTime(), engine->GetTime() + 2200);
				FaderTransform* LogoFadeOut = new FaderTransform(nullptr, 255, 0, engine->GetTime(), engine->GetTime() + 1200);
				LogoFadeIn->AddPostTransform(boost::shared_ptr<ElementTransformationInterface>(LogoFadeOut), 1200);
				

				auto elemettransformer = new ElementTransformer(doc->GetElementById("Logo"));
				elemettransformer->AddTransformation(boost::shared_ptr<ElementTransformationInterface>(LogoFadeIn));
				this->AddNewTransform("LogoFade", elemettransformer);
				
				LogoFadeIn->ReInitialize(engine->GetTime(), engine->GetTime() + 2200, elemettransformer);

				CumulativeTime += 2200 + 1200;

				FaderTransform* InspFadeIn = new FaderTransform(nullptr, 0, 255, engine->GetTime(), engine->GetTime() + 1200);
				FaderTransform* InspFadeOut = new FaderTransform(nullptr, 255, 0, engine->GetTime(), engine->GetTime() + 1200);
				InspFadeIn->AddPostTransform(boost::shared_ptr<ElementTransformationInterface>(InspFadeOut), 1200);


				auto elemettransformer2 = new ElementTransformer(doc->GetElementById("InspiredBy"));
				elemettransformer2->AddTransformation(boost::shared_ptr<ElementTransformationInterface>(InspFadeIn));
				this->AddNewTransform("InspFade", elemettransformer2, CumulativeTime);

				InspFadeIn->ReInitialize(engine->GetTime() + CumulativeTime, engine->GetTime() + CumulativeTime + 2200, elemettransformer);*/
			}
		}
	}
}