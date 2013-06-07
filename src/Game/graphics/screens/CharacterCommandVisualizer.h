#pragma once
#ifndef _CHARACTERCOMMANDVIS_H_
#define _CHARACTERCOMMANDVIS_H_

#include <graphics/sprites/AnimatedSprite.h>
#include <character/BaseCharacter.h>
#include <system/Input/InputInterface.h>
#include <Engine.h>
namespace Game
{
	namespace Graphics
	{
		class CommandOption : public ::Graphics::AnimatedSpriteInterface
		{
		public:
			CommandOption(Engine* eng, const std::string& commandName, sf::Font& textFont, unsigned int fontSize, boost::shared_ptr<sf::Texture> baseTexture, boost::shared_ptr<sf::Texture> selectedTexture);
			//CommandOption(Engine* eng, const std::string& commandName, bool useTextImage, boost::shared_ptr<sf::Texture> baseTexture, boost::shared_ptr<sf::Texture> selectedTexture);
			void Draw(sf::RenderTarget& target);
			void Draw(sf::RenderTarget& target, sf::RenderStates states);
			void Update(const sf::Uint32 time, const float TimeScale = 1.f);
			bool GetValid() const;
			void SetValid(const bool value);
			void SetSelected(bool selected = true);
			void SetCommandName(const std::string& cName);
			const std::string& GetCommandName() const;

		protected:
			std::string CommandName;
			bool Valid;
			bool Selected;
			bool UseRawText;
			sf::Text OptionText;
			sf::Text OptionTextShadow;
			::Graphics::AnimatedSprite OptionBack;
			boost::shared_ptr<sf::Texture> BackTexture;
			boost::shared_ptr<sf::Texture> SelectedBackTexture;
			boost::shared_ptr<sf::Texture> TextValid;
			boost::shared_ptr<sf::Texture> TextInvalid;
		};

		class CommandOptionSet : public ::Graphics::AnimatedSpriteInterface, public ::Input::InputInterface
		{
		public:
			CommandOptionSet(Engine* engine, float defaultOffset = 10.f, float targetOffset = 50.f);
			CommandOptionSet(const std::vector<std::string>& optionNames);
			void AddOption(boost::shared_ptr<CommandOption> option);
			void SetOptionIndex(const int index);
			void Draw(sf::RenderTarget& target);
			void Draw(sf::RenderTarget& target, sf::RenderStates states);
			void Update(const sf::Uint32 time, const float TimeScale = 1.f);
			
			virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);
			virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);
		protected:
			int OptionIndex;
			Engine* Eng;
			
