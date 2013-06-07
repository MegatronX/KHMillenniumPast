#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_
#include <ctime>
#include <ContentManagement/ContentManager.h>
#include <Audio/SoundSystem.h>
#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>
#include <scripting/Python/PythonScripter.h>
#include <Time/GameTimeModule.h>
#include <sfml/Window.hpp>
#include <random>
#include <limits>
#include <system/input/InputModule.h>
#include <graphics/Screens/ScreenManager.h>
#include <Rocket/Core.h>
#include <Graphics/Rocket/BaseFileInterface.h>
#include <Graphics/Rocket/LibRocketRenderInterface.h>
#include <Graphics/Rocket/RocketSystemInterface.h>
#include <Graphics/AnimatedDraw.h>
#include <graphics/lighting/LightingSystem.h>
#include <SFGUI/SFGUI.hpp>
class Engine : public ::Graphics::AnimatedDraw, private boost::noncopyable
{
public:
	Engine();
	Engine(const std::string& configFile, sf::RenderWindow* window, const sf::Vector2i Resolution = sf::Vector2i(800, 600), bool AllowMultipleInputs = true);
	int GetUID();
	bool IsReady() const;

	void Engine::HandleWindowEvents(sf::RenderWindow &GameWindow, bool& ContinueRunning);
	void DispatchInputs();

	sf::Uint32 GetTime();
	//Get Subsystems
	Audio::SoundSystem& GetSoundSystem();
	Scripting::PythonScripter& GetPythonScripter();
	void LaunchPythonCommandLineThread();
	Configuration::AppConfiguration& GetApplicationConfiguration();
	Time::GameTimeModule& GetGameTimeModule();
	Content::ContentManager& GetContentManager();
	Input::InputModule& GetInput();
	::Graphics::Screens::ScreenManager& GetScreenManager();

	::Graphics::LightingSystem& GetLightingSystem();
	sfg::SFGUI& GetSFGUI();
	sfg::Desktop& GetActiveDesktop();

	const sf::Vector2i& GetResolution() const;
	bool IsRunning() const;

	//Draw Interface

	virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0);
	virtual void Update(const float time, const float TimeScale = 1.0);
	virtual void Draw(sf::RenderTarget &window);
	virtual void Draw(sf::RenderTarget &window, sf::RenderStates states);

	//Random

	template <class T>
	T GetRandom(const std::uniform_int_distribution<T>& distr)
	{
		return distr(rng);
	}
	template <class T>
	T GetRandomReal(const std::uniform_real_distribution<T>& distr)
	{
		return distr(rng);
	}

	int GetRandomInt(int min = 0, int max = std::numeric_limits<int>::max())
	{
		if (min > max)
		{
			int temp = min;
			min = max;
			max = temp;
		}
		std::uniform_int_distribution<int> randrange(min, max);
		return static_cast<int>(GetRandom<int>(randrange));
	}

	double GetRandomDouble(double min = std::numeric_limits<double>::min(), double max = std::numeric_limits<double>::max())
	{
		if (min > max)
		{
			double temp = min;
			min = max;
			max = temp;
		}
		std::uniform_real_distribution<double> randrange(min, max);
		return static_cast<double>(GetRandomReal<double>(randrange));
		//return static_cast<T>(min + (double_dist(rng) / (min < max ? max - min : 1)));
		
	}

	virtual ~Engine();
protected:
	//Thread that gets and issues commands from the command line. Launch with sf::Thread to add real time scripting
	void PythonCommandLineIssuer();
	sf::Thread CommandThread;
	bool CommandThreadLaunched;
private:
	//Basic Properties
	int IDIncrementer;
	bool Ready;
	bool Running;
	sf::Vector2i Resolution;

	//Subsystems
	Audio::SoundSystem PrimarySoundSystem;
	Scripting::PythonScripter PScripter;
	Configuration::AppConfiguration ApplicationConfiguration;
	Content::ContentManager ContentManager;
	::Graphics::LightingSystem LSystem;
	Time::GameTimeModule TimeModule;
	sf::Uint32 LastSFGUIUpdate;
	Input::InputModule Input;
	::Graphics::Screens::ScreenManager ScreenManager;
	sfg::SFGUI SFGUISystem;
	sfg::Desktop SFGUIDesktop;
	//Rocket Interfaces
	::Graphics::RocketInterface::BaseFileInterface baseRocketInterface;
	::Graphics::RocketInterface::RocketSFMLRenderer baseRocketRenderer;
	::Graphics::RocketInterface::RocketSystemInterface baseRocketSystem;

	//Randoms
	std::mt19937 rng;
	std::uniform_int_distribution<uint32_t> uint_dist;
	std::uniform_real_distribution<double> double_dist;
};
#endif