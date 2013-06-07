#include "Hand.h"

namespace Game
{
	namespace MiniGames
	{
		namespace Triad
		{
			Hand::Hand(const std::vector<card_ptr>& initialCards) : InHandCards(initialCards)
			{

			}

			void Hand::Print(std::ostream& outStream)
			{
				outStream << "\n\n******* Hand ********* \n\n";
				for(auto iter = InHandCards.begin(); iter != InHandCards.end(); ++iter)
				{
					outStream << (*iter)->GetName() << "\n";
				}
				outStream << "*******************" << std::endl;
			}
		}
	}
}