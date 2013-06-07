#include "Engine.h"
#include <LTBL/Light/LightSystem.h>


Engine::Engine() : IDIncrementer(0), Ready(false), baseRocketInterface(Rocket::Core::String("rml")), Running(true), CommandThread(&Engine::PythonCommandLineIssuer, this), CommandThreadLaunched(false)
{
	srand(time(0));
	rng.seed(time(0));
}
Engine::Engine(const std::string& configFile, sf::RenderWindow* window, const sf::Vector2i Resolution_, bool AllowMultipleInputs) : 
	IDIncrementer(0), Ready(false), Resolution(Resolution_), baseRocketInterface(Rocket::Core::String("")), Running(true), CommandThread(&Engine::PythonCommandLineIssuer, this), CommandThreadLaunched(false)
{
	SFGUISystem.TuneCull(true);
	
	srand(time(0));
	rng.seed(time(0));
	ApplicationConfiguration.Initialize(configFile);
	ContentManager.Initialize(ApplicationConfiguration);
	PScripter.SetPath(ApplicationConfiguration.GetApplicationSetting("ResourcesBaseDirectory") + ApplicationConfiguration.GetApplicationSetting("ScriptPath"));
	PScripter.AddScriptObject<Engine>("Engine", *this, PScripter.GetEngineModule());
	PrimarySoundSystem.SetAudioDirectory(ApplicationConfiguration.GetApplicationSetting(std::string("ResourcesBaseDirectory")) + ApplicationConfiguration.GetApplicationSetting(std::string("MusicSubDir")));
	PrimarySoundSystem.SetSoundEffectsDirectory(ApplicationConfiguration.GetApplicationSetting(std::string("ResourcesBaseDirectory")) + ApplicationConfiguration.GetApplicationSetting(std::string("SoundEffectsDir")));
	Input.Load(configFile, this);
	
	Input.AddKeyPressedEvent(boost::bind(&Graphics::Screens::ScreenManager::HandleKeyPressed, &ScreenManager, _1, _2, _3));
	Input.AddKeyReleasedEvent(boost::bind(&Graphics::Screens::ScreenManager::HandleKeyReleased, &ScreenManager, _1, _2, _3)); 

	LSystem.PrimaryLightSystem.Create(AABB(Vec2f(0.f + 100.f, 0.f + 100.f), Vec2f(static_cast<float>(Resolution.x) + 100.f, static_cast<float>(Resolution.y) +100.f)), window, 
		ContentManager.GetShaderDirectory() + "lightFin.png", ContentManager.GetShaderDirectory() + "lightAttenuationShader.frag");
	//LSystem.PrimaryLightSystem.SetView(window->getView());
	
	baseRocketInterface.SetRootDirectory(this->ContentManager.GetHTMLDirectory().c_str());
	baseRocketRenderer.target = window;
	Rocket::Core::SetRenderInterface(&baseRocketRenderer);
	Rocket::Core::SetFileInterface(&baseRocketInterface);
	Rocket::Core::SetSystemInterface(&baseRocketSystem);
	Rocket::Core::Initialise();
	
	//Prep Font Database
	Rocket::Core::FontDatabase::LoadFontFace((this->ContentManager.GetFontDirectory() + "Chaney Normal.ttf").c_str(), "Chaney", Rocket::Core::Font::Style::STYLE_NORMAL, Rocket::Core::Font::Weight::WEIGHT_NORMAL);
	Rocket::Core::FontDatabase::LoadFontFace((this->ContentManager.GetFontDirectory() + "Chaney Italic.ttf").c_str(), "Chaney", Rocket::Core::Font::Style::STYLE_ITALIC, Rocket::Core::Font::Weight::WEIGHT_NORMAL);
	Rocket::Core::FontDatabase::LoadFontFace((this->ContentManager.GetFontDirectory() + "Chaney Bold.ttf").c_str(), "Chaney", Rocket::Core::Font::Style::STYLE_NORMAL, Rocket::Core::Font::Weight::WEIGHT_BOLD);
	Rocket::Core::FontDatabase::LoadFontFace((this->ContentManager.GetFontDirectory() + "Chaney Bold Italic.ttf").c_str(), "Chaney", Rocket::Core::Font::Style::STYLE_ITALIC, Rocket::Core::Font::Weight::WEIGHT_BOLD);

	Rocket::Core::FontDatabase::LoadFontFace((this->ContentManager.GetFontDirectory() + "Eurostile.ttf").c_str(), "Eurostile", Rocket::Core::Font::Style::STYLE_NORMAL, Rocket::Core::Font::Weight::WEIGHT_NORMAL);

	Ready = true;

	
}
Engine::~Engine()
{
	Rocket::Core::Shutdown();
	if (CommandThreadLaunched)
	{
		CommandThread.terminate();
	}
	
}
int Engine::GetUID()
{
	return ++IDIncrementer;
}
bool Engine::IsReady() const
{
	return Ready;
}
void Engine::HandleWindowEvents(sf::RenderWindow &GameWindow, bool& ContinueRunning)
{
	sf::Event event;
	while(GameWindow.pollEvent(event))
	{
		Input.SetCurrentEvent(event);
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			{
				SFGUIDesktop.HandleEvent(event);
				//Input.DispatchKeyPressedEvents(this->GetTime(), event.key, true);
			}
			break;
		case sf::Event::MouseButtonReleased:
			{
				SFGUIDesktop.HandleEvent(event);
				//Input.DispatchKeyReleasedEvents(this->GetTime(), event.key);
			}
			break;
		case sf::Event::MouseMoved:
			{
				SFGUIDesktop.HandleEvent(event);
				//Input.DispatchKeyPressedEvents(this->GetTime(), event.key, true);
			}
			break;
		case sf::Event::LostFocus:
			{
				//PrimaryInput.SetActive(false);
			}
			break;
		case sf::Event::GainedFocus:
			{
				//PrimaryInput.SetActive(true);
			}
			break;
		case sf::Event::Closed:
			{
				ContinueRunning = false;
			}
			break;
		case sf::Event::KeyPressed:
			{
				SFGUIDesktop.HandleEvent(event);
				//std::cout << "Sending key pressed event\n";
				Input.DispatchKeyPressedEvents(this->GetTime(), event.key);
				//std::cout << "Ending key pressed event\n";
			}
			break;
		case sf::Event::KeyReleased:
			{
				SFGUIDesktop.HandleEvent(event);
				//std::cout << "Key Released in Engine\n";
				Input.DispatchKeyReleasedEvents(this->GetTime(), event.key);
			}
			break;
		case sf::Event::JoystickButtonPressed:
			{
				Input.DispatchJoystickKeyPressedEvents(this->GetTime(), event.joystickButton);
			}
			break;
		case sf::Event::JoystickButtonReleased:
			{
				Input.DispatchJoystickKeyReleasedEvents(this->GetTime(), event.joystickButton);
			}
			break;
		case sf::Event::JoystickMoved:
			{
				
			}
			break;
		}
	}
}
void Engine::DispatchInputs()
{

}

