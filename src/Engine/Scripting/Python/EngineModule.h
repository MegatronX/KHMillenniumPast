#pragma once
#ifndef _PYTHONENGINEMODULE_H_
#define _PYTHONENGINEMODULE_H_
#include <Engine.h>
#include <System/Input/InputInterface.h>
#include "ScriptHelpers.h"
using namespace Content;
using namespace Audio;
namespace Scripting
{
	/*class InputInterfaceWrap : public ::Input::InputInterface
	{
	public:
		InputInterfaceWrap(PyObject* self, bool acceptingInputs = true) : self(self), ::Input::InputInterface(acceptingInputs)
		{
		}

		virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::PlayerInput pInput, ::Input::InputAction& action) override
		{
			return call_method<bool>(self, "HandleKeyPressed", time, ptr(inputModule), pInput, boost::ref(action));
		}
		virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::PlayerInput pInput, ::Input::InputAction& action) override
		{
			return call_method<bool>(self, "HandleKeyReleased", time, ptr(inputModule), pInput, boost::ref(action));
		}
	private:
		PyObject* self;
	};*/
	template <class T>
	T* GetPointerOfObject(T& src)
	{
		return &T;
	}
	BOOST_PYTHON_MODULE(EngineModule)
	{
		//def("GetPointerOfObject", &)
		enum_<Cache::GameStyle>("GameStyle")
			.value("FFTactics", Cache::GameStyle::FFTactics)
			.value("FFV", Cache::GameStyle::FFV)
			.value("FFVI", Cache::GameStyle::FFVI)
			.value("Main", Cache::GameStyle::Main)
			;
		enum_<Cache::ResourceClass>("ResourceClass")
			.value("BackColor", Cache::ResourceClass::BackColor)
			.value("Background", Cache::ResourceClass::Background)
			.value("BattleBack", Cache::ResourceClass::BattleBack)
			.value("Boss", Cache::ResourceClass::Boss)
			.value("Chaser", Cache::ResourceClass::Chaser)
			.value("Enemy", Cache::ResourceClass::Enemy)
			.value("Guardian", Cache::ResourceClass::Guardian)
			.value("GUIBattleElement", Cache::ResourceClass::GUIBattleElement)
			.value("GUIMenuElement", Cache::ResourceClass::GUIMenuElement)
			.value("Icon", Cache::ResourceClass::Icon)
			.value("MagicIcon", Cache::ResourceClass::MagicIcon)
			.value("MagicSheet", Cache::ResourceClass::MagicSheet)
			.value("Music", Cache::ResourceClass::Music)
			.value("OverworldSprite", Cache::ResourceClass::OverworldSprite)
			.value("QuadrupleTriad", Cache::ResourceClass::QuadrupleTriad)
			.value("Queue", Cache::ResourceClass::Queue)
			.value("SkillSheet", Cache::ResourceClass::SkillSheet)
			.value("SoundEffect", Cache::ResourceClass::SoundEffect)
			.value("SummonSprite", Cache::ResourceClass::SummonSprite)
			.value("TileSet", Cache::ResourceClass::TileSet)
			.value("TitleScreen", Cache::ResourceClass::TitleScreen)
			.value("Voice", Cache::ResourceClass::Voice)
			.value("WorldImage", Cache::ResourceClass::WorldImage)
			;
		enum_<Cache::World>("World")
			.value("Any", Cache::World::Any)
			.value("Atlantis", Cache::World::Atlantis)
			.value("FFT", Cache::World::FF_T)
			.value("FFV", Cache::World::FF_V)
			.value("FFVI", Cache::World::FF_VI)
			.value("StationOfAwakening", Cache::World::StationOfAwakening)
			;
		enum_<::Input::InputAction>("InputAction")
			.value("Aux1", ::Input::InputAction::Aux1)
			.value("Aux2", ::Input::InputAction::Aux2)
			.value("AuxLeft", ::Input::InputAction::AuxLeft)
			.value("AuxRight", ::Input::InputAction::AuxRight)
			.value("Cancel", ::Input::InputAction::Cancel)
			.value("Confirm", ::Input::InputAction::Confirm)
			.value("Down", ::Input::InputAction::Down)
			.value("InvalidAction", ::Input::InputAction::InvalidAction)
			.value("Left", ::Input::InputAction::Left)
			.value("MouseLeft", ::Input::InputAction::MouseLeft)
			.value("MouseRight", ::Input::InputAction::MouseRight)
			.value("Right", ::Input::InputAction::Right)
			.value("Select", ::Input::InputAction::Select)
			.value("Start", ::Input::InputAction::Start)
			.value("Up", ::Input::InputAction::Up)
			;
		class_<::Input::InputModule, boost::noncopyable>("InputModule", no_init)
			.def("HandleKeyPressed", &::Input::InputInterface::HandleKeyPressed)
			.def("IsAcceptingInputs", &::Input::InputInterface::IsAcceptingInputs)
			.def("SetAcceptingInputs", &::Input::InputInterface::SetAcceptingInputs)
			.def("HandleKeyReleased", &::Input::InputInterface::HandleKeyReleased)
			.def("SuspendInputs", &::Input::InputModule::SuspendInputs, (boost::python::arg("timeIsDelta") = false))
			;
		enum_<::Input::PlayerInput>("PlayerInput")
			.value("Invalid", ::Input::PlayerInput::Invalid)
			.value("P1Input", ::Input::PlayerInput::P1Input)
			.value("P2Input", ::Input::PlayerInput::P2Input)
			.value("P3Input", ::Input::PlayerInput::P3Input)
			.value("P4Input", ::Input::PlayerInput::P4Input)
			;
		enum_<::Input::InputDevice>("InputDevice")
			.value("DEVICE_JOY1", ::Input::InputDevice::DEVICE_JOY1)
			;
		class_<::Input::InputActionResult>("InputActionResult", no_init)
			.def_readwrite("Cancelled", &::Input::InputActionResult::Cancelled)
			.def_readwrite("IAction", &::Input::InputActionResult::IAction)
			.def_readwrite("PInput", &::Input::InputActionResult::PInput)
			;
		/*class_<InputInterfaceWrap, boost::noncopyable>("InputInteface", init<boost::python::optional<bool> >())
			.def("HandleKeyPressed", pure_virtual(&::Input::InputInterface::HandleKeyPressed))
			.def("HandleKeyReleased", pure_virtual(&::Input::InputInterface::HandleKeyReleased))
			.def("IsAcceptingInputs", &::Input::InputInterface::IsAcceptingInputs)
			.def("SetAcceptingInputs", &::Input::InputInterface::SetAcceptingInputs)
			;*/
		class_<ContentManager, boost::noncopyable>("ContentManager", no_init)
			.def("GetFontDirectory", &ContentManager::GetFontDirectory, return_value_policy<reference_existing_object>())
			.def("GetHTMLDirectory", &ContentManager::GetHTMLDirectory, return_value_policy<reference_existing_object>())
			.def("GetMapDirectory", &ContentManager::GetMapDirectory, return_value_policy<reference_existing_object>())
			.def("GetShaderDirectory", &ContentManager::GetShaderDirectory, return_value_policy<reference_existing_object>())
			.def("RequestFont", &ContentManager::RequestFont)
			.def("RequestSpriteLoadOut", &ContentManager::RequestSpriteLoadout)
			.def("RequestTexture", &ContentManager::RequestTexture, (boost::python::arg("extension") = ".png"))
			.def("VerifyResourceExistance", &ContentManager::VerifyResourceExistance)
			;
		class_<SoundSystem, boost::noncopyable>("SoundSystem", no_init)
			.def("AddSound", &SoundSystem::AddSound, (boost::python::arg("overwriteExisting") = true, boost::python::arg("useStoredPath") = true, boost::python::arg("IsSoundEffect") = false, boost::python::arg("extension") = ".mp3"))
			.def("ClearSounds", &SoundSystem::ClearSounds)
			.def("GetPausedStatus", &SoundSystem::GetPausedStatus)
			.def("MakeGroups", &SoundSystem::MakeGroups)
			.def("SetChannelPause", &SoundSystem::SetChannelPause, (boost::python::arg("ChannelPause") = true))
			.def("PlaySound", &SoundSystem::Play, (boost::python::arg("channel") = 0, boost::python::arg("loop") = true, boost::python::arg("Volume") = 1.0f))
			.def("Play", &SoundSystem::Play, (boost::python::arg("channel") = 0, boost::python::arg("loop") = true, boost::python::arg("Volume") = 1.0f))
			.def("MultiplyPlaybackSpeed", &SoundSystem::MultiplyPlaybackSpeed, (boost::python::arg("ChannelID") = 0, boost::python::arg("PlaybackMult") = 1.0f))
// int channel = 0, bool loop = true, int StartMillseconds = -1, int EndMilliseconds = -1, float Volume = 1.0);
			.def("PlaySoundSection", &SoundSystem::PlaySection, (boost::python::arg("channel") = 0, boost::python::arg("loop") = true, boost::python::arg("StartMilliseconds") = -1, boost::python::arg("EndMilliseconds") = -1, boost::python::arg("Volume") = 1.0f))
			.def("PlaySection", &SoundSystem::PlaySection, (boost::python::arg("channel") = 0, boost::python::arg("loop") = true, boost::python::arg("StartMilliseconds") = -1, boost::python::arg("EndMilliseconds") = -1, boost::python::arg("Volume") = 1.0f))

			;
		//.def("Draw", (void (sf::RenderWindow::*)(const sf::Drawable&, const sf::RenderStates&))&sf::RenderWindow::draw
		class_<Configuration::AppConfiguration>("AppConfiguration", no_init)
			//.def("GetApplicationSetting", (const std::string& (Configuration::AppConfiguration::*)(const char*))&Configuration::AppConfiguration::GetApplicationSetting, return_value_policy<reference_existing_object>())
			.def("GetApplicationSetting", (const std::string (Configuration::AppConfiguration::*)(const std::string&))&Configuration::AppConfiguration::GetApplicationSettingByVal)
			//.def("", &Configuration::AppConfiguration:)
			//.def("", &Configuration::AppConfiguration:)
			//.def("", &Configuration::AppConfiguration:)
			;
		class_<::Engine, boost::noncopyable>("Engine", no_init)
			.def("GetApplicationConfiguration", &::Engine::GetApplicationConfiguration, return_value_policy<reference_existing_object>())
			.def("GetGameTimeModule", &::Engine::GetGameTimeModule, return_value_policy<reference_existing_object>())
			.def("GetPythonScripter", &::Engine::GetPythonScripter, return_value_policy<reference_existing_object>())
			.def("GetSoundSystem", &::Engine::GetSoundSystem, return_value_policy<reference_existing_object>())
			.def("GetContentManager", &::Engine::GetContentManager, return_value_policy<reference_existing_object>())
			.def("GetScreenManager", &::Engine::GetScreenManager, return_value_policy<reference_existing_object>())
			.def("GetInput", &::Engine::GetInput, return_value_policy<reference_existing_object>())
			.def("GetTime", &::Engine::GetTime)
			.def("GetUID", &::Engine::GetUID)
			//.def("", &Engine:)
			//.def("", &Engine:)
			;

	}
}

#endif