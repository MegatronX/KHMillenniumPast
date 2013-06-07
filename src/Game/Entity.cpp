#include "Entity.h"
#include <boost/functional/hash.hpp>
namespace Game
{
	int Entity::EntityIDCounter = 0;
	boost::hash<std::string> Entity::StringHasher;

	const std::string Entity::InvalidPropertyText = "Invalid";

	Entity::Entity() : UID(-1), Type(0), Name("InvalidEntity"), Valid(false)
	{

	}
	Entity::Entity(const std::string& name, const int type, const int ID) : UID(ID), Type(type), Name(name), Valid(true)
	{
		auto hasher = boost::hash<std::string>();
		NameHash = hasher(Name);
	}
	Entity::Entity(const Entity& entity) : Name(entity.Name), Type(entity.Type), NameHash(entity.NameHash), FlagSet(entity.FlagSet), Valid(entity.Valid)
	{
		this->UID = EntityIDCounter++;
		ComponentCollection.rehash(entity.ComponentCollection.size());
		for (auto it = entity.ComponentCollection.begin(); it != entity.ComponentCollection.end(); ++it)
		{
			auto cl = it->second->Clone();
			auto temp = it->second;
			cl->SetOwner(this);
			ComponentCollection[it->first] = cl;//it->second->Clone();
		}
	}
	int Entity::GetID() const
	{
		return UID;
	}
	const std::string& Entity::GetName() const
	{
		return Name;
	}
	std::string Entity::GetNameByVal() const
	{
		return Name;
	}
	int Entity::GetNameHash() const
	{
		return NameHash;
	}
	int Entity::GetType() const
	{
		return Type;
	}
	bool Entity::IsType(int type)
	{
		return (Type & type) > 0;
	}
	Components::Component* Entity::GetComponent(const std::string& index)// const
	{
		boost::mutex::scoped_lock l(mtx);
		auto it = ComponentCollection.find(index);
		if (it != ComponentCollection.end())
			return it->second.get();
		return nullptr;
	}

	boost::shared_ptr<Components::Component> Entity::GetComponentSmartPtr(const std::string& index)
	{
		boost::mutex::scoped_lock l(mtx);
		auto it = ComponentCollection.find(index);
		if (it != ComponentCollection.end())
			return it->second;
		return boost::shared_ptr<Components::Component>();
	}

	bool Entity::HasComponent(const std::string& name) //const
	{
		return GetComponent(name) != nullptr;
	}
	bool Entity::RegisterComponent(const std::string& indexName, boost::shared_ptr<Components::Component> component, bool ReplaceExisting)
	{
		if (!ReplaceExisting && HasComponent(indexName) )
		{
			return false;
		}
		boost::mutex::scoped_lock l(mtx);
		ComponentCollection[indexName] = component;
		return true;
	}
	bool Entity::RemoveComponent(const std::string& indexName)
	{
		bool removed = false;
		auto it = ComponentCollection.find(indexName);
		if (it != ComponentCollection.end())
		{
			ComponentCollection.erase(it);
			removed = true;
		}
		return removed;
	}
	Entity::RawClonePtr Entity::RawClone() const
	{
		return new Entity(*this);
	}
	void Entity::AddFlag(const std::string& flag)
	{
		FlagSet.insert(flag);
	}
	bool Entity::HasFlag(const std::string& flag)
	{
		return FlagSet.find(flag) != FlagSet.end();
	}
	bool Entity::RemoveFlag(const std::string& flag)
	{
		bool Removed = false;
		auto it = FlagSet.find(flag);
		if (it != FlagSet.end())
		{
			FlagSet.erase(it);
			Removed = true;
		}
		return Removed;
	}

	void Entity::SetProperty(const std::string& name, const std::string& value, bool removeExisting)
	{
		if (removeExisting)
		{
			EntityProperties[name] = value;
		}
		else
		{
			auto it = EntityProperties.find(name);
			if (it == EntityProperties.end())
			{
				EntityProperties[name] = value;
			}
		}
	}
	bool Entity::HasPropery(const std::string& name) const
	{
		return EntityProperties.find(name) != EntityProperties.end();
	}
	bool Entity::RemoveProperty(const std::string& name)
	{
		bool removed = false;
		auto it = EntityProperties.find(name);
		if (it != EntityProperties.end())
		{
			EntityProperties.erase(it);
			removed = true;
		}

		return removed;
	}
	std::string InvalidProperty = "Invalid Property";
	const std::string& Entity::GetProperty(const std::string& name) const
	{
		auto it = EntityProperties.find(name);
		if (it != EntityProperties.end())
		{
			return it->second;
		}
		return InvalidPropertyText;
	}

	void Entity::ChangeName(const std::string& newName)
	{
		Name = newName;
	}
	bool Entity::operator==(const Entity& entity) const
	{
		return this->UID == entity.UID;
	}
	bool Entity::operator!=(const Entity& entity) const
	{
		return !(*this == entity);
	}
	Entity& Entity::operator=(const Entity& ref)
	{
		if (this != &ref)
		{
			this->Name = ref.Name;
			this->NameHash = ref.NameHash;
			this->Type = ref.Type;
			this->UID = EntityIDCounter++;
			this->FlagSet = ref.FlagSet;
			ComponentCollection.clear();
			ComponentCollection.rehash(ref.ComponentCollection.size());
			for (auto it = ref.ComponentCollection.begin(); it != ref.ComponentCollection.end(); ++it)
			{
				ComponentCollection[it->first] = it->second->Clone();
			}
		}
		return *this;
	}
	void Entity::AddType(int type)
	{
		Type |= type;
	}
	void Entity::RemoveType(int type)
	{
		if (IsType(type))
			Type = (Type & type) ^ type;
	}
	bool Entity::GetValid() const
	{
		return Valid;
	}
	void Entity::SetValid(const bool val)
	{
		Valid = val;
	}
	Entity::~Entity()
	{

	}
}