sf::Uint32 Engine::GetTime()
{
	return TimeModule.GetGameElapsedTime();
}
//Get Subsystems
Audio::SoundSystem& Engine::GetSoundSystem()
{
	return PrimarySoundSystem;
}
Scripting::PythonScripter& Engine::GetPythonScripter()
{
	return PScripter;
}

void Engine::LaunchPythonCommandLineThread()
{
	CommandThread.launch();
}
const std::string CommandHead = "from EngineModule import *\nfrom CharacterModule import *\nfrom EntityModule import *\n";
void Engine::PythonCommandLineIssuer()
{
	std::string Command;//[256];
	while(true)
	{
		std::getline(std::cin, Command);
		try
		{
			GetPythonScripter().RunString(CommandHead + Command);
		}
		catch (boost::python::error_already_set)
		{
			PyErr_Print();
		}

	}
}

Configuration::AppConfiguration& Engine::GetApplicationConfiguration()
{
	return ApplicationConfiguration;
}
Time::GameTimeModule& Engine::GetGameTimeModule()
{
	return TimeModule;
}
Content::ContentManager& Engine::GetContentManager()
{
	return ContentManager;
}

Input::InputModule& Engine::GetInput()
{
	return Input;
}

Graphics::Screens::ScreenManager& Engine::GetScreenManager()
{
	return ScreenManager;
}

Graphics::LightingSystem& Engine::GetLightingSystem()
{
	return LSystem;
}

sfg::SFGUI& Engine::GetSFGUI()
{
	return SFGUISystem;
}
sfg::Desktop& Engine::GetActiveDesktop()
{
	return SFGUIDesktop;
}
const sf::Vector2i& Engine::GetResolution() const
{
	return Resolution;
}
bool Engine::IsRunning() const
{
	return Running;
}
sf::View TempView;
sf::Vector2f offset(240.f, -115.f);
void Engine::Draw(sf::RenderTarget &window) 
{
	ScreenManager.Draw(window);
	//TempView = window.getView();
	//TempView.setCenter(TempView.getCenter() + offset);// + sf::Vector2f(160, 60));
	//LSystem.PrimaryLightSystem.SetView(TempView);
	//LSystem.Draw(window);
}

void Engine::Draw(sf::RenderTarget &window, sf::RenderStates states) 
{
	ScreenManager.Draw(window, states);
	TempView = window.getView();
	TempView.setCenter(TempView.getCenter() + sf::Vector2f(160, 60));
	LSystem.PrimaryLightSystem.SetView(TempView);
	LSystem.Draw(window, states);
}

void Engine::Update(const sf::Uint32 time, const float TimeScale)
{
	ScreenManager.Update(time, TimeScale);
	LSystem.Update(time, TimeScale);
	sf::Time elapsed = sf::milliseconds(time - LastSFGUIUpdate);
	if (elapsed.asMilliseconds() > 20)
	{
		SFGUIDesktop.Update(elapsed.asSeconds());
		LastSFGUIUpdate = time;
	}
}
void Engine::Update(const float time, const float TimeScale)
{
	Update(static_cast<sf::Uint32>(time * 0.001), TimeScale);
}
