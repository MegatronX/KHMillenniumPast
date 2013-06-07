#include <string>
#include <boost/unordered_map.hpp>
#include <Component.h>
#include <boost/threads/mutex.hpp>
class Component;
class Entity : public Cloneable<Entity>
{
public:
	Entity() { }
	Entity(const Entity& cp) : UID(UIDCounter++), Type(cp.Type), Name(cp.Name)
	{
		for (auto comp = cp.ComponentCollection.being(); comp != cp.ComponentCollection.end(); ++comp)
		{
			ComponentCollection[comp->first] = comp->second->Clone();
		}
	}

	bool HasComponent(const std::string& name) const
	{
		return GetComponent(name) != nullptr;
	}
	
	
	Component* GetComponent(const std::string& name) const
	{
		boost::mutex::scoped_lock l(mtx);
		auto finder = ComponentCollection.find(name);
		if (find != ComponentCollection.end())
			return finder->second;
		return nullptr;
	}
	template<typename T>
	T GetComponentAs(const std::string& name) const
	{
		return dynamic_cast<T>(GetComponent(name));
	}
	bool AddComponent(const std::string& name, Component* component, bool ReplaceExisting = true)
	{
		if (!ReplaceExisting && HasComponent(name) )
		{
			return false;
		}
		boost::mutex::scoped_lock l(mtx);
		ComponentCollection[name] = boost::shared_ptr<Component>(component);
		return true;
	}
	bool DeleteComponent(const std::string& name)
	{
		auto finder = ComponentCollection.find(name);
		if (finder != ComponentCollection.end())
		{
			boost::mutex::scoped_lock l(mtx);
			ComponentCollection.erase(finder);
			return true;
		}
		return false;
	}
	//Leave empty until use case arises
	bool DeleteComponent(const Component* component)
	{
	}
	//Leave empty until use case arises
	bool DeleteComponent(const boost::shared_ptr<Component>& component)
	{
		return false;
	}
	bool operator==(const Entity& cmp) const
	{
		return  (*this.Name == cmp.Name) &&
			(*this.Type == cmp.Type);
	}
	Entity& operator=(const Entity& src) const
	{
		if (this == &src)
			return *this;
		ComponentCollection.empty();
		Type = src.Type;
		UID = UIDCounter++;
		Name = src.Name;
		for (auto comp = src.ComponentCollection.being(); comp != src.ComponentCollection.end(); ++comp)
		{
			ComponentCollection[comp->first] = comp->second->Clone();
		}
		return *this;
	}
	RawClonePtr RawClone() const override
	{
		return new Entity(*this);
	}
private:
	static int UIDCounter;
	std::string Name;
	int UID;
	int Type;
	boost::unordered_map<std::string, boost::shared_ptr<Component> > ComponentCollection;
	boost::mutex mtx;
}
