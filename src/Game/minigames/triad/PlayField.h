#pragma once
#ifndef _PLAYFIELD_H_
#define _PLAYFIELD_H_
#include <stack>
#include <elements/Elements.h>
#include <boost/unordered_map.hpp>
#include "Deck.h"
#include "Hand.h"
#include "TriadPlayer.h"

namespace Game
{
	namespace MiniGames
	{
		namespace Triad
		{
			const int GridWidth = 4;
			const int GridHeight = 4;
			const int GridSize = GridWidth * GridHeight;
			class PlaySquare
			{
			public:
				PlaySquare();
				card_ptr GetCard() const;
				bool IsLive() const;
			private:
				card_ptr SquareCard;
				bool Live;
			};

			class PlayField
			{
			public:
				card_ptr GetCardAtPos(int index) const;
				card_ptr GetCardAtPos(int x, int y) const;
				PlaySquare& GetSquare(int index);
				PlaySquare& GetSquare(int x, int y);
				void AddToGraveyard(const std::string& playerName, card_ptr card);
				void AddToGraveyard(const TriadPlayer& player, card_ptr card);
				void AddToGraveyard(const int index);
			private:
				std::vector<TriadPlayer> Players;
				std::array<PlaySquare, GridSize> Field;
				PlaySquare EmptySquare;
				boost::unordered_map<std::string, std::stack<card_ptr> > GraveYards;
			};
		}
	}
}

#endif