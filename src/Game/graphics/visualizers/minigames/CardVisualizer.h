#include <graphics/Sprites/SpriteInterface.h>
#include <minigames/triad/Card.h>

class Engine;

namespace Game
{
	namespace Graphics
	{
		namespace Visuazlizer
		{
			class CardVisualizer : public SpriteInterface
			{
			public:
				CardVisualizer(MiniGames::Triad::card_ptr cardPtr) : AttachedCard(cardPtr)
				{

				}
				void virtual Draw(sf::RenderTarget &window, sf::RenderStates states) override;
			private:
				Engine* engine;
				MiniGames::Triad::card_ptr AttachedCard;
			};
		}
	}
}