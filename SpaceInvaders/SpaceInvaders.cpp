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
	std::ifstream i("game_settings.json");
	nlohmann::json j;
	i >> j;

	CDP::GameCore& gameCore = CDP::GameCore::Instance();
	gameCore.Initialize(j);
	gameCore.Run();
	
	std::cout << "\nPress Enter to exit the game." << std::endl;
	std::cin.get();
	
    return 0;
}

