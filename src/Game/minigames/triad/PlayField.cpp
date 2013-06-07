#include "PlayField.h"

namespace Game
{
	namespace MiniGames
	{
		namespace Triad
		{
			//PlaySquare

			PlaySquare::PlaySquare()
			{
				
			}
			card_ptr PlaySquare::GetCard() const
			{
				return SquareCard;
			}


			card_ptr PlayField::GetCardAtPos(int index) const
			{
				if (index < GridSize)
				{
					return Field[index].GetCard();
				}
				return card_ptr();
			}
			card_ptr PlayField::GetCardAtPos(int x, int y) const
			{
				return GetCardAtPos(y * GridWidth + x);
			}
			PlaySquare& PlayField::GetSquare(int index)
			{
				if (index < GridSize)
				{
					return Field[index];
				}
			}
			PlaySquare& PlayField::GetSquare(int x, int y)
			{
				return GetSquare(y * GridWidth + x);
			}
			void PlayField::AddToGraveyard(const std::string& playerName, card_ptr card)
			{

			}
			void PlayField::AddToGraveyard(const TriadPlayer& player, card_ptr card)
			{

			}
			void PlayField::AddToGraveyard(const int index)
			{

			}

			//PlayField
		}
	}
}