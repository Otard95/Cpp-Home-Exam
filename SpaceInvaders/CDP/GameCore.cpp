#include "Headers/GameCore.h"
#include <iostream>


using namespace CDP;

// Richard

GameCore::GameCore()
{
}


GameCore::~GameCore()
{
	m_transforms.clear();
	m_colliders.clear();
	m_rigidbodies.clear();
	m_sprites.clear();
	m_game_objects.clear();
	
}

void GameCore::Instantiate(nlohmann::json& jsonObject)
{
	if (jsonObject.find("scene") != jsonObject.end())
	{
		for (nlohmann::json::iterator it = jsonObject["scene"].begin(); it != jsonObject["scene"].end(); ++it)
		{
			m_game_objects.emplace_back(GameObject(it.value()["name"].get<std::string>()));
			
			if(it.value().find("components") != it.value().end())
			{
				for (nlohmann::json::iterator comp = it.value()["components"].begin(); comp != it.value()["components"].end(); ++comp)
				{
					AddComponent(m_game_objects.back(), comp.key(), comp.value());
				}
			}		
		}
	}
}

void GameCore::Destroy(GameObject* go)
{
	//search and destroy
}

void GameCore::AddComponent(GameObject& go, std::string type, nlohmann::json& jo)
{

	if(type == "Transform")
	{
		auto x = jo["pos"]["x"];
		auto y = jo["pos"]["y"];
		CreateTransform(go.GetComponents(), go);
		m_transforms.back().SetPosition(x, y);
	}
	else if(type == "Sprite")
	{
		const auto texture = jo["texture"];
		CreateSprite(go.GetComponents(), go, texture);
	}
	else if (type == "Collider")
	{
		
		CreateCollider(go.GetComponents(), go);
	}
	else if (type == "Rigidbody")
	{
		
		CreateRigidbody(go.GetComponents(), go);

	}
	
	
	//const std::string str = it.key();

	//if (it.key() == "PlayerControls")
	//{
	//	//TO DO: add player component.
	//}
	//else if (it.key() == "Transform")
	//{
	//	CreateCollider()
	//}
}

// end

// Stian

void GameCore::CreateTransform(std::vector<Component*> &components, GameObject& go )
{
	m_transforms.emplace_back(components, go);
	components.push_back(&m_transforms.back());
}

void GameCore::CreateSprite(std::vector<Component*> &components, GameObject& go, std::string texture)
{
	m_sprites.emplace_back(components, go, texture);
	components.push_back(&m_sprites.back());
}

void GameCore::CreateRigidbody(std::vector<Component*>& components, GameObject& go)
{
	m_rigidbodies.emplace_back(components, go, m_colliders.back(), m_transforms.back());
	components.push_back(&m_rigidbodies.back());
}

void GameCore::CreateCollider(std::vector<Component*> &components, GameObject& go)
{
	m_colliders.emplace_back(components, go, m_transforms.back());
	components.push_back(&m_colliders.back());
}
// end
