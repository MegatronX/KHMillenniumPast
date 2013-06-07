#include "BaseCharacter.h"

namespace Game
{
	namespace Character
	{
		BaseCharacter::BaseCharacter() : Entity("DummyCharacter", CharacterEntity), ElementEffectsComponent(this), 
			SEManager(this), AbilManager(this), SManager(this), StatusEffectsComponent(this), Level(1)
		{

		}
		BaseCharacter::BaseCharacter(const std::string& characterName) : Entity(characterName, CharacterEntity), ElementEffectsComponent(this), 
			SEManager(this), AbilManager(this), SManager(this), StatusEffectsComponent(this), Level(1)
		{

		}
		BaseCharacter::BaseCharacter(const std::string& characterName, int baseStats[Character::StatCount]) : Entity(characterName, CharacterEntity), ElementEffectsComponent(this), 
			SEManager(this), AbilManager(this), SManager(this, baseStats), StatusEffectsComponent(this), Level(1)
		{

		}
		BaseCharacter::BaseCharacter(const std::string& characterName, std::vector<int>& baseStats) : Entity(characterName, CharacterEntity), ElementEffectsComponent(this), 
			SEManager(this), AbilManager(this), StatusEffectsComponent(this), SManager(this, baseStats), Level(1)
		{

		}
		BaseCharacter::BaseCharacter(const std::string& characterName, std::map<Stat, int>& baseStats) : Entity(characterName, CharacterEntity), ElementEffectsComponent(this), 
			SEManager(this), AbilManager(this), StatusEffectsComponent(this), SManager(this, baseStats), Level(1)
		{

		}
		BaseCharacter::BaseCharacter(const std::string& characterName, boost::unordered_map<Stat, int>& baseStats) : Entity(characterName, CharacterEntity), ElementEffectsComponent(this), 
			SEManager(this), AbilManager(this), StatusEffectsComponent(this), SManager(this, baseStats), Level(1)
		{

		}
		BaseCharacter::BaseCharacter(const BaseCharacter& cp) : Entity(cp), ElementEffectsComponent(cp.ElementEffectsComponent), SEManager(cp.SEManager), AbilManager(cp.AbilManager),
			SManager(cp.SManager), StatusEffectsComponent(cp.StatusEffectsComponent), AttachedParty(cp.AttachedParty), Level(1)
		{
			ElementEffectsComponent.SetOwner(this);
			SEManager.SetOwner(this);
			AbilManager.SetOwner(this);
			SManager.SetOwner(this);
			StatusEffectsComponent.SetOwner(this);
		}

		

		Components::Component* BaseCharacter::GetComponent(const std::string& index)// const
		{
			const static int EleHash = StringHasher("ElementEffectivenessComponent");
			const static int StatusHash = StringHasher("StatusEffectivenessComponent");
			const static int SEMHash = StringHasher("StatusEffectsManager");
			const static int AbilHash = StringHasher("AbilityManager");
			const static int StatsM = StringHasher("StatsManager");
			auto indexHash = StringHasher(index);

			if (EleHash == indexHash)
			{
				return const_cast<Components::ElementEffectivenessComponent*>(&ElementEffectsComponent);
			}
			else if (StatusHash == indexHash)
			{
				return const_cast<Components::StatusEffectivenessComponent*>(&StatusEffectsComponent);
			}
			else if (SEMHash == indexHash)
			{
				return const_cast<StatusEffects::StatusEffectsManager*>(&SEManager);
			}
			else if (AbilHash == indexHash)
			{
				return const_cast<Abilities::AbilityManager*>(&AbilManager);
			}
			else if (StatsM == indexHash)
			{
				return &SManager;
			}
			else
			{
				return Entity::GetComponent(index);
			}
			return nullptr;
		}
		Entity::RawClonePtr BaseCharacter::RawClone() const
		{
			return new BaseCharacter(*this);
		}

		BaseParty* BaseCharacter::GetParty() const
		{
			return AttachedParty;
		}

		void BaseCharacter::SetParty(BaseParty* party)
		{
			AttachedParty = party;
		}

		StatusEffects::StatusEffectsManager& BaseCharacter::GetStatusEffectsManager()
		{
			return SEManager;
		}
		Abilities::AbilityManager& BaseCharacter::GetAbilityManager()
		{
			return AbilManager;
		}

		StatsManager& BaseCharacter::GetStatsManager()
		{
			return SManager;
		}

		Components::ElementEffectivenessComponent& BaseCharacter::GetElementEffectiveness()
		{
			return ElementEffectsComponent;
		}

		void BaseCharacter::SetName(const std::string& name)
		{
			this->ChangeName(name);
		}

		BaseCharacter& BaseCharacter::operator=(const BaseCharacter& ref)
		{
			if (this != &ref)
			{
				Entity::operator=(ref);
				this->AttachedParty = ref.AttachedParty;
				this->SEManager = ref.SEManager;
				this->SEManager.SetOwner(this);
				this->AbilManager = ref.AbilManager;
				this->AbilManager.SetOwner(this);
				this->SManager = ref.SManager;
				this->SManager.SetOwner(this);
				this->StatusEffectsComponent = ref.StatusEffectsComponent;
				this->StatusEffectsComponent.SetOwner(this);
				this->ElementEffectsComponent = ref.ElementEffectsComponent;
				this->ElementEffectsComponent.SetOwner(this);
			}
			return *this;
		}
	}
}