#include "Card.h"

namespace Game
{
	namespace MiniGames
	{
		namespace Triad
		{


			Card::Card()
			{

			}
			Card::Card(const std::string& name) : Name(name)
			{

			}
			/*Card::Card(const Card& src)
			{

			}*/
			Card::RawClonePtr Card::RawClone() const
			{
				return new Card(*this);
			}

			/*Card& Card::operator=(const Card& src)
			{
			}*/

			int Card::GetCardValue(const CardPosition position) const
			{
				return CardValues[position];
			}
			bool Card::GetCardAttacking(const CardPosition position) const
			{
				return AttackValues[position];
			}
			const std::string& Card::GetName() const
			{
				return Name;
			}
			const std::string& Card::GetOwner() const
			{
				return Owner;
			}
			void Card::SetOwner(const std::string& owner)
			{
				Owner = owner;
			}
			CardClass Card::GetCardClass()
			{
				return cardClass;
			}
			int Card::operator[] (const CardPosition position) const
			{
				return CardValues[position];
			}
			void Card::SetValue(const CardPosition position, const int value)
			{
				CardValues[position] = value;
			}
			void Card::SetAttacking(const CardPosition position, const bool value)
			{
				AttackValues[position] = value;
			}

		}
	}
}