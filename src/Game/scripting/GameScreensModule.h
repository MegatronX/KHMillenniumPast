#pragma once
#ifndef _GAMESCREENSMODULE_H_
#define _GAMESCREENSMODULE_H_
#include <scripting/Python/ScriptHelpers.h>
#include <Graphics/Screens/GameScreen.h>
#include <Graphics/Screens/BasicRMLScreen.h>
#include <Graphics/Screens/TitleScreen.h>
#include <Graphics/Rocket/ElementTransformInterface.h>
#include <Graphics/Rocket/ElementTransformer.h>
using namespace ::Graphics::Screens;
using namespace ::Game::Graphics::Screens;
namespace Game
{
	using namespace Graphics::GameRocket;
	namespace Scripting
	{
		/*class GameScreenWrapper : public ::Game::Graphics::Screens::GameScreen
		{
		public:
			GameScreenWrapper(PyObject* self, const std::string& name, Engine* engine, int id) : self(self), ::Game::Graphics::Screens::GameScreen(name, engine, id)
			{
			}
			void Draw(sf::RenderWindow &window, sf::Shader &shader) override
			{
				call_method<void>(self, "Draw", boost::ref(window), boost::ref(shader));
			}
			void Draw(sf::RenderWindow& window) override
			{
				call_method<void>(self, "Draw", boost::ref(window));
			}
			virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::PlayerInput pInput, ::Input::InputAction& action) override
			{
				return false;//call_method<bool>(self, "HandleKeyPressed", time, ptr(inputModule), pInput, boost::ref(action));
			}
			virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::PlayerInput pInput, ::Input::InputAction& action) override
			{
				return false;//call_method<bool>(self, "HandleKeyReleased", time, ptr(inputModule), pInput, boost::ref(action));
			}
		private:
			PyObject* self;
			};*/
		class BasicRMLScreenWrap : public BasicRMLScreen
		{
		public:
			BasicRMLScreenWrap(PyObject* self, const std::string& name, const std::string& rmlDoc, Engine* engine, int id) : self(self), BasicRMLScreen(name, rmlDoc, engine, id)
			{

			}
			void Draw(sf::RenderTarget &window, sf::RenderStates states) override
			{
				call_method<void>(self, "Draw", boost::ref(window), states);
			}
			void Draw(sf::RenderTarget& window) override
			{
				//BasicRMLScreen::Draw(window);
				call_method<void>(self, "Draw", boost::ref(window));
			}
			void DrawDefault(sf::RenderTarget& window, sf::RenderStates states)
			{
				BasicRMLScreen::Draw(window, states);
			}
			void DrawDefault(sf::RenderTarget& window)
			{
				BasicRMLScreen::Draw(window);
			}
			void Update(const sf::Uint32 time, const float TimeScale = 1.0) override
			{
				call_method<void>(self, "Update", time, TimeScale);
			}
			void UpdateDefault(const sf::Uint32 time, const float TimeScale = 1.0)
			{
				BasicRMLScreen::Update(time, TimeScale);
			}
			bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& iaction) override
			{
				//return false;
				return call_method<bool>(self, "HandleKeyPressed", time, boost::python::ptr(inputModule), boost::ref(iaction));
			}
			bool HandleKeyPressedDefault(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionRes)
			{
				return BasicRMLScreen::HandleKeyPressed(time, inputModule, actionRes);
			}
			bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& iaction) override
			{
				//return false;
				return call_method<bool>(self, "HandleKeyReleased", time, ptr(inputModule), boost::ref(iaction));
				//if (override func = get_override)
				//return call_method<bool>(self, "HandleKeyReleased", time, ptr(inputModule), pinput, boost::ref(iaction));
			}
			bool HandleKeyReleasedDefault(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& iaction)
			{
				return BasicRMLScreen::HandleKeyReleased(time, inputModule, iaction);
			}
		private:
			PyObject* self;
		};
		BOOST_PYTHON_MODULE(GameScreensModule)
		{
			class_<GameScreen, bases<Screen>, boost::noncopyable >("GameScreen", init<const std::string&, ::Engine*, int>())
				;
			class_<BasicRMLScreen, bases<GameScreen>, boost::shared_ptr<BasicRMLScreenWrap>, boost::noncopyable >("BasicRMLScreen", init<const std::string&, const std::string&, Engine*, int>())
				.def("AddNewTransform", (void (BasicRMLScreen::*)(const std::string&, boost::shared_ptr<::Graphics::GameRocket::ElementTransformer>&, sf::Uint32))&BasicRMLScreen::AddNewTransform, boost::python::arg("delay") = 0)
				.def("RemoveTransform", &BasicRMLScreen::RemoveTransform)
				.def("GetDocument", &BasicRMLScreen::GetDocument, return_value_policy<reference_existing_object>())
				.def("GetPageContext", &BasicRMLScreen::GetPageContext, return_value_policy<reference_existing_object>())
				.def("Draw", (void (BasicRMLScreen::*)(sf::RenderTarget&))&BasicRMLScreen::Draw, (void (BasicRMLScreenWrap::*)(sf::RenderTarget&))&BasicRMLScreenWrap::DrawDefault)
				.def("Draw", (void (BasicRMLScreen::*)(sf::RenderTarget&, sf::RenderStates))&BasicRMLScreen::Draw, (void (BasicRMLScreenWrap::*)(sf::RenderTarget&, sf::RenderStates))&BasicRMLScreenWrap::DrawDefault)
				.def("HandleKeyPressed", &BasicRMLScreenWrap::HandleKeyPressedDefault)
				.def("HandleKeyReleased", &BasicRMLScreenWrap::HandleKeyReleasedDefault)
				.def("Update", (void (BasicRMLScreen::*)(const sf::Uint32, float))&BasicRMLScreen::Update, &BasicRMLScreenWrap::UpdateDefault, boost::python::arg("TimeScale") = 1.f)
				.def("ClearTransforms", &BasicRMLScreen::ClearTransforms)
				;
			class_<TitleScreen, bases<BasicRMLScreen>, boost::noncopyable >("TitleScreen", no_init)
				//.def("", &TitleScreen::)
				//.def("", &TitleScreen:)
				;
			//(Rocket::Core::String (Element::*)() const)&Element::GetInnerRML
			/*class_<GameScreen, bases<Screen> >("GameScreen", init<const std::string&, ::Engine*, int>())
				;*/
			/*class_<BasicRMLScreen, bases<GameScreen> >("BasicRMLScreen", init<const std::string&, const std::string&, Engine*, int>())
				.def("AddNewTransform", (void (BasicRMLScreen::*)(const std::string&, boost::shared_ptr<::Graphics::GameRocket::ElementTransformer>&))&BasicRMLScreen::AddNewTransform)
				.def("GetDocument", &BasicRMLScreen::GetDocument, return_value_policy<reference_existing_object>())
				.def("GetPageContext", &BasicRMLScreen::GetPageContext, return_value_policy<reference_existing_object>())*/
				/*.def("", &BasicRMLScreen::)
				.def("", &BasicRMLScreen:)
				.def("", &BasicRMLScreen:)
				.def("", &BasicRMLScreen:)
				.def("", &BasicRMLScreen:)
				.def("", &BasicRMLScreen:)
				.def("", &BasicRMLScreen:)*/
			;
		}
	}
}

#endif