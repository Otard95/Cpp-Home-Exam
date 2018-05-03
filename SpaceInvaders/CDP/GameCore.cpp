#include "Headers/GameCore.h"
#include <iostream>
#include <algorithm>

using namespace CDP;

// Richard

GameCore::GameCore()
	: m_running(false)
	, m_canvas(Canvas::Instance())
	, m_input(InputManager::Instance())
	, m_physics(Physics::Instance())
	, m_time(Time::Instance())
{
	//m_canvas.SetTitle(std::string("Space Invaders Pro"));
	m_physics.Init(&m_rigidbodies, &m_colliders);
}


GameCore::~GameCore()
{
	m_transforms.clear();
	m_colliders.clear();
	m_rigidbodies.clear();
	m_sprites.clear();
	m_game_objects.clear();
	
}

void GameCore::Initialize(nlohmann::json& jsonObject)
{
	if (jsonObject.find("scene") != jsonObject.end())
	{
		for (nlohmann::json::iterator it = jsonObject["scene"].begin(); it != jsonObject["scene"].end(); ++it)
		{
			Instantiate(it.value());
		}
	}

	std::for_each(m_rigidbodies.begin(), m_rigidbodies.end(), [](Rigidbody& c) {
		c.Start();
	});

	std::for_each(m_colliders.begin(), m_colliders.end(), [](Collider& c) {
		c.Start();
	});

	std::for_each(m_transforms.begin(), m_transforms.end(), [](Transform& c) {
		c.Start();
	});

	std::for_each(m_sprites.begin(), m_sprites.end(), [](Sprite& c) {
		c.Start();
	});

	m_running = true;
}

void GameCore::Instantiate(nlohmann::json& jsonObject)
{
	m_game_objects.emplace_back(jsonObject["name"].get<std::string>());

	if (jsonObject.find("components") != jsonObject.end())
	{
		for (nlohmann::json::iterator comp = jsonObject["components"].begin(); comp != jsonObject["components"].end(); ++comp)
		{
			AddComponent(m_game_objects.back(), comp.value()["type"], comp.value());
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

void GameCore::Run()
{
	while(m_running)
	{		
		m_input.Update();
		m_time.Update();
		m_physics.Update();

		std::for_each(m_rigidbodies.begin(), m_rigidbodies.end(), [] (Rigidbody& c) {
			c.Update();
		});

		std::for_each(m_colliders.begin(), m_colliders.end(), [] (Collider& c) {
			c.Update();
		});

		std::for_each(m_transforms.begin(), m_transforms.end(), [] (Transform& c) {
			c.Update();
		});

		std::for_each(m_sprites.begin(), m_sprites.end(), [] (Sprite& c) {
			c.Update();
		});

		m_canvas.RenderFrame();

		if (m_input.GetKey(Keys::Esc)) m_running = false;

		if (m_input.GetKey(Keys::D))
		{
			auto transform = m_game_objects.at(0).GetComponents()[0]->GetComponent<Transform>();
			transform->SetPosition(transform->Position().x + 1, transform->Position().y);
		}
		else if (m_input.GetKey(Keys::A))
		{
			auto transform = m_game_objects.at(0).GetComponents()[0]->GetComponent<Transform>();
			transform->SetPosition(transform->Position().x - 1, transform->Position().y);
		}

	}
}