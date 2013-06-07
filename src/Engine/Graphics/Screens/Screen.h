#pragma once
#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <system/Input/InputInterface.h>
#include <Graphics/AnimatedDraw.h>
#include <Graphics/Sprites/SpriteInterface.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <boost/unordered_map.hpp>
#include <Graphics/DrawManager.h>
class Engine;
namespace Graphics
{
	namespace Screens
	{
		class ScreenStack;
		class Screen : public ::Input::InputInterface, public virtual AnimatedDraw, public virtual SpriteInterface, public Cloneable<Screen>
		{
		public:
			Screen(const std::string& name, ::Engine* engine, const int id);
			virtual ~Screen();
			int GetID() const;
			const std::string& GetScreenName() const;
			void SetScreenName(const std::string& name);

			bool AddOwner(const std::string& name, ScreenStack* stack);
			bool RemoveOwner(const std::string& name);
			bool HasOwner(const std::string& name);
			const boost::unordered_map<std::string, ScreenStack*>& GetOwners() const;
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
			virtual void Draw(sf::RenderTarget &window) override;
			virtual void Draw(sf::RenderTarget &window, sf::RenderStates states) override;
			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0);

			void AddToDrawList(const std::string& index, boost::shared_ptr<DrawInterface> drawable);
			void AddToUpdateList(const std::string& index, const int priority, boost::shared_ptr<Updater> updateable);

			virtual RawClonePtr RawClone() const override
			{
				return new Screen(*this);
			}
			/*virtual bool HandleKeyPressed(const sf::Uint32 time, const Input::InputModule* inputModule, Input::PlayerInput pInput, Input::InputAction& action) override;
			virtual bool HandleKeyReleased(const sf::Uint32 time, const Input::InputModule* inputModule, Input::PlayerInput pInput, Input::InputAction& action) override;

			//Animate Draw
			virtual void Update(const sf::Uint32 time, const float TimeScale = 1.0) override;
			virtual void Update(const float time, const float TimeScale = 1.0) override;

			virtual void Draw(sf::RenderWindow &window) override;
			virtual void Draw(sf::RenderWindow &window, sf::Shader &shader) override;*/

			bool operator==(const Screen& screen) const;
			bool operator!=(const Screen& screen) const;
		protected:
			Engine* engine;
		private:
			//DrawManager DManager;
			int ScreenID;
			std::string ScreenName;
			bool DrawScreen;
			bool UpdateScreen;
			bool InputsEnabled;
			sf::Uint32 LastUpdate;
			boost::unordered_map<std::string, ScreenStack*> OwningStacks;
			sf::Transform LocalTransform;

			std::map<int, boost::unordered_map<std::string, boost::shared_ptr<DrawInterface> > > DrawLists;
			std::map<int, boost::unordered_map<std::string, boost::shared_ptr<Updater> > > UpdateLists;

			friend class ScreenManager;
			//virtual bool HandleKeyPressed(const sf::Uint32 time, InputModule& inputModule, sf::Event::Key& keyEvent) = 0;
			//virtual bool HandleKeyReleased(const sf::Uint32 time, InputModule& inputModule, sf::Event::Key& keyEvent) = 0;
		};
		typedef boost::shared_ptr<Screen> screen_ptr;
	}
}


#endif