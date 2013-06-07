#pragma once
#ifndef _GAMECOMPONENT_H_
#define _GAMECOMPONENT_H_
#include <string>
#include <boost/functional/hash.hpp>
#include <Utilities/Cloneable.h>

namespace Game
{
	namespace Battle
	{
		class Mechanics;
	}
	class Entity;
	namespace Components
	{
		class Component : public Cloneable<Component>
		{
		public:
			Component();
			Component(Entity* Owner);
			Component(Entity* Owner, bool valid, const int id = ++ComponentIDCounter);
			Component(Entity* Owner, const std::string& name, int type, bool valid = true, const int id = ++ComponentIDCounter);
			Component(Entity* Owner, const std::string& name, const std::string& type, bool valid = true, const int id = ++ComponentIDCounter);
			Component(const Component& comp);
		//	Component(const Component& ref);
			bool IsValid() const;
			void SetValid(bool val);
			bool IsType(const int type);
			bool IsType(const std::string& typeName);
			int GetUID() const;
			const std::string& GetName() const;
			std::string GetNameByVal() const;
			int GetNameHash() const;
			int GetComponentType() const;

			Entity* GetOwner() const;

			virtual RawClonePtr RawClone() const;

			bool operator==(const Component& cmp) const;
			bool operator!=(const Component& cmp) const;
			Component& operator=(const Component& cmp);

			void SetOwner(Entity* owner);
			void SetOwnerAndName(Entity* owner, const std::string& name);

			virtual ~Component();
		protected:
			
			friend class Entity;
			friend class Battle::Mechanics;
		private:
			static boost::hash<std::string> StringHash;
			static int ComponentIDCounter;// = 0;
			int ComponentType;
			std::string Name;
			int NameHash;
			int UID;
			bool Valid;
			Entity* Owner;
		};
	}
}

#endif