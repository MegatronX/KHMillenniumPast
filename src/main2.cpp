#include <string>
#include <iostream>
#include <sfml/Graphics.hpp>
#include <sfml/System.hpp>
#include <Engine.h>
#include <boost/python.hpp>
#include <GameInstance.h>
#include <Graphics/Screens/BasicRMLScreen.h>
#include <Graphics/Rocket/PositionTransformer.h>
#include <Graphics/Rocket/FaderTransform.h>
#include <graphics/Screens/TitleScreen.h>
#include <Graphics/Sprites/Sprite.h>
#include <Graphics/Sprites/AnimatedSprite.h>
#include <Graphics/Animation/FrameAnimation.hpp>
#include <minigames//triad/Deck.h>
#include <character/StatsManager.h>
#include <character/Party.h>

#include <components/ElementWeightComponent.h>
#include <components/StatusEffectivenessComponent.h>
#include <components/ElementEffectivenessComponent.h>
#include <components/ApplyEffectComponent.h>

#include <battle/BattleField.h>
#include <battle/mechanics/Mechanics.h>
#include <actions/Attack.h>
#include <components/ApplyEffectComponent.h>
#include <battle/mechanics/ATBTurnGenerator.h>

#include <Graphics/Screens/MapViewLayer.h>
#include <graphics/Screens/GameMapViewScreen.h>

#include <LTBL/Light/LightSystem.h>
#include <LTBL/Light/Light_Point.h>
#include <LTBL/Utils.h>

#include <Graphics/messaging/MessageCenter.h>
#include <battle/DamageCalculationComponent.h>

#include <Math/MathFormula.h>

#include <character/CharacterSpawner.h>
#include <Graphics/Transformers/BaseTransform.h>
#include <Graphics/Transformers/TextTransforms.h>

#include <thor/Shapes.hpp>
#include <thor/Graphics.hpp>
#include <Graphics/Shapes/Shapes.h>

#include <Graphics/Screens/CharacterBattleStatusVisualizer.h>

using namespace std;
using namespace Game;


static const std::string CommandHead = "from EngineModule import *\nfrom CharacterModule import *\nfrom EntityModule import *\n";
void CommandLineIssuer(Engine* engine)
{
	std::string Command;//[256];
	while(true)
	{
		std::getline(std::cin, Command);
		try
		{
			engine->GetPythonScripter().RunString(CommandHead + Command);
		}
		catch (boost::python::error_already_set)
		{
			PyErr_Print();
		}
		
	}
}