			std::vector<boost::shared_ptr<CommandOption> > Options;
			float DefaultOffset;// = 10.f;
			float TargetOffset;
		};
		class CharacterCommandVisualizer : public ::Input::InputInterface, public ::Graphics::AnimatedSpriteInterface
		{
		public:
			CharacterCommandVisualizer(::Input::PlayerInput activeOnPlayer = ::Input::P1Input);
			virtual void SetCharacter(Character::BaseCharacter* character);
			virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);
			virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult);

		protected:
			Character::BaseCharacter* Character;
			boost::unordered_set<::Input::PlayerInput> ActiveOnPlayers;
			int SetIndex;
			std::vector<boost::shared_ptr<CommandOptionSet>> OptionSets;
			
		};
		class StandardCharacterCommandVisualizer : public CharacterCommandVisualizer
		{
		public:
			StandardCharacterCommandVisualizer(Engine* eng) : Eng(eng), BackgroundImage(eng->GetContentManager().RequestTexture("MainCommandBack", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime())),
				CommandHeader(eng->GetContentManager().RequestTexture("CommandHeader", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime()))
			{
				auto optionSet = boost::make_shared<CommandOptionSet>(eng);
				auto texture = eng->GetContentManager().RequestTexture("Option", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime());
				auto textureSel = eng->GetContentManager().RequestTexture("HighlightedOption", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, eng->GetTime());
				auto font = eng->GetContentManager().RequestFont("EurostileExt-Bo", eng->GetTime());
				
				std::string opts[] = {"Attack", "Magic", "Skills", "Items"};
				for (int i = 0; i < 4; ++i)
				{
					auto option = boost::make_shared<CommandOption>(eng, opts[i], *font, 22, texture, textureSel);
					optionSet->AddOption(option);
					option->SetPosition(10, 50 + 28 * i);
				}
				OptionSets.push_back(optionSet);
				optionSet->SetOptionIndex(0);
				SetIndex = 0;

				//auto option = boost::make_shared<CommandOption>();
			}
			virtual void SetCharacter(Character::BaseCharacter* character) override
			{
				Character = character;
				OptionSets.clear();
				auto optionSet = boost::make_shared<CommandOptionSet>(Eng);
				auto texture = Eng->GetContentManager().RequestTexture("Option", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, Eng->GetTime());
				auto textureSel = Eng->GetContentManager().RequestTexture("HighlightedOption", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, Eng->GetTime());
				auto font = Eng->GetContentManager().RequestFont("EurostileExt-Bo", Eng->GetTime());
				std::string opts[] = {"Attack", "Magic", "Skills", "Items"};
				for (int i = 0; i < 4; ++i)
				{
					auto option = boost::make_shared<CommandOption>(Eng, opts[i], *font, 22, texture, textureSel);
					optionSet->AddOption(option);
					option->SetPosition(10, 50 + 28 * i);
				}
				OptionSets.push_back(optionSet);
				optionSet->SetOptionIndex(0);
				SetIndex = 0;
			}
			void Draw(sf::RenderTarget& target)
			{
				sf::RenderStates states;
				states.transform = GetTransform();
				BackgroundImage.Draw(target, states);
				for (auto it = OptionSets.begin(); it != OptionSets.end(); ++it)
				{
					
					(*it)->Draw(target, states);
				}
				CommandHeader.Draw(target, states);
			}
			void Draw(sf::RenderTarget& target, sf::RenderStates states)
			{
				states.transform *= GetTransform();
				BackgroundImage.Draw(target, states);
				for (auto it = OptionSets.begin(); it != OptionSets.end(); ++it)
				{
					(*it)->Draw(target, states);
				}
				CommandHeader.Draw(target, states);
			}
			void Update(const sf::Uint32 time, const float TimeScale = 1.f)
			{
				BackgroundImage.Update(time, TimeScale);
				for (auto it = OptionSets.begin(); it != OptionSets.end(); ++it)
				{
					(*it)->Update(time, TimeScale);
				}
				CommandHeader.Update(time, TimeScale);
			}
		protected:
			Engine* Eng;
			::Graphics::AnimatedSprite CommandHeader;
			::Graphics::AnimatedSprite BackgroundImage;
		};
		/*class CommandOptionsVisualizer
		{
		public:
		protected:
		};
		class CommandPanelOption : public ::Graphics::SpriteInterface, public ::Graphics::Updater
		{
		public:
			CommandPanelOption(const std::string& commandName, boost::shared_ptr<sf::Texture> txPtr, const sf::Vector2f& panelSize, sf::Font& txtFont, unsigned int fontSize = 30U, const sf::Vector2f& txtOffset = sf::Vector2f(0.f, 0.f)) :
				CommandName(commandName), BgSprite(txPtr), NormalText(commandName, txtFont, fontSize), UseNormalText(true), Valid(!commandName.empty())
			{
				//Size bg
				if (txPtr.get() != nullptr)
				{
					sf::Vector2f TargetScale(panelSize.x / txPtr->getSize().x, panelSize.y / txPtr->getSize().y);
					BgSprite.SetScale(TargetScale);
				}
				NormalText.setPosition(txtOffset);
			}
			CommandPanelOption(const std::string& commandName, boost::shared_ptr<sf::Texture> txPtr, const ::Graphics::SpriteImportData& bgDesc, const sf::Vector2f& panelSize, sf::Font& txtFont, unsigned int fontSize = 30U, const sf::Vector2f& txtOffset = sf::Vector2f(0.f, 0.f)) :
				CommandName(commandName), BgSprite(txPtr, bgDesc), NormalText(commandName, txtFont, fontSize), UseNormalText(true), Valid(!commandName.empty())
			{
				//Size bg
				if (txPtr.get() != nullptr)
				{
					sf::Vector2f TargetScale(panelSize.x / txPtr->getSize().x, panelSize.y / txPtr->getSize().y);
					BgSprite.SetScale(TargetScale);
				}
				NormalText.setPosition(txtOffset);
			}
			CommandPanelOption(const std::string& commandName, boost::shared_ptr<sf::Texture> txPtr, const sf::Vector2f& panelSize, boost::shared_ptr<sf::Texture> textTxPtr, float fontHeight = 30.f, const sf::Vector2f& txtOffset = sf::Vector2f(0.f, 0.f)) :
				CommandName(commandName), BgSprite(txPtr), StylizedText(textTxPtr), UseNormalText(false), Valid(!commandName.empty())
			{
				//Size bg
				if (txPtr.get() != nullptr)
				{
					sf::Vector2f TargetScale(panelSize.x / txPtr->getSize().x, panelSize.y / txPtr->getSize().y);
					BgSprite.SetScale(TargetScale);
				}
				NormalText.setPosition(txtOffset);
			}
			CommandPanelOption(const std::string& commandName, boost::shared_ptr<sf::Texture> txPtr, const ::Graphics::SpriteImportData& bgDesc, const sf::Vector2f& panelSize, boost::shared_ptr<sf::Texture> textTxPtr, const ::Graphics::SpriteImportData& txtDesc, float fontHeight = 30.f, const sf::Vector2f& txtOffset = sf::Vector2f(0.f, 0.f)) :
				CommandName(commandName), BgSprite(txPtr, bgDesc), StylizedText(textTxPtr, txtDesc), UseNormalText(false), Valid(!commandName.empty())
			{
				//Size bg
				if (txPtr.get() != nullptr)
				{
					sf::Vector2f TargetScale(panelSize.x / txPtr->getSize().x, panelSize.y / txPtr->getSize().y);
					BgSprite.SetScale(TargetScale);
				}
				NormalText.setPosition(txtOffset);
			}
			void Draw(sf::RenderTarget& target) override
			{
				sf::RenderStates states;
				states.transform = GetTransform();
				BgSprite.Draw(target, states);
				if (UseNormalText)
					target.draw(NormalText, states);
				else
					StylizedText.Draw(target, states);
			}
			void Draw(sf::RenderTarget& target, sf::RenderStates states) override
			{
				states.transform *= GetTransform();
				BgSprite.Draw(target, states);
				if (UseNormalText)
					target.draw(NormalText, states);
				else
					StylizedText.Draw(target, states);
			}
			void Update(const sf::Uint32 time, const float timeScale = 1.f) override
			{
				BgSprite.Update(time, timeScale);

			}
			void SetCommandText(const std::string& cmdtxt)
			{
				CommandName = cmdtxt;
				Valid = !CommandName.size();
			}
			::Graphics::AnimatedSprite BgSprite;
			::Graphics::AnimatedSprite StylizedText;
			sf::Text NormalText;
			bool UseNormalText;
			std::string CommandName;
			bool Valid;
		};
		class CommandPanelSet : public ::Graphics::SpriteInterface, public ::Graphics::Updater
		{
		public:
			CommandPanelSet(const std::vector<std::string>& commands = std::vector<std::string>()) : SelectedIndex(-1)
			{
				int i = 0;
				for (auto opt = commands.begin(); opt != commands.end(); ++opt)
				{
					AddPanel(*opt);
				}
			}
			virtual void AddPanel(const std::string& option)
			{


			}
			void Draw(sf::RenderTarget& target) override
			{
				sf::RenderStates states;
				states.transform = GetTransform();
				for (auto it = CommandOptions.begin(); it != CommandOptions.end(); ++it)
				{
					(*it)->Draw(target, states);
				}
			}
			void Draw(sf::RenderTarget& target, sf::RenderStates states) override
			{
				states.transform *= GetTransform();
				for (auto it = CommandOptions.begin(); it != CommandOptions.end(); ++it)
				{
					(*it)->Draw(target, states);
				}
			}
			void Update(const sf::Uint32 time, const float timeScale = 1.f) override
			{
				for (auto it = CommandOptions.begin(); it != CommandOptions.end(); ++it)
				{
					(*it)->Update(time, timeScale);
				}
			}
			int GetSelectedIndex() const
			{
				return SelectedIndex;
			}
			void SetIndex(const int newIndex)
			{
				if (newIndex != SelectedIndex)
				{

				}
			}
		protected:
			int SelectedIndex;
			std::vector<boost::shared_ptr<CommandPanelOption> > CommandOptions;
		};
		class CommandVisualizer : public ::Graphics::SpriteInterface, public ::Graphics::Updater, public ::Input::InputInterface
		{
		public:
			CommandVisualizer() : ActiveOnPlayer(::Input::P1Input), PanelIndex(0), PanelSetIndex(0)
			{

			}
			Character::BaseCharacter* GetCharacter() const
			{
				return CharacterVis;
				
			}
			virtual void SetCharacter(Character::BaseCharacter* ch)
			{
				CharacterVis = ch;
				std::string leftOpts[2] = {"Defend", "Run"};
				std::string centerOpts[4] = {"Attack", "Magic", "Skill", "Item"};
				std::string rightOpts[3] = {"Summon", "Limit"};

			}
			virtual bool HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
			{
				if (actionResult.PInput == ActiveOnPlayer)
				{
					if (actionResult.IAction == ::Input::Left)
					{

					}
					else if (actionResult.IAction == ::Input::Right)
					{

					}
					else if (actionResult.IAction == ::Input::Up)
					{

					}
					else if (actionResult.IAction == ::Input::Down)
					{

					}
				}
			}
			virtual bool HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
			{

			}
		protected:
			std::vector<CommandPanelSet> CommandSets;
			std::vector<std::vector<boost::shared_ptr<CommandPanelOption> > > CommandOptions;
			unsigned int PanelSetIndex;
			unsigned int PanelIndex;
		private:
			::Input::PlayerInput ActiveOnPlayer;
			sf::Vector2f ActiveOptionSlide;
			::Graphics::AnimatedSprite VisBackground;
			Character::BaseCharacter* CharacterVis;

		};

		//Standard Command Vis
		class StandardCommandPanelOption : public CommandPanelOption
		{
		public:
		protected:
			
		private:
		};

		class StandardCommandVisualizer : public CommandVisualizer
		{
		public:
			StandardCommandVisualizer()
			{

			}
			virtual void SetCharacter(Character::BaseCharacter* ch) override
			{
				CommandVisualizer::SetCharacter(ch);
			}
			void Draw(sf::RenderTarget& target) override
			{
				sf::RenderStates states;
				states.transform = GetTransform();
				for (auto it = CommandOptions.begin(); it != CommandOptions.end(); ++it)
				{
					(*it)->Draw(target, states);
				}
			}
			void Draw(sf::RenderTarget& target, sf::RenderStates states) override
			{
				states.transform *= GetTransform();
				for (auto it = CommandOptions.begin(); it != CommandOptions.end(); ++it)
				{
					(*it)->Draw(target, states);
				}
			}
			void Update(const sf::Uint32 time, const float timeScale = 1.f) override
			{
				for (auto it = CommandOptions.begin(); it != CommandOptions.end(); ++it)
				{
					(*it)->Update(time, timeScale);
				}
			}
		protected:
			
		private:
		};*/
	}
}


#endif