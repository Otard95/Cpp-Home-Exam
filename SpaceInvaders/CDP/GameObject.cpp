#include "Headers/GameObject.h"
#include <iostream>

using namespace CDP;

GameObject::GameObject(nlohmann::json& jsonObject)
{
	m_name = jsonObject["name"].get<std::string>();

	int i = 1;

	for (nlohmann::json::iterator it = jsonObject["components"].begin(); it != jsonObject["components"].end(); ++it)
	{
		const std::string str = it.key();

		if(it.key() == "PlayerControls")
		{
						
		}
	}
	std::cout << m_name << std::endl;
}

GameObject::~GameObject()
{
}

void CDP::GameObject::Update()
{
	if (m_physics_triplet)
	{
		// component force update
	}

	// for each component -> update
}

void CDP::GameObject::Instantiate(nlohmann::json& jsonObject)
{
	//m_game_objects.resize(10);

	if (jsonObject.find("scene") != jsonObject.end())
	{
		for (nlohmann::json::iterator it = jsonObject["scene"].begin(); it != jsonObject["scene"].end(); ++it)
		{
			//m_game_objects.push_back(GameObject(it.value()));		
			GameObject(it.value());
		}
	}
}

void CDP::GameObject::Destroy(GameObject* go)
{
	//search and destroy
}
