#pragma once
#ifndef _CARD_H_
#define _CARD_H_
#include <array>
#include <string>
#include <Utilities/Cloneable.h>
#include <boost/shared_ptr.hpp>
namespace Game
{
	namespace MiniGames
	{
		namespace Triad
		{
			const int CardPositions = 8;
			enum CardPosition
			{
				Up,
				Down,
				Left,
				Right,
				UpLeft,
				UpRight,
				DownLeft,
				DownRight
			};
			enum CardClass
			{
				Character,
				Equipment,
				Item,
				Magic,
			};
			class Card : public Cloneable<Card>
			{
			public:
				Card();
				Card(const std::string& name);
				//Card(const Card& src);
				virtual RawClonePtr RawClone() const override;

				//Card& operator=(const Card& src);

				int GetCardValue(const CardPosition position) const;
				bool GetCardAttacking(const CardPosition position) const;
				
				const std::string& GetName() const;
				const std::string& GetOwner() const;
				void SetOwner(const std::string& owner);

				CardClass GetCardClass();

				int operator[] (const CardPosition position) const;
			protected:
				void SetValue(const CardPosition position, const int value);
				void SetAttacking(const CardPosition position, const bool value);
			private:
				CardClass cardClass;
				
				std::array<int, CardPositions> CardValues;
				std::array<bool, CardPositions> AttackValues;
				std::string Name;
				std::string Owner;
			};

			typedef boost::shared_ptr<Card> card_ptr;
		}
	}
}

#endif