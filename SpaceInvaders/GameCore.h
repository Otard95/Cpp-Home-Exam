#pragma once
#include <vector>
#include "CDP/Headers/GameObject.h"

class GameCore
{
public:
	// Richard
	static GameCore& instance()
	{
		static GameCore gameCore;
		return gameCore;
	}

	std::vector<CDP::GameObject> m_game_objects;

	GameCore();
	~GameCore();
	// end

	// Stian

	//end
};

