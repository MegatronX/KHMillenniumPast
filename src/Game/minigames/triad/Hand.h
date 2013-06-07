#pragma once
#ifndef _HAND_H_
#define _HAND_H_
#include <vector>
#include <iostream>
#include "Card.h"

namespace Game
{
	namespace MiniGames
	{
		namespace Triad
		{
			class Hand
			{
			public:
				Hand(const std::vector<card_ptr>& initialCards);
				virtual void Print(std::ostream& outStream);
				void Shuffle();
			private:
				std::vector<card_ptr> InHandCards;
			};
		}
	}
}

#endif