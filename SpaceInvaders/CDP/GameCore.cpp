#include "Headers/GameCore.h"
#include <iostream>


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
			/*
			for (nlohmann::json::iterator it = jsonObject["components"].begin(); it != jsonObject["components"].end(); ++it)
			{
				const std::string str = it.key();

				if (it.key() == "PlayerControls")
				{
					//TO DO: add player component.
				}
				else if (it.key() == "Transform")
				{
					Transform t = Transform(m_components, *this);
				}
			}
			*/
		}
	}
}

void GameCore::Destroy(GameObject* go)
{
	//search and destroy
}

// end

// Stian

std::shared_ptr<Transform> GameCore::CreateTransform(std::vector<std::shared_ptr<Component>> &components, GameObject& go )
{
	m_transforms.emplace_back(Transform(components, go));
	return std::make_shared<Transform>(m_transforms.back());
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
