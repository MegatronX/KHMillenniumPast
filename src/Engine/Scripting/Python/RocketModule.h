#pragma once
#ifndef _ROCKETMODULE_H_
#define _ROCKETMODULE_H_
#include "ScriptHelpers.h"
#include "ElementTransformWrap.h"
#include <Rocket/Controls.h>
#include <Rocket/Core.h>
#include <Graphics/Rocket/ElementTransformer.h>
#include <Graphics/Rocket/ElementTransformInterface.h>
#include <Graphics/Rocket/FaderTransform.h>
#include <Graphics/Rocket/PositionTransformer.h>
#include <Graphics/Rocket/FaderTransform.h>
//#include <Utilities/boost_function_python.h>
using namespace Graphics;
using namespace Graphics::GameRocket;
using namespace Rocket::Core;
namespace Scripting
{

	//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(GetInnerRMLOverload, GetInnerRML, 0, 1)
	//Rocket::Core::String (Element::*GetInnerRMLBlank)() const = &Element::GetInnerRML;
	//void (Element::*GetInnterRMLByString)(Rocket::Core::String&) const = &Element::GetInnerRML;
	struct transformation_finished_wrapped
	{
		transformation_finished_wrapped(boost::python::object callable) : _callable(callable)
		{
			
		}

		void operator()(sf::Uint32 time, ElementTransformationInterface* src)
		{
			call<void>(_callable.ptr(), time, boost::python::ptr(src));
			//PyGILState_STATE gstate = PyGILState_Ensure();
			//_callable(time, src);//time, src);
			//PyGILState_Release( gstate );
		}

		boost::python::object _callable;
	};

	void createTranformationFinishedEvent(ElementTransformationInterface* src, boost::python::object function)
	{
		
		if (src != nullptr)
			src->AddFinishedEvent(boost::function<void (sf::Uint32, ElementTransformationInterface*)>(transformation_finished_wrapped(function)));
	}

