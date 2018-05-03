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
		CreateTransform(go.GetComponents(), go);
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

	/*std::shared_ptr<Transform> trans = std::make_shared<Transform>(components, go);

	std::cout << trans << std::endl;

	m_transforms.emplace_back(std::move(*trans));
	components.emplace_back(std::move(trans));

	std::cout << &m_transforms.back() << std::endl;
	std::cout << components.back() << std::endl;*/

	/*
	m_transforms.emplace_back(Transform(components, go));
	std::shared_ptr<Transform> ptr = std::shared_ptr<Transform>(&m_transforms.back());
	components.emplace_back(ptr);

	/*
	m_transforms.emplace_back(Transform(components, go));
	components.emplace_back(std::shared_ptr<Transform>(&m_transforms.back()));*/
}

std::shared_ptr<Transform> GameCore::CreateRigidbody(std::vector<std::shared_ptr<Component>> &components, GameObject& go)
{/*
	m_rigidbodies.emplace_back(Rigidbody(components, go));
	return std::make_shared<Rigidbody>(m_rigidbodies.back());*/
	return nullptr;
}

std::shared_ptr<Transform> GameCore::CreateCollider(std::vector<std::shared_ptr<Component>> &components, GameObject& go, Transform& tranform)
{/*
	m_colliders.emplace_back(Collider(components, go, transform));
	return std::make_shared<Collider>(m_colliders.back());*/
	return nullptr;
}
// end
