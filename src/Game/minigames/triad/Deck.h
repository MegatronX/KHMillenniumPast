#pragma once
#ifndef _DECK_H_
#define _DECK_H_
#include <array>
#include <algorithm>
#include <vector>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "Card.h"
#include "Hand.h"
class Engine;
namespace Game
{
	namespace MiniGames
	{
		namespace Triad
		{
			struct DeckStats
			{
				int TotalCards;
				int PlayerCards;
				int EquipCards;
				int ItemCards;
				int MagicCards;
			};
			class Deck : Cloneable<Deck>
			{
			public:
				Deck(Engine* engine);
				void AddCard(card_ptr card);
				card_ptr PopCard();
				card_ptr GetCardAt(int index) const;
				std::vector<card_ptr> DrawCards(const int DrawCount, const bool Random = true, const bool RemoveFromDeck = true, const int startIndex = 0, const bool GuaranteeUniqueness = true);
				void RemoveCard(int index);
				void Shuffle();
				DeckStats AnalyzeDeck();
				const std::vector<card_ptr>& GetAllCards() const;


				void Print(std::ostream& outStream);

				virtual RawClonePtr RawClone() const override;

				card_ptr operator[](const int index) const;

			private:
				std::vector<card_ptr> Cards;
				Engine* engine;
			};

			extern void Test(Engine* engine);
		}
	}
}

#endif