#include "ElementTransformWrap.h"
using namespace boost::python;
using namespace Graphics::GameRocket;
namespace Scripting 
{
	ElementTransformationInterfaceWrap::ElementTransformationInterfaceWrap(PyObject* self_) 
		: self(self_), ElementTransformationInterface(nullptr, 0, 0)
	{

	}
	ElementTransformationInterfaceWrap::ElementTransformationInterfaceWrap(PyObject* self_, ElementTransformer* target, const sf::Uint32 currentTime, const sf::Uint32 EndTime_)
		: self(self_), ElementTransformationInterface(target, currentTime, EndTime_)
	{

	}
	void ElementTransformationInterfaceWrap::ReInitialize(const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* holder)
	{
		return call_method<void>(self, "ReInitialize", currentTime, EndTime_, ptr(holder));
	}
	void ElementTransformationInterfaceWrap::Update(ElementTransformer* target, const sf::Uint32 time)
	{
		return call_method<void>(self, "Update", ptr(target), time);
	}
	void ElementTransformationInterfaceWrap::ReInitializeDefault(const sf::Uint32 currentTime, const sf::Uint32 EndTime_, ElementTransformer* holder)
	{
		return ElementTransformationInterface::ReInitialize(currentTime, EndTime_, holder);
	}
	void ElementTransformationInterfaceWrap::UpdateDefault(ElementTransformer* target, const sf::Uint32 time)
	{
		return ElementTransformationInterface::Update(target, time);
	}
}