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

std::shared_ptr<Transform> GameCore::CreateTransform(std::vector<std::shared_ptr<Component>> &components, GameObject& go )
{
	m_transforms.emplace_back(Transform(components, go));
	return std::make_shared<Transform>(m_transforms.back());
}

std::shared_ptr<Transform> GameCore::CreateRigidbody(std::vector<std::shared_ptr<Component>> &components, GameObject& go)
{
	m_rigidbodies.emplace_back(Rigidbody(components, go));
	return std::make_shared<Rigidbody>(m_rigidbodies.back());
}

std::shared_ptr<Transform> GameCore::CreateCollider(std::vector<std::shared_ptr<Component>> &components, GameObject& go, Transform& tranform)
{
	go
	m_colliders.emplace_back(Collider(components, go, transform));
	return std::make_shared<Collider>(m_colliders.back());
}


// end
