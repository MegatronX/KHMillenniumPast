#include "UseComponentWrap.h"
#include <battle/BattleField.h>
#include <memory>
#include <boost/intrusive_ptr.hpp>
using namespace boost::python;
namespace Game
{
	namespace Scripting
	{
		UseComponentWrap::UseComponentWrap(PyObject* self_, Entity* owner) : self(self_), UseComponent(owner)
		{

		}
		UseComponentWrap::UseComponentWrap(PyObject* self_, Entity* owner, const std::string& name, bool hasUse, bool hasBattleUse) : self(self_), 
			UseComponent(owner, name, hasUse, hasBattleUse)
		{

		}
		UseComponentWrap::UseComponentWrap(PyObject* self_, Entity* owner, bool HasUse, bool HasBattleUse) 
			: UseComponent(owner, HasUse, HasBattleUse), self(self_)
		{

		}
		UseComponentWrap::UseComponentWrap(PyObject* self_, const Components::UseComponent& cmp) : self(self_), Components::UseComponent(cmp)
		{

		}
		/*UseComponentWrap::UseComponentWrap(const Components::UseComponentWrap& cmp)
		{

		}*/
		bool UseComponentWrap::Use(Actions::Action* action)
		{
			return call_method<bool>(self, "Use", ptr(action));//, boost::ref(Targets));
		}
		bool UseComponentWrap::UseDefault(Actions::Action* action)
		{
			return this->UseComponent::Use(action);//(Users), (Targets));
		}
		bool UseComponentWrap::BattleUse(Actions::Action* action, Battle::BattleField* field)
		{
			return call_method<bool>(self, "BattleUse", ptr(action), ptr(field));
		}
		bool UseComponentWrap::BattleUseDefault(Actions::Action* action, Battle::BattleField* field)
		{
			return this->UseComponent::BattleUse(action, field);
		}
		Components::UseComponent::ClonePtr UseComponentWrap::Clone() const
		{
			//Components::UseComponent::ClonePtr res = call_method<Components::UseComponent::ClonePtr>(self, "Clone");
			//boost::shared_ptr<Components::Component> res = call_method<boost::shared_ptr<Components::Component> >(self, "Clone");
			//boost::shared_ptr<Components::Component> res = call_method<boost::shared_ptr<Components::Component> >(self, "Clone");
			return call_method<Components::UseComponent::ClonePtr>(self, "Clone");
			//int x = 10;
			//return nullptr;
		}
		Components::UseComponent::ClonePtr UseComponentWrap::CloneDefault() const
		{
			return this->Components::UseComponent::Clone();
		}
	}
}
