// SpaceInvaders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include "nlohmann_json/json.hpp"
#include "CDP/Headers/GameObject.h"
#include "CDP/Headers/GameCore.h"


int main()
{
	std::ifstream i("json_game_save_draft.json");
	nlohmann::json j;
	i >> j;

	CDP::GameCore::Instantiate(j);
    return 0;
}

