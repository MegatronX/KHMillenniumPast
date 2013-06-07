#include "CharacterCommandVisualizer.h"

namespace Game
{
	namespace Graphics
	{
		CommandOption::CommandOption(Engine* eng, const std::string& commandName, sf::Font& textFont, unsigned int fontSize, boost::shared_ptr<sf::Texture> baseTexture, boost::shared_ptr<sf::Texture> selectedTexture) : BackTexture(baseTexture),
			SelectedBackTexture(selectedTexture), CommandName(commandName), Valid(!commandName.empty()), Selected(false), UseRawText(true), OptionBack(baseTexture), OptionText(commandName, textFont, fontSize),
			OptionTextShadow(commandName, textFont, fontSize)
		{
			OptionTextShadow.setColor(sf::Color::Black);
			auto textSize = OptionText.getGlobalBounds();
			auto backSize = OptionBack.GetBaseSprite().getGlobalBounds();
			OptionText.setPosition((backSize.width - textSize.width) * 0.5f, -4.f);
			OptionTextShadow.setPosition(OptionText.getPosition() + sf::Vector2f(2.f, 2.f));
		}
		void CommandOption::Draw(sf::RenderTarget& target)
		{
			sf::RenderStates states;
			states.transform = GetTransform();
			OptionBack.Draw(target, states);
			if (UseRawText)
			{
				target.draw(OptionTextShadow, states);
				target.draw(OptionText, states);
			}
		}
		void CommandOption::Draw(sf::RenderTarget& target, sf::RenderStates states)
		{
			states.transform *= GetTransform();
			OptionBack.Draw(target, states);
			if (UseRawText)
			{
				target.draw(OptionTextShadow, states);
				target.draw(OptionText, states);
			}
		}
		void CommandOption::Update(const sf::Uint32 time, const float TimeScale)
		{
			OptionBack.Update(time, TimeScale);
			AnimatedSpriteInterface::Update(time, TimeScale);
		}
		void CommandOption::SetSelected(bool selected)
		{
			Selected = selected;
			OptionBack.SetTexture(selected ? SelectedBackTexture : BackTexture);
		}
		bool CommandOption::GetValid() const
		{
			return Valid;
		}
		void CommandOption::SetValid(const bool value)
		{
			Valid = value;
		}

		void CommandOption::SetCommandName(const std::string& cName)
		{
			CommandName = cName;
		}
		const std::string& CommandOption::GetCommandName() const
		{
			return CommandName;
		}


