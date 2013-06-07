#pragma once
#ifndef _TRIADPLAYER_H_
#define _TRIADPLAYER_H_
#include <stack>
#include "Hand.h"
#include <sfml/Graphics/Color.hpp>
namespace Game
{
	namespace MiniGames
	{
		namespace Triad
		{
			class TriadPlayer
			{
			public:
				Hand& GetHand() const;
				const std::string& GetPlayerName() const;
				sf::Color& GetPlayerColor() const;
			private:
				std::string PlayerName;
				sf::Color PlayerColor;
				Hand PlayerHand;
			};
		}
	}
}

#endif