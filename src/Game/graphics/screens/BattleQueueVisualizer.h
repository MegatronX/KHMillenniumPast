#pragma once
#include <Graphics/visualizers/EntityComponentVisualizer.h>
#include <battle/mechanics/QueueTurnGenerator.h>
#include <Graphics/Sprites/AnimatedSprite.h>
namespace Game
{
	namespace Graphics
	{
		const std::string BattleQueueVisualizerIndex = "BattleQueueVisComponent";
		class BattleQueueVisualizer : public ComponentVisualizer
		{
		public:
			BattleQueueVisualizer(Engine* engine, Battle::QueueTurnGenerator* turnGen, Entity* owner);

			void QueueModifiedHandler(Battle::TurnGenerator& gen, Battle::BattleMode mode);

			void BuildQueue(const Battle::TurnQueue& bQueue, const int limit = 10);

			virtual void Draw(sf::RenderTarget &window) override;
			virtual void Draw(sf::RenderTarget &window, sf::RenderStates states) override;
			virtual void Update(const sf::Uint32 time, const float timescale = 1.f);

			~BattleQueueVisualizer();
		protected:
			struct QueueVisualEntry
			{
				QueueVisualEntry(const std::string& name, int entryNum, sf::Vector2f& pos, sf::Vector2f size, boost::shared_ptr<sf::Texture> tx, boost::shared_ptr<sf::Font> txtFont, sf::Vector2f txtOffset = sf::Vector2f(0.f, 0.f), const sf::Uint32 fontSize = 15);
				::Graphics::AnimatedSprite Sprite;
				boost::shared_ptr<sf::Font> TextFont;
				sf::Vector2f Positon;
				sf::Vector2f Size;
				sf::Vector2f TextOffset;
				int EntryNumber;
				sf::Text Name;

			};

			std::deque<QueueVisualEntry> QueueEntries;

			Battle::QueueTurnGenerator* TurnGen;
			boost::signals2::connection QueueModifiedConnection;
		};
	}
}