		//Command Option Set
		CommandOptionSet::CommandOptionSet(Engine* engine, float defaultOffset, float targetOffset) : OptionIndex(-1), Eng(engine), DefaultOffset(10.f), TargetOffset(targetOffset)
		{

		}
		CommandOptionSet::CommandOptionSet(const std::vector<std::string>& optionNames) : OptionIndex(-1)
		{
			for (auto option = optionNames.begin(); option != optionNames.end(); ++option)
			{

			}
		}
		void CommandOptionSet::AddOption(boost::shared_ptr<CommandOption> option)
		{
			Options.push_back(option);
		}
		void CommandOptionSet::SetOptionIndex(const int index)
		{
			OptionIndex = index;
			if (Options[index]->GetValid())
			{
				Options[index]->SetSelected(true);
			}
		}
		void CommandOptionSet::Draw(sf::RenderTarget& target)
		{
			sf::RenderStates states;
			states.transform = GetTransform();
			for (auto it = Options.begin(); it != Options.end(); ++it)
			{
				auto pos = (*it)->GetPosition();
				(*it)->Draw(target, states);
			}
		}
		void CommandOptionSet::Draw(sf::RenderTarget& target, sf::RenderStates states)
		{
			states.transform *= GetTransform();
			for (auto it = Options.begin(); it != Options.end(); ++it)
			{
				auto pos = (*it)->GetPosition();
				(*it)->Draw(target, states);
			}
		}
		void CommandOptionSet::Update(const sf::Uint32 time, const float TimeScale)
		{
			for (auto it = Options.begin(); it != Options.end(); ++it)
			{
				(*it)->Update(time, TimeScale);
			}
		}
		bool CommandOptionSet::HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{
			bool handled = false;
			int oldIndex = OptionIndex;
			if (actionResult.IAction == ::Input::Down)
			{

				OptionIndex = (OptionIndex + 1 >= Options.size() ? 0 : OptionIndex + 1); 
				int counter = 0;
				for (int counter = 0; counter < Options.size() && !Options[OptionIndex]->GetValid(); ++counter)
				{
					OptionIndex = (OptionIndex + 1 >= Options.size() ? OptionIndex + 1 : 0);
				}
				//Animation would go here


			}
			else if (actionResult.IAction == ::Input::Up)
			{
				OptionIndex = (OptionIndex - 1 < 0 ? Options.size() - 1 : OptionIndex - 1); 
				int counter = 0;
				for (int counter = 0; counter < Options.size() && !Options[OptionIndex]->GetValid(); ++counter)
				{
					OptionIndex = (OptionIndex - 1 < 0 ? Options.size() - 1 : OptionIndex - 1); 
				}
			}
			if (oldIndex != OptionIndex)
			{
				Options[OptionIndex]->SetSelected(true);
				Options[OptionIndex]->ClearTransforms(Eng->GetTime());
				Options[OptionIndex]->AddTransform("SlideOutTransform", boost::make_shared<::Graphics::PositionTransform>(*(Options[OptionIndex]), sf::Vector2f(TargetOffset, Options[OptionIndex]->GetPosition().y), Eng->GetTime(), 200));
				Options[oldIndex]->SetSelected(false);
				Options[oldIndex]->ClearTransforms(Eng->GetTime());
				Options[oldIndex]->AddTransform("SlideInTransform", boost::make_shared<::Graphics::PositionTransform>(*(Options[oldIndex]), sf::Vector2f(DefaultOffset, Options[oldIndex]->GetPosition().y), Eng->GetTime(), 200));
				handled = true;
				Eng->GetSoundSystem().Play("SelectionChange", static_cast<int>(Audio::SoundChannels::MenuSounds), false);
			}
			return true;
		}
		bool CommandOptionSet::HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{
			bool handled = false;
			if (actionResult.IAction == ::Input::Up)
			{

			}
			else if (actionResult.IAction == ::Input::Down)
			{
			}
			return handled;
		}

		//Character Command Vis
		CharacterCommandVisualizer::CharacterCommandVisualizer(::Input::PlayerInput activeOnPlayer)
		{
			ActiveOnPlayers.insert(activeOnPlayer);
		}
		void CharacterCommandVisualizer::SetCharacter(Character::BaseCharacter* character)
		{
			Character = character;
		}
		bool CharacterCommandVisualizer::HandleKeyPressed(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{
			bool handled = false;
			if (ActiveOnPlayers.find(actionResult.PInput) != ActiveOnPlayers.end() )
			{
				if (actionResult.IAction == ::Input::Left)
				{

				}
				else if (actionResult.IAction == ::Input::Right)
				{

				}
				else if (actionResult.IAction == ::Input::Up || actionResult.IAction == ::Input::Down)
				{
					if (SetIndex >= 0 && SetIndex < OptionSets.size())
					{
						handled = OptionSets[SetIndex]->HandleKeyPressed(time, inputModule, actionResult);
					}
				}
			}
			return handled;
		}
		bool CharacterCommandVisualizer::HandleKeyReleased(const sf::Uint32 time, const ::Input::InputModule* inputModule, ::Input::InputActionResult& actionResult)
		{
			bool handled = false;
			if (ActiveOnPlayers.find(actionResult.PInput) != ActiveOnPlayers.end() )
			{
				if (actionResult.IAction == ::Input::Left)
				{

				}
				else if (actionResult.IAction == ::Input::Right)
				{

				}
				else if (actionResult.IAction == ::Input::Up)
				{
					if (SetIndex >= 0 && SetIndex < OptionSets.size())
					{
						handled = OptionSets[SetIndex]->HandleKeyReleased(time, inputModule, actionResult);
					}
				}
				else if (actionResult.IAction == ::Input::Down)
				{
					if (SetIndex >= 0 && SetIndex < OptionSets.size())
					{
						handled =OptionSets[SetIndex]->HandleKeyReleased(time, inputModule, actionResult);
					}
				}
			}
			return handled;
		}

	}
}