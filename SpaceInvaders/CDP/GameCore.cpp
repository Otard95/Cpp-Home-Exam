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
					AddComponent(m_game_objects.back(), comp.value()["type"], comp.value());
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
	std::cout << type << std::endl;
	if(type == "Transform")
	{
		const auto x = jo["pos"]["x"];
		const auto y = jo["pos"]["y"];
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
		auto bound_size = Vector2<double>(jo["x"], jo["y"]);
		CreateCollider(go.GetComponents(), go);
		m_colliders.back().UpdateSize(bound_size);
	}
	else if (type == "Rigidbody")
	{
		const auto is_kinematic = jo["is_kinematic"];
		const auto use_gravity = jo["use_gravity"];
		CreateRigidbody(go.GetComponents(), go);
		m_rigidbodies.back().m_use_gravity = use_gravity;
		m_rigidbodies.back().m_is_kinematic = is_kinematic;
	}
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
	std::cout << "added collider" << std::endl;
	components.push_back(&m_colliders.back());
}
// end