void BattleTest(Engine& GameEngine, GameInstance& GameInst)
{
	int arStats[Character::StatCount] = {9999, 999, 37, 32, 29, 28, 24, 34, 52, 40, 40, 200, 49};
	arStats[Character::Speed] = 128;
	std::string BattleCompIndex = "BattleCharacterComponent";
	auto Arian = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Arian", arStats));

	int crStats[Character::StatCount] = {314, 44, 39, 32, 31, 28, 24, 34, 47, 25, 20, 200, 49};
	crStats[Character::Speed] = 180;
	auto Ceira = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Ceira", crStats));

	auto ele = Arian->GetComponentAs<Components::ElementEffectivenessComponent*>("ElementEffectivenessComponent");
	ele->SetEffectivness(Elements::Ice, 2.f);

	int corrStat[] = {624, 34, 37, 32, 29, 28, 24, 34, 40, 20, 20, 200, 49};
	corrStat[Character::Speed] = 128;
	auto Corrupted = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Corrupted1", corrStat));

	int xaxStat[] = {624, 39, 47, 37, 39, 34, 41, 154, 150, 130, 110, 210, 59};
	auto Xax = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Xaxion", xaxStat));

	Character::bparty_ptr Party(new Character::BaseParty("PlayerParty"));

	Party->AddMember(Arian, "Arian");
	//Arian->SetParty(Party.get());
	Party->AddMember(Ceira, "Ceira");
	//Ceira->SetParty(Party.get());
	Character::bparty_ptr EnemyParty(new Character::BaseParty("EnemyParty"));
	EnemyParty->AddMember(Corrupted, Corrupted->GetName());
	EnemyParty->AddMember(Xax, Xax->GetName());

	auto bchar = boost::shared_ptr<Battle::BattleCharacterComponent>(new Battle::BattleCharacterComponent(Arian.get(), nullptr, Party.get()));
	Arian->RegisterComponent(BattleCompIndex, bchar);
	Arian->GetComponentAs<Character::StatsManager*>("StatsManager")->SyncAllBattleStats();

	bchar = boost::shared_ptr<Battle::BattleCharacterComponent>(new Battle::BattleCharacterComponent(Ceira.get(), nullptr, Party.get()));
	Ceira->GetComponentAs<Character::StatsManager*>("StatsManager")->SyncAllBattleStats();
	Ceira->RegisterComponent(BattleCompIndex, bchar);

	Corrupted->GetComponentAs<Character::StatsManager*>("StatsManager")->SyncAllBattleStats();
	bchar = boost::shared_ptr<Battle::BattleCharacterComponent>(new Battle::BattleCharacterComponent(Corrupted.get(), nullptr, EnemyParty.get()));
	Corrupted->RegisterComponent(BattleCompIndex, bchar);

	Xax->GetComponentAs<Character::StatsManager*>("StatsManager")->SyncAllBattleStats();
	bchar = boost::shared_ptr<Battle::BattleCharacterComponent>(new Battle::BattleCharacterComponent(Xax.get(), nullptr, EnemyParty.get()));
	Xax->RegisterComponent(BattleCompIndex, bchar);

	Battle::BattleField Field(Party, EnemyParty);
	Field.PreBattlePhase();
	Field.BattlePhase();

	//Field.GetTurnGenerator()->GenerateNextCharacter(520);

	int ContinueBattle = -10;
	auto start = GameEngine.GetTime();
	//while(true)
	//	sf::sleep(sf::milliseconds(50));
	try
	{
		auto haste = GameInst.GetSELibrary().GetStatusEffectClone("Haste");
		auto reflect = GameInst.GetSELibrary().GetStatusEffectClone("Reflect");


		Corrupted->GetStatusEffectsManager().AddStatusEffect(reflect, reflect->GetRecommendedTicks());
		auto comp0 = reflect->GetComponent("FinalizeTargetsModifier");
		auto hcomp = haste->GetComponentAs<Components::ApplyEffectComponent*>("ApplyEffectComponent");
		//hcomp->Apply(Arian.get());
		Arian->GetStatusEffectsManager().AddStatusEffect("Haste", 11);
		Ceira->GetStatusEffectsManager().AddStatusEffect("Storm Drain", 9);
		Ceira->GetStatusEffectsManager().AddStatusEffect("Ocean Guardian", 14);
	}
	catch (const boost::python::error_already_set& ex)
	{
		PyErr_Print();
		std::string exp = "";
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << "\n";
	}

	try
	{
		for(;ContinueBattle < 0; ++ContinueBattle)
		{
			//Battle Test

			auto ww = GameInst.GetActionLibrary().GetAction("White Wind");
			auto wwdc = ww->GetComponentAs<::Game::Battle::DamageCalculationComponent*>("DamageCalculatorComponent");
			ww->Users.AddCharacter(Arian.get());
			ww->Targets.AddCharacter(Corrupted.get());
			int dmg = wwdc->CalculateDamage(*ww, *(ww->Targets.GetFirst()->AttachedCharacter), Field.GetMechanics());

			auto mgd = GameInst.GetActionLibrary().GetAction("Megiddo Flame");

			auto blizzard = GameInst.GetActionLibrary().GetAction("Blizzard");
			blizzard->Targets.AddCharacter(Xax.get());
			blizzard->Targets.AddCharacter(Arian.get());
			blizzard->Users.AddCharacter(Arian.get());
			//blizzard->Users.AddCharacter(Ceira.get());
			auto elecomp = blizzard->GetComponentAs<Components::ElementWeightComponent*>("ElementalWeightComponent");

			auto megiddo = GameInst.GetActionLibrary().GetAction("Megiddo Flame");
			wwdc = megiddo->GetComponentAs<::Game::Battle::DamageCalculationComponent*>("DamageCalculatorComponent");

			megiddo->Targets.AddCharacter(Corrupted.get());
			megiddo->Users.AddCharacter(Arian.get());
			megiddo->Users.AddCharacter(Ceira.get());

			dmg = wwdc->CalculateDamage(*megiddo, *(megiddo->Targets.GetFirst()->AttachedCharacter), Field.GetMechanics());

			Field.GetMechanics().ProcessActionDefault(*blizzard);
			std::vector<int> dmgs;
			for (auto trg = blizzard->Targets.GetGroup().begin(); trg != blizzard->Targets.GetGroup().end(); ++trg)
			{
				auto acttarg = trg->second;
				auto atk = dynamic_cast<Game::Actions::Attack*>(acttarg.action.get());
				dmgs.push_back(atk->GetCalculatedDamage());
			}
			Field.GetMechanics().ProcessActionDefault(*megiddo);

			for (auto trg = megiddo->Targets.GetGroup().begin(); trg != megiddo->Targets.GetGroup().end(); ++trg)
			{
				auto acttarg = trg->second;
				auto atk = dynamic_cast<Game::Actions::Attack*>(acttarg.action.get());
				dmgs.push_back(atk->GetCalculatedDamage());
			}
			auto water = GameInst.GetActionLibrary().GetAction("Wateraga");
			water->Targets.AddCharacter(Corrupted.get());
			water->Targets.AddCharacter(Arian.get());
			water->Users.AddCharacter(Arian.get());

			Field.GetMechanics().ProcessActionDefault(*water);

			for (auto trg = water->Targets.GetGroup().begin(); trg != water->Targets.GetGroup().end(); ++trg)
			{
				auto acttarg = trg->second;
				auto atk = dynamic_cast<Game::Actions::Attack*>(acttarg.action.get());
				dmgs.push_back(atk->GetCalculatedDamage());
			}
			dmgs.clear();

			auto &sm = Arian->GetStatsManager();
			sm.RemapStat(Character::Stat::HP, Character::Stat::MP);
			sm.RemapStat(Character::Stat::MP, Character::Stat::HP);

			int AHp = sm.GetCurrentHP();
			int AMp = sm.GetCurrentMP();

			sm.ClearRemappings();

			int AHp2 = sm.GetCurrentHP();
			int AMp2 = sm.GetCurrentMP();

		}
	}
	catch (const boost::python::error_already_set& ex)
	{
		PyErr_Print();
		std::string exp = "";
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << "\n";
	}
}

