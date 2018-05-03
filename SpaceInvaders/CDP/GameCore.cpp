#include "Headers/GameCore.h"


using namespace CDP;

// Richard

GameCore::GameCore()
{
}


GameCore::~GameCore()
{
}

void GameCore::Instantiate(nlohmann::json& jsonObject)
{
	if (jsonObject.find("scene") != jsonObject.end())
	{
		for (nlohmann::json::iterator it = jsonObject["scene"].begin(); it != jsonObject["scene"].end(); ++it)
		{
			GameObject(it.value());
		}
	}
}

void GameCore::Destroy(GameObject* go)
{
	//search and destroy
}

// end

// Stian

// end
