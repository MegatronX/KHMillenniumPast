/*	Kingdom Hearts MP main.cpp
*	Responsible for creating and launching the game instance
*
*
*
*/

//C++ standard headers
#include <string>
#include <iostream>
//sfml headers
#include <sfml/Graphics.hpp>
#include <sfml/System.hpp>
//boost headers
#include <boost/python.hpp>
//game headers
#include <Engine.h>
#include <GameInstance.h>
#include <graphics/Screens/GameMapViewScreen.h>
//Lighting
#include <LTBL/Light/LightSystem.h>
#include <LTBL/Light/Light_Point.h>
#include <LTBL/Utils.h>

sf::Texture text;
Engine* ActiveEngine;
ltbl::Light_Point* testLight;
void LightingTest(Graphics::LightingSystem& lsystem)
{
	testLight = new ltbl::Light_Point();
	testLight->m_intensity = 2.0f;
	testLight->m_center = Vec2f(200.0f, 200.0f);
	testLight->m_radius = 600.0f;
	testLight->m_size = 15.0f;
	testLight->m_spreadAngle = ltbl::pifTimes2;
	testLight->m_softSpreadAngle = 0.0f;
	testLight->CalculateAABB();

	testLight->m_bleed = 0.4f;
	testLight->m_linearizeFactor = 0.2f;
	lsystem.GetPrimaryLightSystem()->AddLight(testLight);


	ltbl::EmissiveLight* emissiveLight = new ltbl::EmissiveLight();

	

	if(!text.loadFromFile(ActiveEngine->GetContentManager().GetResourcesDirectory() + "graphics/lighting/emissive.png"))
		abort();

	emissiveLight->SetTexture(&text);

	emissiveLight->SetRotation(45.0f);

	emissiveLight->m_intensity = 1.3f;

	lsystem.GetPrimaryLightSystem()->AddEmissiveLight(emissiveLight);

	emissiveLight->SetCenter(Vec2f(500.0f, 500.0f));
}
void PreloadSounds(Engine* eng)
{
	eng->GetSoundSystem().AddSound("SelectionCancel", "SelectionCancel", true, true, true, ".wav");
	eng->GetSoundSystem().AddSound("SelectionChange", "SelectionChange", true, true, true, ".wav");
	eng->GetSoundSystem().AddSound("SelectionConfirm", "SelectionConfirm", true, true, true, ".wav");
	eng->GetSoundSystem().AddSound("SelectionFailed", "SelectionFailed", true, true, true, ".wav");
	eng->GetSoundSystem().AddSound("SelectionInvalid", "SelectionInvalid", true, true, true, ".wav");
		/*
		Engine.GetSoundSystem().AddSound("SelectionCancel", "SelectionCancel", True, True, True, ".wav")
		Engine.GetSoundSystem().AddSound("SelectionChange", "SelectionChange", True, True, True, ".wav")
		Engine.GetSoundSystem().AddSound("SelectionConfirm", "SelectionConfirm", True, True, True, ".wav")
		Engine.GetSoundSystem().AddSound("SelectionFailed", "SelectionFailed", True, True, True, ".wav")
		Engine.GetSoundSystem().AddSound("SelectionInvalid", "SelectionInvalid", True, True, True, ".wav")
		*/
}
int main()
{
	try
	{
		sf::Vector2i Res(800, 600);
		sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
		GameWindow.setFramerateLimit(100);

		Engine GameEngine("Config.xml", &GameWindow, Res);
		Game::GameInstance GameInst(GameEngine, false);
		ActiveEngine = &GameEngine;
		GameInst.LoadSave("../../../resources/saves/sav1.xml", "Save0");

		GameEngine.LaunchPythonCommandLineThread();
		PreloadSounds(&GameEngine);
		auto lyptr = boost::shared_ptr<Game::Graphics::Screens::GameMapViewScreen>(new Game::Graphics::Screens::GameMapViewScreen(&GameEngine, std::string("Traverse Point - Far Left.tmx"), sf::Vector2f(20 * 32, 13* 32), 5, &GameWindow, std::string("Station"), GameInst.GetPlayerParty().GetPartyMembersInOrder()[0]->GetName(), GameEngine.GetUID()));
		GameEngine.GetScreenManager().AddScreen(lyptr, 0);
		sf::Uint32 time = GameEngine.GetTime();
		auto& ls = GameEngine.GetLightingSystem();
		//LightingTest(ls);
		sf::Vector2i prevMousePos = sf::Mouse::getPosition(GameWindow);
		sf::Vector2i mousePos = prevMousePos;
		for(bool Running = true; Running; time = GameEngine.GetTime())
		{
			GameEngine.HandleWindowEvents(GameWindow, Running);
			//Update
			mousePos = sf::Mouse::getPosition(GameWindow);
			if (mousePos != prevMousePos)
			{
				prevMousePos = mousePos;
				//std::cout << "mousepos: " << mousePos.x << ", " << mousePos.y << "\n";
				//testLight->SetCenter(Vec2f(static_cast<float>(mousePos.x), static_cast<float>(Res.y) - static_cast<float>(mousePos.y)));
			}
			GameEngine.Update(time);
			//Clear
			GameWindow.clear();
			//Draw
			GameEngine.Draw(GameWindow);
			//Display
			GameWindow.display();

		}
	}
	catch (boost::python::error_already_set)
	{
		PyErr_Print();
		std::string exp = "";
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << "\n";
	}
	

	return EXIT_SUCCESS;
}