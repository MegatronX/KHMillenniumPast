#include "Deck.h"
#include <Engine.h>
#include <random>
#include <unordered_set>
namespace Game
{
	namespace MiniGames
	{
		namespace Triad
		{

			void Test(Engine* engine)
			{
				Deck deck(engine);
				
				for (int i = 0; i < 50; ++i)
				{
					card_ptr card(new Card("Test" + boost::lexical_cast<std::string>(i)));
					deck.AddCard(card);
				}
				for (int i = 0; i < 20; ++i)
				{
					deck.Shuffle();
					Hand myHand(deck.DrawCards(10, false, false, 0));
					myHand.Print(std::cout);
				}
			}

			Deck::Deck(Engine* engine) : engine(engine)
			{

			}
			void Deck::AddCard(card_ptr card)
			{
				Cards.push_back(card);
			}
			card_ptr Deck::PopCard()
			{
				auto card = *Cards.begin();
				Cards.erase(Cards.begin());
				return card;
			}
			card_ptr Deck::GetCardAt(int index) const
			{
				if (index < Cards.size())
					return Cards[index];
				return card_ptr();
			}
			std::vector<card_ptr> Deck::DrawCards(const int DrawCount, const bool Random, const bool RemoveFromDeck, const int startIndex, const bool GuaranteeUniqueness)
			{
				std::vector<card_ptr> DrawnCards;
				DrawnCards.reserve(DrawCount);
				int Drawn = 0;
				int index = 0;
				std::unordered_set<int> DrawnCardIndexes;
				if (Random)
				{
					for (; Cards.size() > 0 && DrawnCards.size() < DrawCount && DrawnCardIndexes.size() < Cards.size(); ++Drawn)
					{
						index = engine->GetRandomInt(0, Cards.size() - 1);
						if (GuaranteeUniqueness && !RemoveFromDeck)
						{
							bool add = true;
							int iter = 0;
							const int iterationLimit = 70;
							for (; iter <= iterationLimit && std::find(DrawnCardIndexes.begin(), DrawnCardIndexes.end(), index) != DrawnCardIndexes.end(); ++iter)
							{
								index = engine->GetRandomInt(0, Cards.size() - 1);
							}
							if(iter >= iterationLimit) //Stops indefinite randomization
							{
								for (int i = 0; i < Cards.size(); ++i)
								{
									if (std::find(DrawnCardIndexes.begin(), DrawnCardIndexes.end(), i) != DrawnCardIndexes.end())
									{
										index = i;
									}
								}
							}
							if (add)
								DrawnCardIndexes.insert(index);
						}
						DrawnCards.push_back(Cards[index]);
						if (RemoveFromDeck)
						{
							Cards.erase(Cards.begin() + index);
						}
					}
				}
				else
				{
					for (index = startIndex; Cards.size() > 0 && DrawnCards.size() < DrawCount && DrawnCardIndexes.size() < Cards.size() && std::find(DrawnCardIndexes.begin(), DrawnCardIndexes.end(), index) == DrawnCardIndexes.end(); index = (index + 1) % Cards.size(), ++Drawn)
					{
						if (GuaranteeUniqueness && !RemoveFromDeck)
						{
							DrawnCardIndexes.insert(index);
						}
						DrawnCards.push_back(Cards[index]);
						if (RemoveFromDeck)
						{
							Cards.erase(Cards.begin() + index);
							--index;
						}
					}
				}

				/*if (Random)
				{
					for (;Drawn < DrawCount && DrawnCards.size() < Cards.size() && Cards.size() > 0; ++Drawn)
					{
						if (GuaranteeUniqueness)
						{
							index = engine->GetRandomInt<uint32_t>() % Cards.size();
							while (std::find(DrawnCardIndexes.begin(), DrawnCardIndexes.end(), index) != DrawnCardIndexes.end())
							{
								index = engine->GetRandomInt<uint32_t>() % Cards.size();
							}
						}
						
						DrawnCards.push_back(Cards[index]);
						if (RemoveFromDeck)
						{
							DrawnCards.erase(Cards.begin() + index);
						}
						
					}
				}
				else
				{
					for (index = startIndex; Drawn < DrawCount && DrawnCards.size() < Cards.size() && index < Cards.size(); ++index, ++Drawn)
					{
						DrawnCards.push_back(Cards[index]);
						if (RemoveFromDeck)
						{
							DrawnCards.erase(Cards.begin() + index);
						}
					}
				}*/


				return DrawnCards;
			}
			void Deck::RemoveCard(int index)
			{
				if (index < Cards.size())
				{
					Cards.erase(Cards.begin() + index);
				}
			}
			void Deck::Shuffle()
			{
				std::random_shuffle(Cards.begin(), Cards.end());
			}
			DeckStats Deck::AnalyzeDeck()
			{
				DeckStats stats;
				stats.TotalCards = Cards.size();

				for(auto card = Cards.begin(); card != Cards.end(); ++card)
				{
					switch((*card)->GetCardClass())
					{
					case Character:
						stats.PlayerCards++;
						break;
					case Equipment:
						stats.EquipCards++;
						break;
					case Item:
						stats.ItemCards++;
						break;
					case Magic:
						stats.MagicCards++;
						break;
					}
				}

				return stats;
			}
			const std::vector<card_ptr>& Deck::GetAllCards() const
			{
				return Cards;
			}
			void Deck::Print(std::ostream& outStream)
			{

			}

			Deck::RawClonePtr Deck::RawClone() const
			{
				return new Deck(*this);
			}
			card_ptr Deck::operator[](const int index) const
			{
				return GetCardAt(index);
			}
		}
	}
}