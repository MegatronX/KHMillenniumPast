#include "Component.h"
namespace Game
{
	namespace Components
	{
		boost::hash<std::string> Component::StringHash = boost::hash<std::string>();
		int Component::ComponentIDCounter = 0;
		Component::Component() : UID(-1), ComponentType(-1), Valid(false)
		{

		}
		Component::Component(Entity* Owner) : UID(-1), ComponentType(-1), Valid(false), Owner(Owner)
		{

		}
		Component::Component(Entity* Owner, bool valid, const int id) : UID(valid ? -1 : id), ComponentType(0), NameHash(0), Valid(valid), Owner(Owner)
		{

		}
		Component::Component(Entity* Owner, const std::string& name, int type, bool valid, const int id) : Name(name), NameHash(StringHash(name)), ComponentType(type), UID(id), Valid(valid), Owner(Owner)
		{

		}
		Component::Component(Entity* Owner, const std::string& name, const std::string& type, bool valid, const int id) : Name(name), NameHash(StringHash(name)), ComponentType(StringHash(type)), UID(id), Valid(valid), Owner(Owner)
		{

		}
		Component::Component(const Component& comp) : Name(comp.Name), NameHash(comp.NameHash), ComponentType(comp.ComponentType), Valid(comp.Valid), Owner(comp.Owner), UID(++ComponentIDCounter)
		{

		}
		/*Component::Component(const Component& ref)
		{
			this->ComponentType = ref.ComponentType;
			this->Name = ref.Name;
			this->NameHash = ref.NameHash;
			this->UID = ref.UID;
			this->Valid = ref.Valid;
		}*/
		bool Component::IsValid() const
		{
			return Valid;
		}
		bool Component::IsType(const int type)
		{
			return type == ComponentType;
		}
		bool Component::IsType(const std::string& typeName)
		{
			return IsType(StringHash(typeName));
		}
		int Component::GetUID() const
		{
			return UID;
		}
		const std::string& Component::GetName() const
		{
			return Name;
		}
		std::string Component::GetNameByVal() const
		{
			return Name;
		}
		int Component::GetNameHash() const
		{
			return NameHash;
		}
		int Component::GetComponentType() const
		{
			return ComponentType;
		}
		Component::RawClonePtr Component::RawClone() const
		{
			return new Component(*this);
		}
		bool Component::operator==(const Component& cmp) const
		{
			return this->UID == cmp.UID;
		}
		bool Component::operator!=(const Component& cmp) const
		{
			return !(*this == cmp);
		}
		Component& Component::operator=(const Component& cmp)
		{
			if ((*this) == cmp)
				return *this;
			ComponentType = cmp.ComponentType;
			Name = cmp.Name;
			NameHash = cmp.NameHash;
			UID = ++ComponentIDCounter;
			Valid = cmp.Valid;
			Owner = cmp.Owner;
			Valid = cmp.Valid;
			return *this;
		}
		void Component::SetValid(bool val)
		{
			Valid = val;
		}
		Entity* Component::GetOwner() const
		{
			return Owner;
		}
		void Component::SetOwner(Entity* owner)
		{
			Owner = owner;
		}
		void Component::SetOwnerAndName(Entity* owner, const std::string& name)
		{

		}
		Component::~Component()
		{

		}
	}
}