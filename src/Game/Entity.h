#pragma once
#ifndef _Entity_H_
#define _Entity_H_

#include <string>
#include <boost/functional.hpp>
#include <components/Component.h>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/thread/mutex.hpp>
namespace Game
{
	enum EntityTypes
	{
		ItemEntity = 1,
		CharacterEntity = 2,
		StatusEffectEntity = 4,
		AbilityEntity = 8,
		TileMapEntity = 16,
		ActionEntity = 32,
		PartyEntity = 64,
		BattlePartyEntity = 128,
		Battlefield = 256,
		Other = 1024
	};

	class Entity : public Cloneable<Entity> 
	{
	public:
		Entity();
		Entity(const std::string& name, const int type, const int ID = EntityIDCounter++);
		Entity(const Entity& entity);
		//Entity(const std::string& name, const std::string& type, const int ID = ++EntityIDCounter);
		int GetID() const;
		const std::string& GetName() const;
		std::string GetNameByVal() const;
		int GetNameHash() const;
		int GetType() const;
		bool IsType(int type);

		virtual Components::Component* GetComponent(const std::string& index);// const;
		template <typename T>
		T GetComponentAs(const std::string& name)// const
		{
			return dynamic_cast<T>(GetComponent(name));
		}
		//IMPORTANT: Not all components are accessible as SmartPtrs
		virtual boost::shared_ptr<Components::Component> GetComponentSmartPtr(const std::string& index);// const;
		template <typename T>
		boost::shared_ptr<T> GetComponentSmartPtrAs(const std::string& name)// const
		{
			return boost::dynamic_pointer_cast<T>(GetComponentSmartPtr(name));
		}

		bool HasComponent(const std::string& name); //const;
		bool RegisterComponent(const std::string& indexName, boost::shared_ptr<Components::Component> component, bool ReplaceExisting = true);
		bool RemoveComponent(const std::string& indexName);
		virtual RawClonePtr RawClone() const override;

		//Leave empty until use case arises
		bool DeleteComponent(const Components::Component* component);
		//Leave empty until use case arises
		bool DeleteComponent(const boost::shared_ptr<Components::Component>& component);

		void AddFlag(const std::string& flag);
		bool HasFlag(const std::string& flag);
		bool RemoveFlag(const std::string& flag);

		void SetProperty(const std::string& name, const std::string& value, bool removeExisting = true);
		bool HasPropery(const std::string& name) const;
		bool RemoveProperty(const std::string& name);
		const std::string& GetProperty(const std::string& name) const;

		bool operator==(const Entity& entity) const;
		bool operator!=(const Entity& entity) const;
		Entity& operator=(const Entity& entity);

		bool GetValid() const;
		void SetValid(const bool val);

		virtual ~Entity();

		const static std::string InvalidPropertyText;
	protected:
		void AddType(int type);
		void RemoveType(int type);
		void ChangeName(const std::string& newName);

		boost::unordered_map<std::string, boost::shared_ptr<Components::Component> > ComponentCollection;
		boost::unordered_set<std::string> FlagSet;
		boost::unordered_map<std::string, std::string> EntityProperties;
		static boost::hash<std::string> StringHasher;

	private:
		
		std::string Name;
		static int EntityIDCounter;
		int NameHash;
		int Type;
		int UID;
		boost::mutex mtx;
		bool Valid;
	};
	
}

#endif