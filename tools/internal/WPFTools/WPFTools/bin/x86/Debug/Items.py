from ItemModule import *
from CharacterModule import *
from BattleModule import *
from StatusEffectsModule import *
from EngineModule import *
from ElementModule import *

import copy
#name, description, const int itemTypes, const int itemFlags, const int itemUse, const int throwPower, const int value, int id
class ScriptedItem(Item):
    def __init__(self, name, description, itemtypes, primarytype, flags, usability, value, throwpower):
        Item.__init__(self, name, description, itemtypes, primarytype, flags, usability, value, throwpower, Item.GetNextItemID())
    def Clone(self):
        return copy.deepcopy(self)

class PermanentStatBooster(UsableItem):
    def __init__(self, name, description, itemtypes, flags, value, throwpower, boostingmap):
        self.BoostMap = boostingmap
        itemtypes |= ItemType.StatBoostingItem
        flags |= ItemFlag.Consumable;
        UsableItem.__init__(self, name, description, itemtypes, ItemType.StatBoostingItem, flags, ItemUsage.UsableOnlyOutsideOfBattle, throwpower, value, ActionTargets.Any, Item.GetNextItemID())
    def Use(self, targets):
        if (len(targets) > 1):
            print "Cannot apply stat boost to more then 1 Target!"
        target = targets[0];
        for stat, boost in self.BoostMap.iteritems():
            target.SetPermanentStatBoost(stat, target.GetPermanentStatBoost(stat) + boost)
            target.SyncCombinedStat(stat)
    def Clone(self):
        return copy.deepcopy(self);

class HealingItem(UsableItem):
    def __init__(self, name, description, itemtypes, primarytype, flags, usability, targetting, value, throwpower, healmap):
        UsableItem.__init__(self, name, description, itemtypes, primarytype, flags, usability, throwpower, value, targetting, Item.GetNextItemID())
        self.HealMap = healmap
    def Use(self, targets):
        for target in targets:
            if('HP' in self.HealMap):
                HealRate = self.HealMap['HP'][0]
                AbsoluteHeal = self.HealMap['HP'][1]
                #print (target.GetName() + " HP: " + str(target.GetHP()) + ". Abs Heal: " + str(AbsoluteHeal))
                if (AbsoluteHeal):
                    target.SetHP(int(target.GetHP() + HealRate))
                    #print (target.GetName() + " HP: " + str(target.GetHP()))
                else:
                    target.SetHP(int(target.GetHP() + target.GetInBattleStat(Stat.HP) * HealRate))
                    #print (target.GetName() + " HP: " + str(target.GetHP()) + "| Heal Rate: " + str(HealRate) + " | Max Health: " + str(target.GetInBattleStat(Stat.HP)))
            if ('MP' in self.HealMap):
                HealRate = self.HealMap['MP'][0]
                AbsoluteHeal = self.HealMap['MP'][1]
                if (AbsoluteHeal):
                    target.SetMP(int(target.GetMP() + HealRate))
                else:
                    target.SetMP(int(target.GetMP() + target.GetInBattleStat(Stat.MP) * HealRate))

            if ('SP' in self.HealMap):
                HealRate = self.HealMap['SP'][0]
                AbsoluteHeal = self.HealMap['SP'][1]
                if (AbsoluteHeal):
                    target.SetSP(int(target.GetSP() + HealRate))
                else:
                    target.SetSP(int(target.GetSP() + target.GetInBattleStat(Stat.SP) * HealRate))
    def BattleUse(self, users, targets, field):
        bcharvec = BaseCharacterVector()
        for target in targets:
            bcharvec.append(target.GetCharacter().GetCharacterPtr())
        #self.UseInBattle = true
        self.Use(bcharvec)
    def Clone(self):
        return copy.deepcopy(self)
