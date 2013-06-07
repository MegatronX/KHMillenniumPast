#pragma once
#ifndef _GRAPHICSMODULE_H_
#define _GRAPHICSMODULE_H_
#include "ScriptHelpers.h"
#include <Graphics/AnimatedDraw.h>
#include <Graphics/DrawInterface.h>
#include <Graphics/Screens/Screen.h>
using namespace ::Graphics;
namespace Scripting
{
	class DrawInterfaceWrap : public DrawInterface
	{
	public:
		DrawInterfaceWrap(PyObject* self, int priority = 0, bool drawing = true) : self(self), DrawInterface(priority, drawing)
		{

		}
		DrawInterfaceWrap(PyObject* self, const DrawInterface& src) : self(self), DrawInterface(src)
		{

		}
		DrawInterfaceWrap(PyObject* self, const DrawInterfaceWrap& src) : self(self), DrawInterface(src)
		{
		}
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			call_method<void>(self, "draw", boost::ref(target), states);
		}
	private:
		PyObject* self;
	};

	class AnimatedDrawWrap : public AnimatedDraw
	{
	public:
		AnimatedDrawWrap(PyObject* self, int priority = 0, bool paused = true) : self(self), AnimatedDraw(paused, priority)
		{

		}
		//??? not sure how to do this
		AnimatedDrawWrap(PyObject* self, const AnimatedDrawWrap& src) : self(self), AnimatedDraw(src)
		{

		}
		AnimatedDrawWrap(PyObject* self, const AnimatedDraw& src) : self(self), AnimatedDraw(src)
		{

		}
		void Update(const sf::Uint32 time, const float TimeScale = 1.0) override
		{
			call_method<void>(self, "Update", time, TimeScale);
		}
		void Update(const float time, const float TimeScale = 1.0) override
		{
			call_method<void>(self, "Update", time, TimeScale);
			
		}
	private:
		PyObject* self;
	};
	BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(RenderWindowDraw, Draw, 1, 2)
		//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(RenderWindowSetActive, SetActive, 0, 1)
	BOOST_PYTHON_MODULE(GraphicsModule)
	{
		class_<DrawInterface, boost::shared_ptr<DrawInterfaceWrap> >("DrawInterface", init<boost::python::optional<int, bool>>())
			.def("GetDrawPriority", &DrawInterface::GetDrawPriority)
			.def("IsDrawing", &DrawInterface::IsDrawing)
			.def("SetDrawing", &DrawInterface::SetDrawing)
			.def("SetDrawPriority", &DrawInterface::SetDrawPriority)
			;
		class_<sf::RenderStates>("RenderStates", no_init)
			;
		class_<AnimatedDraw, boost::shared_ptr<AnimatedDrawWrap>, bases<DrawInterface> >("AnimatedDraw", init<boost::python::optional<bool, int>>())
			;
		/*enum_<sf::RenderStates>("RenderStates")
			.def("BlendMode", sf::RenderStates::BlendMode)
			;*/
		class_<sf::Vector2f>("Vector2f", init<>())
			.def(init<float, float>())
			.def_readwrite("x", &sf::Vector2f::x)
			.def_readwrite("y", &sf::Vector2f::y)
			//.def(-self)
			//.def(+self)
			.def(self + self)
			.def(self - self)
			.def(self += self)
			.def(self -= self)
			//.def(self * float())
			.def(self / float())
			;

		class_<sf::Vector2i>("Vector2i", init<>())
			.def(init<int, int>())
			.def_readwrite("x", &sf::Vector2i::x)
			.def_readwrite("y", &sf::Vector2i::y)
			.def(self + self)
			.def(self - self)
			.def(self += self)
			.def(self -= self)
			//.def(self * float())
			//.def(self / float())
			;
		
		class_<sf::Texture>("Texture", init<>())
			;
		class_<sf::Image>("Image", init<>())
			;
		class_<sf::Shader, boost::noncopyable>("Shader", init<>())
			.def("Bind", &sf::Shader::bind)
			
			.def("IsAvailable", &sf::Shader::isAvailable).staticmethod("IsAvailable")
			//.def("LoadFromFile", &sf::Shader::LoadFromFile)
			//.def("LoadFromMemory", &sf::Shader::LoadFromMemory)
			//.def("Unbind", &sf::Shader::unbind)
			;
		//(Rocket::Core::String (Element::*)() const)&Element::GetInnerRML
		class_<sf::RenderWindow, boost::noncopyable>("RenderWindow", no_init)
			.def("Capture", &sf::RenderWindow::capture)
			.def("Clear", &sf::RenderWindow::capture)
			.def("Close", &sf::RenderWindow::close)
			//.def("ConvertCoords", (sf::Vector2f (sf::RenderWindow::*)(const sf::Vector2i&) const)&sf::RenderWindow::convertCoords)
			//.def("ConvertCoords", (sf::Vector2f (sf::RenderWindow::*)(const sf::Vector2i&, const sf::View&) const)&sf::RenderWindow::convertCoords)
			.def("Display", &sf::RenderWindow::display)
			.def("Draw", (void (sf::RenderWindow::*)(const sf::Drawable&, const sf::RenderStates&))&sf::RenderWindow::draw, (boost::python::arg("states") = sf::RenderStates::Default))
			.def("Draw", (void (sf::RenderWindow::*)(const sf::Vertex*, unsigned int, sf::PrimitiveType, const sf::RenderStates&))&sf::RenderWindow::draw, (boost::python::arg("states") = sf::RenderStates::Default))
			//.def("EnableKeyRepeat", &sf::RenderWindow::enableKeyRepeat)
			//.def("EnableVerticalSync", &sf::RenderWindow::enableVerticalSync)
			.def("GetDefaultView", &sf::RenderWindow::getDefaultView, return_value_policy<reference_existing_object>())
			//.def("GetFrameTime", &sf::RenderWindow::getFrameTime)
			.def("GetView", &sf::RenderWindow::getView, return_value_policy<reference_existing_object>())
			.def("GetViewport", &sf::RenderWindow::getViewport)
			.def("IsOpened", &sf::RenderWindow::isOpen)
			.def("PopGLStates", &sf::RenderWindow::popGLStates)
			.def("PushGLStates", &sf::RenderWindow::pushGLStates)
			.def("ResetGLStates", &sf::RenderWindow::resetGLStates)
			.def("SetActive", &sf::RenderWindow::setActive, (boost::python::arg("active") = true))
			.def("SetFrameLimit", &sf::RenderWindow::setFramerateLimit)
			.def("SetJoystickThreshold", &sf::RenderWindow::setJoystickThreshold)
			.def("SetPosition", &sf::RenderWindow::setPosition)
			.def("SetSize", &sf::RenderWindow::setSize)
			.def("SetTitle", &sf::RenderWindow::setTitle)
			.def("SetView", &sf::RenderWindow::setView)
			//.def("Show", &sf::RenderWindow::show)
			//.def("ShowMouseCursor", &sf::RenderWindow::showMouseCursor)
			;
		
		/*class_<DrawInterfaceWrap>("DrawInterface", init<boost::python::optional<int, bool> >())
			.def(init<const DrawInterface&>())
			.def("Draw", pure_virtual((void (DrawInterface::*)(sf::RenderWindow&))&DrawInterface::Draw))
			.def("Draw", pure_virtual((void (DrawInterface::*)(sf::RenderWindow&, sf::Shader&))&DrawInterface::Draw))
			.def("IsDrawing", &DrawInterface::IsDrawing)
			.def("SetDrawing", &DrawInterface::SetDrawing)
			.def("GetDrawPriority", &DrawInterface::GetDrawPriority)
			;
		class_<AnimatedDrawWrap, bases<DrawInterfaceWrap> >("AnimatedDraw", init<boost::python::optional<int, bool> >())
			.def(init<const AnimatedDraw&>())
			.def(init<const AnimatedDrawWrap&>())
			.def("Update", pure_virtual((void (AnimatedDraw::*)(const sf::Uint32, const float))&AnimatedDraw::Update))
			.def("Update", pure_virtual((void (AnimatedDraw::*)(const float, const float))&AnimatedDraw::Update))
			.def("GetPause", &AnimatedDraw::GetPause)
			.def("SetPause", &AnimatedDraw::SetPause)
			;*/
	}
}

#endif