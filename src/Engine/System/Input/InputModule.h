#pragma once
#ifndef _INPUTMODULE_H_
#define _INPUTMODULE_H_
#include "InputDevice.h"
#include <boost/unordered_map.hpp>
#include <sfml/Window.hpp>
#include <sfml/System.hpp>
#include <boost/signal.hpp>

class Engine;

namespace Input
{
	enum PlayerInput
	{
		P1Input,
		P2Input,
		P3Input,
		P4Input,
		Invalid
	};
	#define InputCount 12
	#define MaxPlayerCount 2
	enum InputAction
	{
		Confirm,
		Cancel,
		Aux1,
		Aux2,
		Start, 
		Select,
		Up,
		Down,
		Left,
		Right,
		AuxLeft,
		AuxRight,
		MouseLeft,
		MouseRight,
		MouseMove,
		InvalidAction
	};
	extern const boost::unordered_map<InputAction, std::string> ActionNameLookup;
	extern const boost::unordered_map<std::string, InputAction> NameActionLookup;
	extern const boost::unordered_map<std::string, sf::Keyboard::Key> StringToKeyMap;
	extern const boost::unordered_map<sf::Keyboard::Key, std::string> KeyToStringMap;
	extern const boost::unordered_map<sf::Event::EventType, InputAction> EventTypeToAction;
	extern const boost::unordered_map<InputAction, sf::Event::EventType> ActionToEventType;
	struct InputActionResult
	{
	public:
		InputActionResult(bool cancelled = false, PlayerInput pInput = PlayerInput::P1Input, InputAction iAction = InputAction::InvalidAction) :
		  Cancelled(cancelled), IAction(iAction), PInput(pInput)
		{

		}
		virtual ~InputActionResult()
		{
		}
		bool Cancelled;
		InputAction IAction;
		PlayerInput PInput;
	};
	class PlayerInputSet
	{
	public:
		PlayerInputSet(unsigned int joystckId = 0);
		void MapKeyboardInput(sf::Keyboard::Key key, InputAction action);

		void MapJoystickButton(unsigned int button, InputAction action);

		const boost::unordered_map<sf::Keyboard::Key, InputAction>& GetKeyboardInputMap() const;
		const boost::unordered_map<InputAction, sf::Keyboard::Key>& GetReverseKeyboardInputMap() const;
		const boost::unordered_map<unsigned int, InputAction>& GetJoypadInputMap() const;
		const boost::unordered_map<InputAction, unsigned int>& GetReverseJoypadInputMap() const;

		//Returns the key mapped to an action
		sf::Keyboard::Key operator[] (const InputAction action) const;
		
		//Maps a keyboard key to his players action
		InputAction operator[] (const sf::Keyboard::Key key) const;
		//Return joystick mapping
		InputAction operator[] (const unsigned int joyButton) const;
		unsigned int GetJoystickMapping(const InputAction action) const;
		unsigned int GetJoystickID() const;

		void Clear();
		virtual ~PlayerInputSet();
		//unsigned int operator[] (const sf::Joystick::);
	private:
		boost::unordered_map<sf::Keyboard::Key, InputAction> KeyboardInputMap;
		boost::unordered_map<InputAction, sf::Keyboard::Key> ReverseKeyboardInputMap;
		boost::unordered_map<unsigned int, InputAction> JoypadInputMap;
		boost::unordered_map<InputAction, unsigned int> ReverseJoypadInputMap;
		unsigned int JoystickID;
	
	};

	class InputModule;

	typedef boost::signal<void (const sf::Uint32, const InputModule*, InputActionResult& actionResult) > KeyChangeEvent;
	class InputModule : public boost::signals::trackable
	{
	public:
		InputModule();
		InputModule(const std::string& configFile, Engine* engine);

		void Load(const std::string& configFile, Engine* engine);
		PlayerInputSet& GetPlayerInput(PlayerInput input);

		bool IsActionPushed(PlayerInput input, const InputAction action);

		boost::signals::connection AddKeyPressedEvent(const KeyChangeEvent::slot_type& handler);
		void DispatchKeyPressedEvents(const sf::Uint32 time, sf::Event::KeyEvent& keyEvent, bool DispatchInvalidActions = false);
		void DispatchJoystickKeyPressedEvents(const sf::Uint32 time, sf::Event::JoystickButtonEvent& joyEvent, bool DispatchInvalidActions = false);

		boost::signals::connection AddKeyReleasedEvent(const KeyChangeEvent::slot_type& handler);
		void DispatchKeyReleasedEvents(const sf::Uint32 time, sf::Event::KeyEvent& keyEvent, bool DispatchInvalidActions = false);
		void DispatchJoystickKeyReleasedEvents(const sf::Uint32 time, sf::Event::JoystickButtonEvent& joyEvent, bool DispatchInvalidActions = false);

		void SetActivePlayer(PlayerInput player);
		PlayerInput GetActivePlayer() const;

		void Clear();

		void SuspendInputs(const sf::Uint32 expireTime, bool timeIsDelta = false);

		void SetCurrentEvent(sf::Event& ev);
		const sf::Event& GetCurrentEvent() const;

		bool operator[] (const InputAction action);
		bool operator[] (const sf::Keyboard::Key key);
		bool operator[] (unsigned int joystickKey);

	protected:
	private:
		sf::Event* CurrentEvent;
		//sf::Keyboard* keyboard;
		//sf::Joystick* joystick;
		Engine* engine;
		bool Suspended;
		sf::Uint32 SuspenstionEnd;
		KeyChangeEvent KeyPressedSignal;
		KeyChangeEvent KeyReleasedSignal;

		PlayerInput ActiveInput;
		PlayerInputSet Player1InputMap;
#if MaxPlayerCount > 1
		PlayerInputSet Player2InputMap;
#endif
#if MaxPlayerCount > 2
		PlayerInputSet Player3InputMap;
#endif
	};
}
#endif