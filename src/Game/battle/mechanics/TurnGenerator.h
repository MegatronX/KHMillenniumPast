#pragma once
#ifndef _TURNGENERATOR_H_
#define _TURNGENERATOR_H_
#include <deque>
#include <vector>
#include <Entity.h>
#include <battle/BattleCharacterComponent.h>
#include <boost/signals2.hpp>
#include <Graphics/Updater.h>
namespace Game
{
	namespace Battle
	{
		class BattleField;
		class Mechanics;

		typedef std::deque<BattleCharacterComponent*> TurnQueue;
		typedef std::vector<BattleCharacterComponent*> ReadyList;
		typedef boost::signals2::signal<void (ReadyList, BattleMode)> CharactersReadySignal;
		typedef boost::signals2::signal<void (TurnGenerator&, BattleMode)> QueueChangedSignal;
		class TurnGenerator : public Components::Component, public ::Graphics::Updater
		{
		public:
			TurnGenerator(Entity* owner, const std::string& CType = "TurnGenerator");
			TurnGenerator(const TurnGenerator& tg);
			void Update(const sf::Uint32 time, const float TimeScale = 1.f) override;
			virtual RawClonePtr RawClone() const override;
			virtual void TrackCharacter(BattleCharacterComponent* character);
			virtual bool StopTrackingCharacter(const std::string& name);
			virtual bool StopTrackingCharacter(BattleCharacterComponent* character);

			BattleCharacterComponent* GetCharacter(const std::string& name);

			virtual BattleCharacterComponent* GetReadyCharater(bool popOffReadyList = false);

			virtual void PopReadyCharacter();

			virtual void GenerateNextCharacter(const unsigned int GenCounter = 1);

			virtual void FillQueue(const unsigned int QueueSizeFill = 10);

			virtual void ClearQueue(const BattleMode mode);

			virtual void TickCharacter(BattleCharacterComponent* character);

			const boost::unordered_map<std::string, BattleCharacterComponent*>& GetUpdateList() const;

			void SetGeneratorMode(const BattleMode mode);

			BattleMode GetGeneratorMode() const;

			virtual void PushRealToSim();

			virtual void PushSimToReal();

			boost::signals2::connection AddCharacterReadyEventHandler(const CharactersReadySignal::slot_type& event);

			boost::signals2::connection AddQueueModifiedEventHandler(const QueueChangedSignal::slot_type& event);

			void DispatchQueueModifiedEvents();
			//static boost::shared_ptr<TurnGenerator> MakeGenerator(const std::string& type);

			TurnQueue& GetTurnQueue(const BattleMode mode);

			virtual void StartCharacterTurn(Character::BaseCharacter& character);

			virtual void EndCharacterTurn(Character::BaseCharacter& character);



			virtual ~TurnGenerator();
			//void
		protected:
			virtual void HandleTimerOverflow(BattleCharacterComponent*, BattleMode);

			BattleMode GeneratorMode;

			CharactersReadySignal ReadyCharSignal;
			QueueChangedSignal QueueModifiedSignal;

			boost::unordered_map<std::string, BattleCharacterComponent*> UpdateList;
			boost::unordered_map<std::string, boost::signals2::connection> TimerOverflowConnections;
			boost::unordered_map<std::string, boost::signals2::connection> QueueModifiedConnections;

			std::array<ReadyList, ModeCount> ReadyLists;
			std::array<TurnQueue, ModeCount> TurnQueues;
		private:
			

			Mechanics* ownerMechanics;
		};
	}
}

#endif