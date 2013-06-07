#pragma once
#ifndef _PYTHONGAMEINSTANCE_H_
#define _PYTHONGAMEINSTANCE_H_
#include <GameInstance.h>
#include <boost/python.hpp>
namespace Game
{
	BOOST_PYTHON_MODULE(GameInstanceModule)
	{
		class_<GameInstance, boost::noncopyable>("GameInstance", no_init)
			.def("GetItemLibrary", &GameInstance::GetItemLibrary, return_value_policy<reference_existing_object>())
			.def("GetActionLibrary", &GameInstance::GetActionLibrary, return_value_policy<reference_existing_object>())
			.def("MakeNewGame", &GameInstance::MakeNewGame)
			.def("GetPlayerParty", &GameInstance::GetPlayerParty, return_value_policy<reference_existing_object>())
			.def("GetCharacterLibrary", &GameInstance::GetCharacterLibrary, return_value_policy<reference_existing_object>())
			//.def("", &GameInstance::)
			//.def("", &GameInstance)
			;
	}
}

#endif