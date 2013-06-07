#include "Stats.h"
#include <boost/assign.hpp>

namespace Game
{
	namespace Character
	{
		
		const std::array<Stat, VolateStatCount> VolatileStats = {{Stat::HP, Stat::MP, Stat::SP}};
		const boost::unordered_map<Stat, std::string> StatNameLookup = boost::assign::map_list_of
			(Stat::HP, "HP")
			(Stat::MP, "MP")
			(Stat::SP, "SP")
			(Stat::Strength, "Strength")
			(Stat::Vitality, "Vitality")
			(Stat::Magic, "Magic")
			(Stat::Spirit, "Spirit")
			(Stat::Skill, "Skill")
			(Stat::Speed, "Speed")
			(Stat::Agility, "Agility")
			(Stat::Evasion, "Evasion")
			(Stat::MgEvasion, "MgEvasion")
			(Stat::Accuracy, "Accuracy")
			(Stat::Luck, "Luck");
		extern const boost::unordered_map<std::string, Stat> NameStatLookup = boost::assign::map_list_of
			("HP", Stat::HP)
			("MP", Stat::MP)
			("SP", Stat::SP)
			("Strength", Stat::Strength)
			("Str", Stat::Strength)
			("Vitality", Stat::Vitality)
			("Vit", Stat::Vitality)
			("Magic", Stat::Magic)
			("Mg", Stat::Magic)
			("Spirit", Stat::Spirit)
			("Spr", Stat::Spirit)
			("Skill", Stat::Skill)
			("Skl", Stat::Skill)
			("Speed", Stat::Speed)
			("Spd", Stat::Speed)
			("Agility", Stat::Agility)
			("Evasion", Stat::Evasion)
			("Ev", Stat::Evasion)
			("MgEvasion", Stat::MgEvasion)
			("MgEv", Stat::MgEvasion)
			("Accuracy", Stat::Accuracy)
			("MgAcr", Stat::MgAccuracy)
			("MgAccuracy", Stat::MgAccuracy)
			("MagicAccuracy", Stat::MgAccuracy)
			("Acr", Stat::Accuracy)
			("Luck", Stat::Luck)
			("Lck", Stat::Luck);

		/*
		<Str value="13"/>
		<Mg value="17"/>
		<Vit value="20"/>
		<Spr value="19"/>
		<Spd value="35"/>
		<Ev value="3"/>
		<MgEv value="2"/>
		<Acr value="17"/>
		<Lck value="10"/>
		*/
	}
}