	BOOST_PYTHON_MODULE(RocketModule)
	{
		/*class_<Rocket::Core::ElementDocument, boost::noncopyable>("ElementDocument")
			;*/
		//typedef Rocket::Core::Property::Get<int> GetAsInt;
		//def_function<void (sf::Uint32 time, ElementTransformationInterface*)>("TransformationCompletedSignal", "Transformation signal");
		class_<Rocket::Core::Property>("Property")
			/*.def("GetAsInt", GetAsInt)
			.def("", &Rocket::Core::Property:)
			.def("", &Rocket::Core::Property:)
			.def("", &Rocket::Core::Property:)
			.def("", &Rocket::Core::Property:)
			.def("", &Rocket::Core::Property:)
			.def("", &Rocket::Core::Property:)
			.def("", &Rocket::Core::Property:)
			.def("", &Rocket::Core::Property:)*/
			//.def("GetAsInt", &Property::Get<int>, return_value_policy<copy_const_reference>())
			;
		class_<String>("RocketString")
			.def(init<>())
			.def(init<const char*>())
			.def(init<const String&>())
			.def("CString", &String::CString)
			/*.def("Clear", &String::Clear)
			.def("CString", &String::CString, return_value_policy<reference_existing_object>())
			.def("Empty", &String::Empty)
			.def("Length", &String::Length)*/
			//.def("__eq__", &String::operator==)
			//.def("__neq__", &String::operator!=)
			/*.def(self + self)
			.def(self += self)
			.def(self != self)
			.def(self == self)
			.def(self < self)*/
			;
		class_<Vector2f>("RVector2f", init<>())
			.def(init<float, float>())
			.def_readwrite("x", &Vector2f::x)
			.def_readwrite("y", &Vector2f::y)
			.def("DotProduct", &Vector2f::DotProduct)
			.def("Magnitude", &Vector2f::Magnitude)
			.def("Normalise", &Vector2f::Normalise)
			.def("Rotate", &Vector2f::Rotate)
			.def("SquaredMagnitude", &Vector2f::SquaredMagnitude)
			.def(-self)
			.def(self * float())
			.def(self / float())
			.def(self + self)
			.def(self += self)
			.def(self -= self)
			.def(+self)
			//.def("", &Vector2f::)
			;
		
		class_<Element>("Element", init<const String&>())
			//.def()
			.def(init<const Element&>())
			.def("AppendChild", &Element::AppendChild, (boost::python::arg("dom_element") = true))
			.def("Blur", &Element::Blur)
			.def("Click", &Element::Click)
			.def("Clone", &Element::Clone, return_value_policy<manage_new_object>())
			.def("DumpLeakReport", &Element::DumpLeakReport)
			.def("Focus", &Element::Focus)
			.def("GetAbsoluteLeft", &Element::GetAbsoluteLeft)
			.def("GetAbsoluteOffset", &Element::GetAbsoluteOffset)
			.def("GetAbsoluteTop", &Element::GetAbsoluteTop)
			.def("GetChild", &Element::GetChild, return_value_policy<reference_existing_object>())
			.def("GetClientHeight", &Element::GetClientHeight)
			.def("GetClientLeft", &Element::GetClientLeft)
			.def("GetClientTop", &Element::GetClientTop)
			.def("GetClientWidth", &Element::GetClientWidth)
			.def("GetElementById", &Element::GetElementById, return_value_policy<reference_existing_object>())
			.def("GetFirstChild", &Element::GetFirstChild, return_value_policy<reference_existing_object>())
			.def("GetId", &Element::GetId, return_value_policy<reference_existing_object>())
			//.def("GetInnerRML", &Element::GetInnerRML, GetInnerRMLOverload())
			.def("GetInnerRML", (Rocket::Core::String (Element::*)() const)&Element::GetInnerRML)
			//.def("GetInnterRML", &GetInnterRMLByString)
			//.def("GetInnerRML", &Element::GetInnerRML, arg())
			.def("GetLastChild", &Element::GetLastChild, return_value_policy<reference_existing_object>())
			.def("GetLocalProperty", &Element::GetLocalProperty, return_value_policy<reference_existing_object>())
			.def("GetNextSibling", &Element::GetNextSibling, return_value_policy<reference_existing_object>())
			.def("GetNumAttributes", &Element::GetNumAttributes)
			.def("GetNumChildren", &Element::GetNumChildren)
			.def("GetOffsetHeight", &Element::GetOffsetHeight)
			.def("GetOffsetLeft", &Element::GetOffsetLeft)
			.def("GetOffsetParent", &Element::GetOffsetParent, return_value_policy<reference_existing_object>())
			.def("GetOffsetTop", &Element::GetOffsetTop)
			.def("GetOffsetWidth", &Element::GetOffsetWidth)
			.def("GetOwnerDocument", &Element::GetOwnerDocument, return_value_policy<reference_existing_object>())
			.def("GetParentNode", &Element::GetParentNode, return_value_policy<reference_existing_object>())
			.def("GetPreviousSibling", &Element::GetPreviousSibling, return_value_policy<reference_existing_object>())
			//.def("GetProperty", &Element::GetProperty, return_value_policy<reference_existing_object>())
			//.def("GetPropertyAsInt", &Element::GetProperty<int>, return_value_policy<reference_existing_object>())
			.def("GetScrollHeight", &Element::GetScrollHeight)
			.def("GetScrollLeft", &Element::GetScrollLeft)
			.def("GetScrollTop", &Element::GetScrollTop)
			.def("GetScrollWidth", &Element::GetScrollWidth)
			//.def("GetStyle", &Element::GetStyle, return_value_policy<reference_existing_object>())
			//.def("GetStyleSheet", &Element::GetStyleSheet, return_value_policy<reference_existing_object>())
			.def("GetTagName", &Element::GetTagName, return_value_policy<reference_existing_object>())
			.def("GetZIndex", &Element::GetZIndex)
			.def("HasAttribute", &Element::HasAttribute)
			.def("HasChildNodes", &Element::HasChildNodes)
			//.def("InsertBefore", &Element::InsertBefore)
			.def("IsClassSet", &Element::IsClassSet)
			.def("IsClippingEnabled", &Element::IsClippingEnabled)
			.def("IsPointWithinElement", &Element::IsPointWithinElement)
			.def("IsPseudoClassSet", &Element::IsPseudoClassSet)
			.def("IsVisible", &Element::IsVisible)
			.def("RemoveAttribute", &Element::RemoveAttribute)
			.def("RemoveChild", &Element::RemoveChild)
			.def("RemoveProperty", &Element::RemoveProperty)
			//.def("ConvertCoords", (sf::Vector2f (sf::RenderWindow::*)(const sf::Vector2i&) const)&sf::RenderWindow::convertCoords)
			//.def("Draw", (void (sf::RenderWindow::*)(const sf::Drawable&, const sf::RenderStates&))&sf::RenderWindow::draw, (boost::python::arg("states") = sf::RenderStates::Default))
			.def("SetProperty", (bool (Element::*)(const Rocket::Core::String&, const Rocket::Core::String&))&Element::SetProperty)
			.def("SetProperty", (bool (Element::*)(const Rocket::Core::String&, const Rocket::Core::Property&))&Element::SetProperty)
			.def("ScrollIntoView", &Element::ScrollIntoView)
			.def("SetScrollLeft", &Element::SetScrollLeft)
			.def("SetScrollTop", &Element::SetScrollTop)
			.def("SetClass", &Element::SetClass)
			.def("SetClassNames", &Element::SetClassNames)
			.def("SetId", &Element::SetId)
			.def("SetInnerRML", &Element::SetInnerRML)
			.def("SetOffset", &Element::SetOffset)
			.def("Update", &Element::Update)
			.def("UpdateLayout", &Element::UpdateLayout)
			;
		class_<ElementDocument, bases<Element> >("ElementDocument", no_init)
			.def("CreateElement", &ElementDocument::CreateElement, return_value_policy<manage_new_object>())
			.def("CreateTextNode", &ElementDocument::CreateTextNode, return_value_policy<manage_new_object>())
			.def("CreateElementUnmanaged", &ElementDocument::CreateElement, return_value_policy<reference_existing_object>())
			.def("CreateTextNodeUnmanaged", &ElementDocument::CreateTextNode, return_value_policy<reference_existing_object>())
			.def("GetElementById", &ElementDocument::GetElementById, return_value_policy<reference_existing_object>())
			/*.def("", &ElementDocument:)
			.def("", &ElementDocument:)
			.def("", &ElementDocument:)
			.def("", &ElementDocument:)
			.def("", &ElementDocument:)
			.def("", &ElementDocument:)*/
			;
		class_<ElementTransformationInterface, boost::shared_ptr<ElementTransformationInterfaceWrap>, boost::noncopyable >("ElementTransformationInterface", init<ElementTransformer*, const sf::Uint32, const sf::Uint32>())
			//.def(init<const ElementTransformationInterface&>())
			.def("ReInitialize", &ElementTransformationInterface::ReInitialize, &ElementTransformationInterfaceWrap::ReInitializeDefault)
			.def("Update", &ElementTransformationInterface::Update, &ElementTransformationInterfaceWrap::UpdateDefault)
			.def("AddPostTransform", &ElementTransformationInterface::AddPostTransform)
			.def("AddTimedTransform", &ElementTransformationInterface::AddTimedTransform)
			.def("IsFinished", &ElementTransformationInterface::IsFinished)
			.def("AddFinishedEvent", &createTranformationFinishedEvent, (boost::python::arg("src"), boost::python::arg("function")))
			;
		class_<FaderTransform, boost::shared_ptr<FaderTransform>, bases<ElementTransformationInterface> >("FaderTransform", init<ElementTransformer*, const sf::Uint8, const sf::Uint8, const sf::Uint32, const sf::Uint32>())
			//.def()
			.def("FullReInitialize", &FaderTransform::FullReInitialize)
			;
		
		/*class_<TimedTransform, bases<ElementTransformationInterface> >("TimedTransform", init<boost::shared_ptr<ElementTransformationInterface>&, const sf::Uint32, const sf::Uint32>())
			.def_readwrite("ActivationTime", &TimedTransform::ActivationTime)
			.def_readwrite("Transform", &TimedTransform::Transform)
			.def_readwrite("Duration", &TimedTransform::TransDuration)
			;*/

		class_<PositionTransformer, boost::shared_ptr<PositionTransformer>, bases<ElementTransformationInterface> >("PositionTransform", init<ElementTransformer*, sf::Vector2f&, const sf::Uint32, sf::Uint32>())
			.def("FullReInitialize", &PositionTransformer::FullReInitialize)
			;
		
		class_<ElementTransformer, boost::shared_ptr<ElementTransformer>, boost::noncopyable>("ElementTransformer", init<boost::python::optional<Element*> >())
			.def(init<std::vector<ElementTransformationInterface*>&, boost::python::optional<Rocket::Core::Element*> >())
			.def(init<std::vector< boost::shared_ptr<ElementTransformationInterface> >&>())
			.def("GetTarget", &ElementTransformer::GetTarget, return_value_policy<reference_existing_object>())
			.def("SetTarget", &ElementTransformer::SetTarget)
			.def("Update", &ElementTransformer::Update)
			.def("AddTransformation", &ElementTransformer::AddTransformation)
			;
	}
}

#endif