#include <Graphics/Camera/Camera.h>

#include <items/EquipmentComponent.h>
#include <items/Item.h>
using namespace Items;

item_ptr MakeTestArmor()
{
	int statAdd[Character::StatCount] = {222, 99, 37, 32, 29, 28, 24, 34, 52, 40, 40, 200, 49};
	item_ptr armor = item_ptr(new Item("Armor", "Legendary Armor", 10000000));
	armor->RegisterComponent(EquipmentComponentIndex, boost::shared_ptr<EquipmentComponent>(new EquipmentComponent(armor.get())));
	armor->RegisterComponent(StatAdderIndex, boost::shared_ptr<Components::StatComponent<int>>(new Components::StatComponent<int>(armor.get(), statAdd)));

	boost::unordered_map<Elements::Element, float> eleWeight;
	eleWeight[Elements::Air] = 0.3;
	eleWeight[Elements::Fire] = 0.5;

	armor->RegisterComponent(ElementEffectAdderIndex, boost::shared_ptr<Components::ElementEffectivenessComponent>(new Components::ElementEffectivenessComponent(armor.get(), eleWeight)));

	boost::unordered_map<std::string, float> effTable;
	effTable["Slow"] = 1.f;
	armor->RegisterComponent(StatusEffectAdderIndex, boost::shared_ptr<Components::StatusEffectivenessComponent>(new Components::StatusEffectivenessComponent(armor.get(), effTable)));

	float statMult[Character::StatCount] = {0.1f, 0.f, 0.f, 0.f, 0.1f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	armor->RegisterComponent(StatMultIndex, boost::shared_ptr<Components::StatComponent<float>>(new Components::StatComponent<float>(armor.get(), statMult)));
	return armor;
}

int mainxxxxx()
{
	try
	{
		sf::Vector2i Res(800, 600);
		sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
		GameWindow.setFramerateLimit(100);

		Engine GameEngine("Config.xml", &GameWindow, Res);
		Game::GameInstance GameInst(GameEngine, false);

		GameInst.LoadSave("../../../resources/saves/sav1.xml", "Save0");

		sf::Thread CommandThread(&CommandLineIssuer, &GameEngine);
		CommandThread.launch();

		int arStats[Character::StatCount] = {9999, 806, 37, 32, 29, 28, 24, 34, 52, 40, 40, 200, 49};
		arStats[Character::Speed] = 28;
		std::string BattleCompIndex = "BattleCharacterComponent";
		auto Arian = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Arian", arStats));
		Arian->GetStatsManager().SetCurrentHP(5890);
		Arian->SetProperty("Type", "Arian");
		Arian->SetProperty("DisplayName", "Arian");
		int crStats[Character::StatCount] = {8591, 999, 37, 32, 29, 28, 24, 34, 52, 40, 40, 200, 49};
		crStats[Character::Speed] = 27;
		auto Ceira = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Ceira", crStats));

		int brStats[Character::StatCount] = {8591, 999, 37, 32, 29, 28, 24, 34, 52, 40, 40, 200, 49};
		auto Bartz = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Bartz", brStats));

		int carStats[Character::StatCount] = {82633, 999, 9937, 32, 29, 28, 24, 34, 52, 40, 40, 200, 49};
		auto Cara = boost::shared_ptr<Character::BaseCharacter>(new Character::BaseCharacter("Cara", carStats));

		//Arian->GetStatusEffectsManager().AddStatusEffect("Haste", 7);

		auto ChSpawn = boost::shared_ptr<Character::CharacterSpawner>(new Character::CharacterSpawner(Arian.get()));
		boost::unordered_map<Character::EntryID, int> Spawns;
		Spawns[Character::EntryID("Red Dragon", 83)] = 2;
		Spawns[Character::EntryID("Red Dragon", 56)] = 2;
		Spawns[Character::EntryID("Omega Weapon", 100)] = 2;

		auto party = ChSpawn->CreateParty("EnemyParty", Spawns);

		GameInst.GetPlayerParty().AddCharacter("Arian", Arian);

		auto lyptr = boost::shared_ptr<Game::Graphics::Screens::GameMapViewScreen>(new Game::Graphics::Screens::GameMapViewScreen(&GameEngine, std::string("Traverse Point - Far Left.tmx"), sf::Vector2f(20 * 32, 13* 32), 5, &GameWindow, std::string("Station"), GameInst.GetPlayerParty().GetPartyMembersInOrder()[0]->GetName(), GameEngine.GetUID()));
		GameEngine.GetScreenManager().AddScreen(lyptr, 0);
		sf::Uint32 time = GameEngine.GetTime();
		sf::Uint32 lastHPSet = time;

		std::string effects[] = {"Juggernaut", "Haste", "Haste+"};

		bool added = false;
		for(bool Running = true; Running; time = GameEngine.GetTime())
		{
			GameEngine.HandleWindowEvents(GameWindow, Running);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C) && time > (lastHPSet + 500))
			{
				lastHPSet = time;
				int prevHP = Arian->GetStatsManager().GetCurrentHP();
				int newHP = GameEngine.GetRandomInt(1, Arian->GetStatsManager().GetBattleStat(Character::Stat::HP));
				Arian->GetStatsManager().SetCurrentHP(newHP);
				std::cout << "New HP Ratio " << (static_cast<float>(newHP) / static_cast<float>(Arian->GetStatsManager().GetBattleStat(Character::Stat::HP))) << "\n";
				int newSP = GameEngine.GetRandomInt(1, Arian->GetStatsManager().GetBattleStat(Character::Stat::SP));
				Arian->GetStatsManager().SetCurrentSP(newSP);
				int effectIdx = GameEngine.GetRandomInt(0, (sizeof(effects) / sizeof(std::string)) - 1);
				bool rmv = static_cast<bool>(GameEngine.GetRandomInt(0, 1));
				int index = GameEngine.GetRandomInt(1, 6);
				if (!added)
				{
					Arian->GetStatusEffectsManager().AddStatusEffect("Haste", 7);
					added = true;
				}
				else
				{
					Arian->GetStatusEffectsManager().RemoveStatusEffect("Haste");
					Arian->GetStatusEffectsManager().AddStatusEffect("Haste", 7);
					added = false;
				}
				/*for (int i = 0; i < index; ++i)
				{
					effectIdx = GameEngine.GetRandomInt(0, (sizeof(effects) / sizeof(std::string)) - 1);
					rmv = static_cast<bool>(GameEngine.GetRandomInt(0, 1));
					if (rmv)
						Arian->GetStatusEffectsManager().RemoveStatusEffect(effects[effectIdx]);
					else
						Arian->GetStatusEffectsManager().AddStatusEffect(effects[effectIdx], 7);

					std::cout << "SE: " << effects[effectIdx] << " | Added: " << !rmv << "\n";
				}*/
			}
			//Update
			GameEngine.Update(time);
			//Clear
			GameWindow.clear();
			//Draw
			GameEngine.Draw(GameWindow);
			//Display
			GameWindow.display();

		}
		CommandThread.terminate();
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << "\n";
	}
	catch (boost::python::error_already_set)
	{
		PyErr_Print();
		std::string exp = "";
	}

	return EXIT_SUCCESS;
}

