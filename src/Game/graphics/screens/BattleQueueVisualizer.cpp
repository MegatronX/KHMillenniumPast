#include "BattleQueueVisualizer.h"

namespace Game
{
	namespace Graphics
	{
		BattleQueueVisualizer::BattleQueueVisualizer(Engine* engine, Battle::QueueTurnGenerator* turnGen, Entity* owner) : ComponentVisualizer(engine, turnGen, owner), TurnGen(turnGen)
		{
			if (TurnGen != nullptr)
			{
				//ReadySignalConnection = TurnGen->AddCharacterReadyEventHandler(boost::bind(&BattleQueueVisualizer::NewCharacterReady, this, _1, _2));
				QueueModifiedConnection = TurnGen->AddQueueModifiedEventHandler(boost::bind(&BattleQueueVisualizer::QueueModifiedHandler, this, _1, _2));
			}

		}

		void BattleQueueVisualizer::QueueModifiedHandler(Battle::TurnGenerator& gen, Battle::BattleMode mode)
		{
			if (mode == Battle::BattleMode::Sim)
			{
				auto& targQueue = gen.GetTurnQueue(mode);
				std::cout << "Changing Queue Preview. Queue Size is " << gen.GetTurnQueue(mode).size() << "\n";
				BuildQueue(targQueue);
			}
			
		}

		void BattleQueueVisualizer::BuildQueue(const Battle::TurnQueue& bQueue, const int limit)
		{
			int entry = 0;
			sf::Vector2f start(00.f, 0.f);
			sf::Vector2f size(90.f, 32.f);
			sf::Vector2f spacing(0.f, 4.f);
			sf::Vector2f txtOff(40.f, 26.f); 
			int i = 0;
			QueueEntries.clear();
			for (auto ch = bQueue.begin(); ch != bQueue.end() && i < limit; ++ch, ++i)
			{
				auto prop = (*ch)->GetOwner()->GetProperty("Type");
				if (prop != Entity::InvalidPropertyText)
				{
					auto tx = Eng->GetContentManager().RequestTexture(prop, Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::GUIBattleElement, Eng->GetTime());
					QueueEntries.push_back(QueueVisualEntry(prop, entry, sf::Vector2f(start.x + (spacing.x * static_cast<float>(entry)), start.y + ((size.y + spacing.y) * static_cast<float>(entry))), size, tx, Eng->GetContentManager().RequestFont("calibri", Eng->GetTime()), txtOff));
				}
				++entry;
			}
		}

		void BattleQueueVisualizer::Draw(sf::RenderTarget &window)
		{
			sf::RenderStates states;
			states.transform = GetTransform();
			for (auto qEn = QueueEntries.begin(); qEn != QueueEntries.end() && (qEn->Sprite.GetPosition().x < 800 && qEn->Sprite.GetPosition().y < 600); ++qEn)
			{
				qEn->Sprite.Draw(window, states);
				window.draw(qEn->Name, states);
			}
		}
		void BattleQueueVisualizer::Draw(sf::RenderTarget &window, sf::RenderStates states)
		{
			states.transform *= GetTransform();
			for (auto qEn = QueueEntries.begin(); qEn != QueueEntries.end(); ++qEn)
			{
				qEn->Sprite.Draw(window, states);
				window.draw(qEn->Name, states);
				//window.draw(qEn->Name, sf::RenderStates(&shader));
			}
		}
		void BattleQueueVisualizer::Update(const sf::Uint32 time, const float timescale)
		{

		}

		BattleQueueVisualizer::~BattleQueueVisualizer()
		{
			QueueModifiedConnection.disconnect();
		}

		BattleQueueVisualizer::QueueVisualEntry::QueueVisualEntry(const std::string& name, int entryNum, sf::Vector2f& pos, sf::Vector2f size, boost::shared_ptr<sf::Texture> tx, boost::shared_ptr<sf::Font> txtFont, sf::Vector2f txtOffset, const sf::Uint32 fontSize) : Size(size), Positon(pos), EntryNumber(entryNum), 
			TextFont(txtFont), Name(sf::String(name), *TextFont), Sprite(tx)
		{
			Name.setPosition(pos + TextOffset);
			Name.setCharacterSize(fontSize);
			Sprite.SetPosition(pos);
			auto txSize = Sprite.GetBaseSprite().getTextureRect();
			Sprite.SetScale(size.x / txSize.width, size.y / txSize.height);

		}

	}
}