#Synthesis Items
ItemLibrary.AddItem(ScriptedItem("Abounding Crystal", "A colourful crystal composed of many smaller crystals. It gives off a warm glow.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Blazing Shard", "A small red shard that appears to have a small flame inside. It feels warm to the touch.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Blazing Stone", "A red stone that glows brightly from the fire inside. It feels hot to the touch.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Blazing Gem", "Fire swirls around inside, giving off a bright glow. It is painfully hot to the touch.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Blazing Crystal", "A powerful flame burns inside making it look as though it's on fire. It emits a dangerous amount of heat.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Bright Shard", "A small shard with a few specks of light floating inside. It emits a faint glow.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Bright Stone", "Several small lights dance around inside. It emits a noticable glow.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Bright Gem", "Many small lights swirl around inside. It gives off a strong glow.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Bright Crystal", "Countless lights flow around inside. It gives off an intense light.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Chaos Crystal", "Light is refracted chaotically inside producing intense colours. It sometimes vibrates wildly.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Dark Shard", "A small shard that seems to absorb light cast on it.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Dark Stone", "It appears to draw in light, casting shadows around itself.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Dark Gem", "Draws in and absorbs light, darkening areas around it. It is cool to the touch.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Dark Crystal", "Draws in large amounts of light, darkening large areas. It feels cold to the touch.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Dense Shard", "A small grey shard that is suprisingly heavy.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Dense Stone", "A heavy stone that is difficult to damage.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Dense Gem", "An opaque grey gem that is extremely heavy and resilient to damamge.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Dense Crystal", "A mostly opaque crystal that is exceedingly difficult to move due to it's weight. Has tremendous strength.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Energy Shard", "A shard that occasionally moves by itself, it is strongly drawn to other metals.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Energy Stone", "It glows faintly and is warm to the touch. It can magnify any force applied to it. It can impart energy to nearby objects.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Energy Gem", "It seems to contract and expand when held. Holding it causes a rush of energy to pass through the holder.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Energy Crystal", "It pulsates with intense energy. It greatly magnifies any force applied to it and frequently energizes nearby objects.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Fleeting Crystal", "A decayed crysal that looks as though it was once glorious. Listening closely, voices can sometimes be heard.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Frost Shard", "A translucent blue shard. It is cool to the touch.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Frost Stone", "A light weight blue stone, it is quite cold to the touch.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Frost Gem", "A gem frozen from the inside out, it is always covered in a layer of ice.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Frost Crystal", "A brilliantly blue crystal that freezes nearby objects. It is dangerously cold.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Manifest Illusion", "A small multicoloured crystal, it strongly distorts any light passing through. It is rumoured to reveal a being's true form.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Lost Illusion", "A large elaborate crystal that warps light. It is rumoured that it can reveal glimpses of the future.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Orichalcum", "An extremely rare and strong material, it boasts great strength and resistance to the elements.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Orichalcum+", "Orichalcum refined to it's purest level, Orichalcum+ is incredibly rare and valuable. It posseses superior strength to Orichalcum.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Lucid Shard", "A dark, smoky crystal, it is surpsingly light.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Lucid Stone", "Smoke seems to swirl around inside. It is cool to the touch and gives off an eerie vibe.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Lucid Gem", "Smoke moves around chaotically inside. It is cold to the touch and uneases those around it.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Lucid Crystal", "An extremely light crystal, it feels as though an ominous presence lurks inside it's dark smoky interior.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Mythril Shard", "A small shard with incredible strength, it feels almost as light as air.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Mythril Stone", "A virtually weightless stone, it glimmers brilliantly blue and purple. When combined with other Mythril stones, it can be used for equipment.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Myhtril Gen", "Very lightweight and surprisingly strong, further refinement will make it even stronger.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Mythril Crystal", "Incredibly light-weight and strong, it makes the ideal base metal for equipment.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Power Shard", "A deep blue metal shard, it gravitate to other power shards to form stronger structures.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Power Stone", "A strong, heavy stone, it increases strength when held.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Power Gen", "A hevy gem that makes one feel more powerful just by looking at it. Increases the strength of near by objects.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Power Crystal", "Holding the crystal makes one feel nearly indestructible. It greatly increases the strength of everything near it.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Rememberance Shard", "It feels soft and yielding to the touch. It invokes feelings of nostalgia.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Rememberance Stone", "It increases memory strength, it is rumoured to give brief glimpses of the past.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Rememberance Gem", "Can causes involuntary recall of past memories. Voices can sometimes be heard from it.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Rememberance Crystal", "It vastly increases the strength of memories when held. It often reveals glimpses of the past. it is rumoured to be able to revert objects to their previous forms.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Secret Crystal", "Said to be unbrekable, the crystal's core is permanently obscurred beneath a strong multi-coloured glow.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))

ItemLibrary.AddItem(ScriptedItem("Serenity Shard", "N/A", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Serenity Stone", "N/A", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Serenity Gem", "N/A", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Serenity Crystal", "N/A", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))


ItemLibrary.AddItem(ScriptedItem("Prism Shard", "A shard that splits light into 7 colours.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Prism Gem", "A gem that warps light.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Prism Crystal", "A heavy crystal that warps and amplifies light.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50))
ItemLibrary.AddItem(ScriptedItem("Enriched Etherium", "Highly purified Etherium, possesing superior strength to impure Etherium.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 50000))
ItemLibrary.AddItem(ScriptedItem("Enriched Etherium Ore", "Processed Etherium Ore that can be turned into Etherium.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 5000))
ItemLibrary.AddItem(ScriptedItem("Etherium", "An extremely rare metal with incredible strength and resilience.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 20000))
ItemLibrary.AddItem(ScriptedItem("Etherium Ore", "An impure and rare ore that can be processed into Etherium.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 1000))
ItemLibrary.AddItem(ScriptedItem("Purified Etherium Ore", "Highly refined Etherium ore that can under go transmutation into Etherium.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 2500))
ItemLibrary.AddItem(ScriptedItem("Raw Etherium Ore", "Extrmely impure Etherium ore. It must be highly refined to be usable.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 500))
ItemLibrary.AddItem(ScriptedItem("Raw Etherium", "Transmuted Etherium ore. Further purification is needed to maximize the metal's strength.", ItemType.SynthesisMaterial, ItemType.SynthesisMaterial, 0, ItemUsage.Unusable, 0, 1000))

#Potions
ItemLibrary.AddItem(HealingItem("Potion", "Restores a small amount of HP.", ItemType.HealingItem, ItemType.HealingItem, ItemFlag.Consumable, ItemUsage.UsableInBattle | ItemUsage.UsableOutsideOfBattle, ActionTargets.Any, 100, 0, {'HP': (500, True)}))
ItemLibrary.AddItem(HealingItem("Hi-Potion", "Restores HP.", ItemType.HealingItem, ItemType.HealingItem, ItemFlag.Consumable, ItemUsage.UsableInBattle | ItemUsage.UsableOutsideOfBattle, ActionTargets.Any, 1000, 0, {'HP': (2000, True)}))
ItemLibrary.AddItem(HealingItem("Mega-Potion", "Fully restores HP.", ItemType.HealingItem, ItemType.HealingItem, ItemFlag.Consumable, ItemUsage.UsableInBattle | ItemUsage.UsableOutsideOfBattle, ActionTargets.Any, 5000, 0, {'HP': (1.0, False)}))

#Ethers
ItemLibrary.AddItem(HealingItem("Ether", "Restores a small amount of MP.", ItemType.HealingItem, ItemType.HealingItem, ItemFlag.Consumable, ItemUsage.UsableInBattle | ItemUsage.UsableOutsideOfBattle, ActionTargets.Any, 1000, 0, {'MP': (50, True)}))
ItemLibrary.AddItem(HealingItem("Hi-Ether", "Restores MP.", ItemType.HealingItem, ItemType.HealingItem, ItemFlag.Consumable, ItemUsage.UsableInBattle | ItemUsage.UsableOutsideOfBattle, ActionTargets.Any, 4000, 0, {' MP': (200, True)}))
ItemLibrary.AddItem(HealingItem("Mega-Ether", "Fully restores MP.", ItemType.HealingItem, ItemType.HealingItem, ItemFlag.Consumable, ItemUsage.UsableInBattle | ItemUsage.UsableOutsideOfBattle, ActionTargets.Any, 10000, 0, {'MP': (1.0, False)}))

ItemLibrary.AddItem(HealingItem("Elixir", "Restores HP.", ItemType.HealingItem, ItemType.HealingItem, ItemFlag.Consumable, ItemUsage.UsableInBattle | ItemUsage.UsableOutsideOfBattle, ActionTargets.Any, 10, 0, {'HP': (1.0, False), 'MP': (1.0, False), 'SP': (1.0, False)}))
ItemLibrary.AddItem(HealingItem("Megalixir", "Restores HP.", ItemType.HealingItem, ItemType.HealingItem, ItemFlag.Consumable, ItemUsage.UsableInBattle | ItemUsage.UsableOutsideOfBattle, ActionTargets.AnyParty, 10, 0, {'HP': (1.0, False), 'MP': (1.0, False), 'SP': (1.0, False)}))

#StatBoosters
ItemLibrary.AddItem(PermanentStatBooster("Power Boost", "It surges with incredible power. You feel stronger just by touching it.", ItemType.StatBoostingItem, ItemFlag.Consumable, 25000, 0, {Stat.Strength: 2}))
ItemLibrary.AddItem(PermanentStatBooster("Defense Boost", "It's suface is incredibly hard, and feels nearbly unbrekable. You feel more resilient just holding it.", ItemType.StatBoostingItem, ItemFlag.Consumable, 25000, 0, {Stat.Vitality: 2}))
ItemLibrary.AddItem(PermanentStatBooster("Magic Boost", "Sparkling with pure magical essense, your mind feels clearler when holding it.", ItemType.StatBoostingItem, ItemFlag.Consumable, 25000, 0, {Stat.Magic: 2}))
ItemLibrary.AddItem(PermanentStatBooster("HP Boost", "Despite it's high level of elasticity, it feels very difficult to break. You feel energized when holding it.", ItemType.StatBoostingItem, ItemFlag.Consumable, 25000, 0, {Stat.HP: 25}))
#ItemLibrary.AddItem(ItemTest("Rainbow Crystal", "Glitters brilliantly in 7 colours"))



'''class HealingItem(UsableItem):
    def __init__(self, name, description, itemclass, value, healmap, flags = 0):
        Item.__init__(self, name, description, flags, itemclass, value)
        self.HealMap = healmap
        #self.UseInBattle = false
    def Use(targets):
        for target in targets:
            if ('HP' in self.HealMap):
                HealRate = self.HealMap['HP'][0]
                AbsoluteHeal = self.HealMap['HP'][1]
                if (AbsoluteHeal):
                    target.SetHP(int(target.GetHP() + HealRate))
                else:
                    target.SetHP(int(target.GetHP() + target.GetInBattleStat(Stat.HP) * HealRate))

            if ('MP' in self.HealMap):
                HealRate = self.HealMap['MP'][0]
                AbsoluteHeal = self.HealMap['MP'][1]
                if (AbsoluteHeal):
                    target.SetHP(int(target.GetMP() + HealRate))
                else:
                    target.SetHP(int(target.GetMP() + target.GetInBattleStat(Stat.MP) * HealRate))

            if ('SP' in self.HealMap):
                HealRate = self.HealMap['SP'][0]
                AbsoluteHeal = self.HealMap['SP'][1]
                if (AbsoluteHeal):
                    target.SetHP(int(target.GetSP() + HealRate))
                else:
                    target.SetHP(int(target.GetSP() + target.GetInBattleStat(Stat.SP) * HealRate))
    def BattleUse(users, targets, field):
        bcharvec = BaseCharacterVector()
        for target in targets:
            bcharvec.append(target.GetCharacter().GetCharacterPtr())
        #self.UseInBattle = true
        self.Use(bcharvec)
        #self.UseInBattle = false
    def Clone(self):
        return copy.deepcopy(self)
        '''