int main_()
{
	//Use to test sf::view manipulation

	try
	{
		sf::Vector2i Res(800, 600);
		sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
		GameWindow.setFramerateLimit(60);
		Engine GameEngine("Config.xml", &GameWindow, Res);
		Game::GameInstance GameInst(GameEngine, false);

		sf::Thread CommandThread(&CommandLineIssuer, &GameEngine);
		CommandThread.launch();
		sf::Texture kida;
		kida.loadFromFile("..\\..\\..\\resources\\Graphics\\Sprites\\kida.png");
		sf::Sprite KidaPlat(kida);

		sf::Texture yuko;
		yuko.loadFromFile("..\\..\\..\\resources\\Graphics\\Sprites\\Enemies\\Yuko.gif");

		sf::Sprite yukoSp(yuko);

		yukoSp.setPosition(kida.getSize().x * 0.3f, kida.getSize().y * 0.3f);

		sf::Uint32 time = GameEngine.GetTime();

		::Graphics::Camera cam;
		sf::View view;
		sf::View defaultView = GameWindow.getView();
		for(bool Running = true; Running; time = GameEngine.GetTime())
		{

			GameEngine.HandleWindowEvents(GameWindow, Running);
			GameEngine.Update(time);
			GameWindow.clear();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				cam.Rotate(sf::Vector3f(1.f, 0.f, 0.f));
				view.rotate(0.8f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				cam.Rotate(sf::Vector3f(-1.f, 0.f, 0.f));
				view.rotate(-0.8f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				cam.Rotate(sf::Vector3f(0.f, 1.f, 0.f));
				view.setSize(view.getSize().x, view.getSize().y -5.f);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				cam.Rotate(sf::Vector3f(0.f, -1.f, 0.f));
				view.setSize(view.getSize().x, view.getSize().y + 5.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				cam.Rotate(sf::Vector3f(0.f, 0.f, 1.f));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			{
				cam.Rotate(sf::Vector3f(0.f, 0.f, -1.f));
			}
			auto trans = view.getTransform();
			auto pos = sf::Vector2f(yukoSp.getPosition());
			auto transpos = trans.transformPoint(pos);

			pos = sf::Vector2f(transpos.x * pos.x, transpos.y * pos.y);

			yukoSp.setPosition(pos);
			//cam.Set();
			GameWindow.setView(view);
			//GameEngine.Draw(KidaPlat);
			GameWindow.draw(KidaPlat);
			GameWindow.setView(defaultView);
			GameWindow.draw(yukoSp);

			//spr.Draw(GameWindow);
			//aspr.Draw(GameWindow);
			//ts->Draw(GameWindow);
			GameWindow.display();

			yukoSp.setPosition(pos);
		}

	}
	catch(std::exception ex)
	{

	}
	return EXIT_SUCCESS;
}

int mainlight()
{
	try
	{
		sf::Vector2i Res(800, 600);
		sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
		GameWindow.setFramerateLimit(90);
		Engine GameEngine("Config.xml", &GameWindow, Res);
		Game::GameInstance GameInst(GameEngine, false);

		sf::Thread CommandThread(&CommandLineIssuer, &GameEngine);
		CommandThread.launch();

		sf::Uint32 time = GameEngine.GetTime();

		ltbl::LightSystem ls(AABB(Vec2f(0.0f, 0.0f), Vec2f(static_cast<float>(800), static_cast<float>(600))), &GameWindow, GameEngine.GetContentManager().GetShaderDirectory() + "lightFin.png", GameEngine.GetContentManager().GetShaderDirectory() + "lightAttenuationShader.frag");

		// Create a light
		ltbl::Light_Point* testLight = new ltbl::Light_Point();
		testLight->m_intensity = 2.0f;
		testLight->m_color.g = 0.f;
		testLight->m_color.r = 0.7f;
		testLight->m_center = Vec2f(200.0f, 200.0f);
		testLight->m_radius = 600.0f;
		testLight->m_size = 15.0f;
		testLight->m_spreadAngle = ltbl::pifTimes2;
		testLight->m_softSpreadAngle = 0.0f;
		testLight->CalculateAABB();

		testLight->m_bleed = 0.4f;
		testLight->m_linearizeFactor = 0.2f;

		ls.AddLight(testLight);

		testLight->SetAlwaysUpdate(true);

		// Create a light
		ltbl::Light_Point* testLight2 = new ltbl::Light_Point();
		testLight2->m_center = Vec2f(200.0f, 200.0f);
		testLight2->m_radius = 500.0f;
		testLight2->m_size = 30.0f;
		testLight2->m_color.r = 0.5f;
		testLight2->m_intensity = 1.5f;
		testLight2->m_spreadAngle = ltbl::pifTimes2;
		testLight2->m_softSpreadAngle = 0.0f;
		testLight2->CalculateAABB();

		ls.AddLight(testLight2);

		testLight2->SetAlwaysUpdate(false);


		ltbl::ConvexHull* testHull = new ltbl::ConvexHull();

		// Pre-calculate certain aspects

		std::vector<Vec2f> points;
		points.push_back(Vec2f(100.f, 100.f));
		points.push_back(Vec2f(200.f, 100.f));
		points.push_back(Vec2f(200.f, 150.f));

		testHull->m_vertices = points;

		testHull->CalculateNormals();
		testHull->CalculateAABB();

		testHull->SetWorldCenter(Vec2f(300.0f, 300.0f));

		testHull->m_renderLightOverHull = true;

		ls.AddConvexHull(testHull);

		sf::View view;
		view.setSize(sf::Vector2f(static_cast<float>(800), static_cast<float>(600)));
		view.setCenter(view.getSize() / 2.0f);

		auto lyptr = boost::shared_ptr<Game::Graphics::Screens::GameMapViewScreen>(new Game::Graphics::Screens::GameMapViewScreen(&GameEngine, std::string("Station1.tmx"), sf::Vector2f(20 * 32, 20 * 32), 2, &GameWindow, std::string("Station"), "Arian", GameEngine.GetUID()));
		GameEngine.GetScreenManager().AddScreen(lyptr);


		for(bool Running = true; Running; time = GameEngine.GetTime())
		{

			GameEngine.HandleWindowEvents(GameWindow, Running);
			GameEngine.Update(time);
			ls.SetView(view);
			sf::Vector2i mousePos = sf::Mouse::getPosition(GameWindow);
			//testLight2->IncCenter(ltbl::Vec2f(0.1f, 0.0f));
			// Update light
			testLight->SetCenter(Vec2f(static_cast<float>(mousePos.x), static_cast<float>(600) - static_cast<float>(mousePos.y)));

			GameWindow.clear();
			GameWindow.setView(view);
			GameEngine.Draw(GameWindow);
			// Calculate the lights
			ls.RenderLights();

			// Draw the lights
			ls.RenderLightTexture();

			//cam.Set();
			GameWindow.display();

		}
	}
	catch (std::exception e)
	{
	}
	return EXIT_SUCCESS;
}

int main_btest()
{
	sf::Vector2i Res(800, 600);
	sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
	GameWindow.setFramerateLimit(90);
	Engine GameEngine("Config.xml", &GameWindow, Res);
	Game::GameInstance GameInst(GameEngine, false);

	BattleTest(GameEngine, GameInst);
	sf::Thread CommandThread(&CommandLineIssuer, &GameEngine);
	CommandThread.launch();

	sf::Uint32 time = GameEngine.GetTime();

	Game::Graphics::Messaging::MessageCenter MC("Message.rml", &GameEngine);

	Game::Graphics::Messaging::MessageFormatting format;

	format.ScreenOffset = sf::Vector2f(20, 350);
	format.TextOffset = sf::Vector2f(190, 100);
	format.TextColor = sf::Color(128, 255, 190);
	format.ShadowText = true;
	format.ShadowColor = sf::Color::Red;
	format.ShadowOffset = sf::Vector2i(1, 1);
	format.CharacterSpeaking = true;
	format.Speaker = "ceira";
	format.Emotion = "content";
	MC.AddMessage("Ceira: Message test", "CeiraMsg1", format);
//	sf::Text t("Test");
//	t.setPosition(200, 160);
	try
	{
		for(bool Running = true; Running; time = GameEngine.GetTime())
		{

			GameEngine.HandleWindowEvents(GameWindow, Running);
			GameEngine.Update(time);
			MC.Update(time);
			GameWindow.clear();

			//GameEngine.Draw(GameWindow);
			MC.Draw(GameWindow);
			//GameWindow.draw(t);
			//cam.Set();
			GameWindow.display();
		}
	}
	catch (std::exception ex)
	{

	}
	return EXIT_SUCCESS;
}

int main222()
{
	try
	{
		sf::Vector2i Res(800, 600);
		sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
		GameWindow.setFramerateLimit(90);
		Engine GameEngine("Config.xml", &GameWindow, Res);
		Game::GameInstance GameInst(GameEngine, false);

		sf::Thread CommandThread(&CommandLineIssuer, &GameEngine);
		CommandThread.launch();

		sf::Uint32 time = GameEngine.GetTime();
		//Engine* engine, std::string &mapFile, sf::Vector2f &startPos, sf::RenderWindow* window, std::string &name, int layerID = -1
		auto lyptr = boost::shared_ptr<Game::Graphics::Screens::GameMapViewScreen>(new Game::Graphics::Screens::GameMapViewScreen(&GameEngine, std::string("Station1.tmx"), sf::Vector2f(20 * 32, 20 * 32), 2, &GameWindow, std::string("Station"), "Arian", GameEngine.GetUID()));
		//GameEngine.GetInput().AddKeyPressedEvent(boost::bind(::Graphics::Screens::MapViewLayer::HandleKeyPressed, ly.HandleKeyPressed, _1, _2, _3));

		::Graphics::Camera cam;
		sf::View view;
		sf::View defaultView = GameWindow.getView();
		GameEngine.GetScreenManager().AddScreen(lyptr);

		auto &lights = GameEngine.GetLightingSystem();
		//lights.AddLightPointToPrimary(400.f, Vec2f(400, 300), 500, 400, ltbl::pifTimes2, 0, 1, 1);
		std::vector<Vec2f> points;
		points.push_back(Vec2f(100.f, 100.f));
		points.push_back(Vec2f(200.f, 100.f));
		points.push_back(Vec2f(200.f, 150.f));

		//lights.AddConvexHullToPrimary(points, true, Vec2f(300.f, 300.f));



		ltbl::Light_Point* testLight2 = new ltbl::Light_Point();
		testLight2->m_center = Vec2f(200.0f, 200.0f);
		testLight2->m_radius = 50.0f;
		testLight2->m_size = 10.0f;
		//testLight2->m_color.r = 0.5f;
		//testLight2->m_color.g = 0.f;
		testLight2->m_intensity = 5.5f;
		testLight2->m_spreadAngle = ltbl::pifTimes2;
		testLight2->m_softSpreadAngle = 0.0f;
		testLight2->m_bleed = 0.0001f;
		testLight2->m_linearizeFactor = 0.4f;

		testLight2->CalculateAABB();

		lights.AddLightToPrimary(testLight2);
		testLight2->SetAlwaysUpdate(true);


		ltbl::Light_Point* testLight3 = new ltbl::Light_Point();
		testLight3->m_center = Vec2f(200.0f, 200.0f);
		testLight3->m_radius = 50.0f;
		testLight3->m_size = 10.0f;
		//testLight2->m_color.r = 0.5f;
		//testLight2->m_color.g = 0.f;
		testLight3->m_intensity = 5.5f;
		testLight3->m_spreadAngle = ltbl::pifTimes2;
		testLight3->m_softSpreadAngle = 0.0f;
		testLight3->m_bleed = 0.0001f;
		testLight3->m_linearizeFactor = 0.4f;

		testLight3->CalculateAABB();

		lights.AddLightToPrimary(testLight3);
		testLight3->SetAlwaysUpdate(true);


		for(bool Running = true; Running; time = GameEngine.GetTime())
		{

			GameEngine.HandleWindowEvents(GameWindow, Running);
			GameEngine.Update(time);
			GameWindow.clear();

			GameEngine.Draw(GameWindow);
			//cam.Set();
			GameWindow.display();
			auto &center = GameWindow.getView().getCenter();

			sf::Vector2i mousePos = sf::Mouse::getPosition(GameWindow);
			testLight2->SetCenter(Vec2f(static_cast<float>(mousePos.x) - 100, static_cast<float>(600) - static_cast<float>(mousePos.y)));
			testLight3->SetCenter(Vec2f(static_cast<float>(mousePos.x) + 100, static_cast<float>(600) - static_cast<float>(mousePos.y)));
		}
	}
	catch (std::exception e)
	{
	}
	return EXIT_SUCCESS;
}

int main_primary()
{
	try
	{
		sf::Vector2i Res(800, 600);
		sf::RenderWindow GameWindow(sf::VideoMode(Res.x, Res.y, 32), std::string("Kingdom Hearts Millennium Past"));
		GameWindow.setFramerateLimit(60);
		Engine GameEngine("Config.xml", &GameWindow, Res);
		Game::GameInstance GameInst(GameEngine, false);

		int x = 10;
		//Game::Graphics::GameRocket::BasicRMLScreen screen("Inv", "TitleScreen.rml", &GameEngine, GameEngine.GetUID());
		//Game::Graphics::Screens::TitleScreen TitleScr(&GameEngine);
		/*auto ceira = screen.GetDocument()->GetElementById(Rocket::Core::String("CeiraImg"));

		auto transformer = new Graphics::GameRocket::ElementTransformer(ceira);

		auto ptrans = Graphics::GameRocket::eletransform_ptr(new Graphics::GameRocket::PositionTransformer(transformer, sf::Vector2f(400, 200), GameEngine.GetTime(), GameEngine.GetTime() + 4000));
		auto ftrans = Graphics::GameRocket::eletransform_ptr(new Graphics::GameRocket::FaderTransform(nullptr, 255, 0, GameEngine.GetTime(), GameEngine.GetTime() + 5000));
		auto ftrans2 =  Graphics::GameRocket::eletransform_ptr(new Graphics::GameRocket::FaderTransform(nullptr, 0, 255, GameEngine.GetTime(), GameEngine.GetTime() + 5000));
		*/
		//auto obj = GameEngine.GetPythonScripter().RunFile("TitleScreen.py");

		/*ptrans->AddPostTransform(ftrans, 5000);
		ftrans->AddPostTransform(ftrans2, 5000);
		ftrans2->AddPostTransform(ftrans, 5000);
		transformer->AddTransformation(ptrans);
		//screen.AddNewTransform("Test Trans", transformer);
		transformer->SetTarget(ceira);
		Graphics::GameRocket::ElementTransformer* trans = new Graphics::GameRocket::ElementTransformer();
		Graphics::GameRocket::PositionTransformer* pTrans = new Graphics::GameRocket::PositionTransformer(GameEngine.GetTime(), GameEngine.GetTime() + 4000, sf::Vector2f(100, 0));
		Graphics::GameRocket::ElementTransformationInterface* col = new Graphics::GameRocket::FaderTransform(0, 255, GameEngine.GetTime(), GameEngine.GetTime() + 12000);

		trans->AddTransformation(pTrans);
		trans->AddTransformation(col);
		screen.AddNewTransform("Test Trans", trans);
		trans->SetTarget(screen.GetDocument()->GetElementById(Rocket::Core::String("CeiraImg")));
		pTrans->Initialize(trans);
		col->Initialize(trans);*/
		//trans->AddTransformation()
		//screen.Add





		/*auto SManager = Arian.GetComponentAs<Character::StatsManager*>("StatsManager");
		SManager->SyncAllBattleStats();
		auto SEManager = Arian.GetComponentAs<StatusEffects::StatusEffectsManager*>("StatusEffectsManager");
		auto haste = GameInst.GetSELibrary().GetStatusEffect("Haste");
		SEManager->AddStatusEffect("Haste", DEFAULT_TURNS);
		SEManager->RemoveStatusEffect("Haste");
		Game::MiniGames::Triad::Test(&GameEngine);*/
		sf::Thread CommandThread(&CommandLineIssuer, &GameEngine);
		CommandThread.launch();
		sf::Uint32 time = GameEngine.GetTime();
		std::cout << "First Time: " << time << std::endl;

		auto tx = GameEngine.GetContentManager().RequestTexture("Arian Test 2", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Guardian, GameEngine.GetTime());
		::Graphics::Sprite spr(tx);
		spr.SetPosition(100, 400);
		::Graphics::Sprite spr2(tx);
		spr2.SetPosition(100, 400);

		auto cr = GameEngine.GetContentManager().RequestTexture("Ceira", Cache::GameStyle::Main, Cache::World::Any, Cache::ResourceClass::Guardian, GameEngine.GetTime());

		::Graphics::AnimatedSprite aspr(cr, false);
		::Graphics::FrameAnimation idle;
		for (int i = 0; i < 4; ++i)
			idle.addFrame(1.f, sf::IntRect(128 * i, 0, 128, 128));

		aspr.GetAnimator().setDefaultAnimation(idle, sf::seconds(2.f));
		aspr.GetAnimator().addAnimation("Idle", idle, sf::seconds(2.f));
		aspr.GetAnimator().playAnimation("Idle");

		const Items::Item* bcryst = GameInst.GetItemLibrary().GetItemByName("Blazing Crystal");
		auto descr = bcryst->GetDescription();
		sf::Uint32 prev = time;

		sf::Clock frameClock;


		GameEngine.GetPythonScripter().RunFile("TitleScreen.py");
		auto ts = GameEngine.GetScreenManager().GetScreenStack("TitleScreen");
		try
		{

			for(bool Running = true; Running; time = GameEngine.GetTime())
			{

				GameEngine.HandleWindowEvents(GameWindow, Running);
				GameEngine.Update(time);
				GameWindow.clear(sf::Color::White);
				GameEngine.Draw(GameWindow);
				//spr.Draw(GameWindow);
				//aspr.Draw(GameWindow);
				//ts->Draw(GameWindow);
				GameWindow.display();


			}
		}
		catch (boost::python::error_already_set)
		{
			PyErr_Print();
			std::string exp = "";
		}
		GameWindow.close();
		CommandThread.terminate();
	}
	catch (const boost::python::error_already_set& ex)
	{
		PyErr_Print();
		std::string exp = "";
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << "\n";
	}

	int gf;
	std::cin >> gf;
	return EXIT_SUCCESS;
}