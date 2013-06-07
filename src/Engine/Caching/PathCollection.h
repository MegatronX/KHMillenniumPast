#pragma once
#ifndef _PATHCOLLECTION_H_
#define _PATHCOLLECTION_H_

#include <string>

namespace Cache
{
	struct PathCollection
	{
		std::string BattleBacks;
		std::string BackColorsDirectory;
		std::string Backgrounds;
		std::string SpriteDirectory;
		std::string BossSubDirectory;
		std::string EnemySubDirectory;
		std::string NPCSubDirectory;
		std::string WeaponsSubDirectory;
		std::string BattleSubDirectory;
		std::string GuardianSubDirectory;
		std::string ChasersSubDirectory;
		std::string GUISubDirectory;
		std::string GUIBattleSubDirectory;
		std::string GUIBattleQueueSubDirectory;
		std::string GUIMenuSubDirectory;
		std::string IconSubDirectory;
		std::string TitleScreenSubDirectory;
		std::string QueueSubDirectory;
		std::string QuadrupleTriadDirectory;
		std::string WorldSubDirectory;
		std::string OverworldSpriteDirectory;
		std::string MagicSheetSpriteDirectory;
		std::string SkillSheetSpriteDirectory;
		std::string MinigameSpriteDirectory;
		std::string DDRSpriteDirectory;
		std::string ParticleDirectory;
	};
}

#endif