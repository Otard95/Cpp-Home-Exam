// SpaceInvaders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include "nlohmann_json/json.hpp"
#include "CDP/Headers/GameObject.h"
#include "CDP/Headers/GameCore.h"
#include <iostream>


int main(int argc, char** argv)
{
	std::ifstream i("json_game_save_draft.json");
	nlohmann::json j;
	i >> j;

	CDP::GameCore gameCore = CDP::GameCore::instance();
	gameCore.Instantiate(j);
	std::cout << "MAIN" << std::endl;
	system("pause");
    return 0;
}

