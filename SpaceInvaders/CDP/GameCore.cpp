#include "Headers/GameCore.h"
#include <iostream>
#include <algorithm>
#include "Headers/AlienLogic.h"

using namespace CDP;

GameCore & CDP::GameCore::Instance() {
	{
		static GameCore m_instance;
		return m_instance;
	}
}

GameCore::GameCore()
	: m_running(false)
	  , m_canvas(Canvas::Instance())
	  , m_input(InputManager::Instance())
	  , m_physics(Physics::Instance())
	  , m_time(Time::Instance())
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

void GameCore::Initialize(nlohmann::json& jsonObject)
{
	if (jsonObject.find("scene") != jsonObject.end())
	{
		for (nlohmann::json::iterator it = jsonObject["scene"].begin(); it != jsonObject["scene"].end(); ++it)
		{
			if (it.value()["name"] == "Invader")
			{
				InstantiateAliens(it.value());
			}
			else
			{
				Instantiate(it.value());
			}
		}
	}

	std::for_each(m_rigidbodies.begin(), m_rigidbodies.end(), [](std::shared_ptr<Rigidbody> c)
	{
		c->Start();
	});

	std::for_each(m_colliders.begin(), m_colliders.end(), [](std::shared_ptr<Collider> c)
	{
		c->Start();
	});

	std::for_each(m_transforms.begin(), m_transforms.end(), [](std::shared_ptr<Transform> c)
	{
		c->Start();
	});

	std::for_each(m_sprites.begin(), m_sprites.end(), [](std::shared_ptr<Sprite> c)
	{
		c->Start();
	});

	std::for_each(m_player_controlls.begin(), m_player_controlls.end(), [](std::shared_ptr<PlayerControlls> c)
	{
		c->Start();
	});

	std::for_each(m_alien_logics.begin(), m_alien_logics.end(), [](std::shared_ptr<AlienLogic> c)
	{
		c->Start();
	});

	m_running = true;
}

std::weak_ptr<GameObject> GameCore::Instantiate(nlohmann::json& jsonObject)
{
	m_game_objects.emplace_back(std::make_shared<GameObject>(jsonObject["name"].get<std::string>()));

	if (jsonObject.find("components") != jsonObject.end())
	{
		for (nlohmann::json::iterator comp = jsonObject["components"].begin(); comp != jsonObject["components"].end(); ++comp)
		{
			AddComponent(*m_game_objects.back(), comp.value()["type"], comp.value());
		}
	}

	if (m_running)
		m_game_objects.back()->Start();

	return m_game_objects.back();

}

std::weak_ptr<GameObject> GameCore::FindGameObject(const std::string& name)
{
	std::shared_ptr<GameObject> out;
	std::for_each(m_game_objects.begin(), m_game_objects.end(), [&name, &out](std::shared_ptr<GameObject> go){
		if (out) return;
		if (go->GetName() == name)
			out = go;
	});
	return out;
}

void GameCore::InstantiateAliens(nlohmann::json jsonObject)
{
	int width = jsonObject["width"];
	int height = jsonObject["height"];

	int offsetX = width / (jsonObject["col"].get<int>() + 2);
	int offsetY = height / jsonObject["row"].get<int>();


	for (int i = 0; i < jsonObject["row"]; i++)
	{
		for (int j = 0; j < jsonObject["col"]; j++)
		{
			jsonObject["components"][0]["pos"]["x"] = j * offsetX + offsetX / 2;
			jsonObject["components"][0]["pos"]["y"] = i * offsetY + offsetY * 2;
			
			Instantiate(jsonObject);
		}
	}
}

void GameCore::Destroy(std::shared_ptr<GameObject> go)
{
	for (auto it = m_game_objects.begin(); it != m_game_objects.end(); ++it)
	{
		if (*it == go)
		{
			for (auto itcmp = (*it)->GetComponents().begin(); itcmp != (*it)->GetComponents().end(); ++itcmp)
			{
				DestroyComponent(*itcmp);
			}
			m_game_objects.erase(it);
			return;
		}
	}
}

void GameCore::DestroyComponent(std::shared_ptr<Component> cmp)
{
	for (auto it = m_rigidbodies.begin(); it != m_rigidbodies.end(); ++it) {
		if (*it == cmp)
		{
			m_rigidbodies.erase(it);
			return;
		}
	}
	for (auto it = m_colliders.begin(); it != m_colliders.end(); ++it) {
		if (*it == cmp) {
			m_colliders.erase(it);
			return;
		}
	}
	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it) {
		if (*it == cmp) {
			m_sprites.erase(it);
			return;
		}
	}
	for (auto it = m_transforms.begin(); it != m_transforms.end(); ++it) {
		if (*it == cmp) {
			m_transforms.erase(it);
			return;
		}
	}
	for (auto it = m_player_controlls.begin(); it != m_player_controlls.end(); ++it) {
		if (*it == cmp) {
			m_player_controlls.erase(it);
			return;
		}
	}
	for (auto it = m_alien_logics.begin(); it != m_alien_logics.end(); ++it) {
		if (*it == cmp) {
			m_alien_logics.erase(it);
			return;
		}
	}
}

void GameCore::AddComponent(GameObject& go, std::string type, nlohmann::json& jo)
{
	if (type == "Transform")
	{
		const auto x = jo["pos"]["x"];
		const auto y = jo["pos"]["y"];
		CreateTransform(go.GetComponents(), go);
		m_transforms.back()->SetPosition(x, y);
	}
	else if (type == "Sprite")
	{
		const auto texture = jo["texture"];
		CreateSprite(go.GetComponents(), go, texture);
	}
	else if (type == "Collider")
	{
		auto bound_size = Vector2<double>(jo["x"], jo["y"]);
		CreateCollider(go.GetComponents(), go);
		m_colliders.back()->UpdateSize(bound_size);
		if (jo.find("trigger") != jo.end())
			m_colliders.back()->is_trigger = jo["trigger"];

		m_physics.Init(m_rigidbodies, m_colliders);
	}
	else if (type == "Rigidbody")
	{
		const auto is_kinematic = jo["is_kinematic"];
		const auto use_gravity = jo["use_gravity"];
		CreateRigidbody(go.GetComponents(), go);
		m_rigidbodies.back()->m_use_gravity = use_gravity;
		m_rigidbodies.back()->m_is_kinematic = is_kinematic;
		if (jo.find("velocity") != jo.end())
			m_rigidbodies.back()->velocity = Vector2<double>(jo["velocity"]["x"], jo["velocity"]["y"]);

		m_physics.Init(m_rigidbodies, m_colliders);
	}
	else if (type == "PlayerController")
	{
		CreatePlayerController(go.GetComponents(), go, jo["bullet_prefab"]);
		if (jo.find("speed") != jo.end())
			m_player_controlls.back()->SetSpeed(jo["speed"]);
		if (jo.find("fire_rate") != jo.end())
			m_player_controlls.back()->SetFireRate(jo["fire_rate"]);
	}
	else if (type == "KillTrigger") {
		CreateKillTrigger(go.GetComponents(), go);
	}
	else if (type == "AlienLogic")
	{
		CreateAlienLogic(go.GetComponents(), go, jo["move_length"], jo["move_interval"], jo["drop_length"]
												, jo["fire_rate"], jo["bullet_prefab"]);
	}
	else if (type == "GameManager")
	{
		CreateGameManager(go.GetComponents(), go);
	}
}

// end

// Stian

void GameCore::CreateTransform(std::vector<std::shared_ptr<Component>>& components, GameObject& go)
{
	m_transforms.emplace_back(std::make_shared<Transform>(components, go));
	components.push_back(m_transforms.back());
}

void GameCore::CreateSprite(std::vector<std::shared_ptr<Component>>& components, GameObject& go, std::string texture)
{
	m_sprites.emplace_back(std::make_shared<Sprite>(components, go, texture));
	components.push_back(m_sprites.back());
}

void GameCore::CreateRigidbody(std::vector<std::shared_ptr<Component>>& components, GameObject& go)
{
	m_rigidbodies.emplace_back(std::make_shared<Rigidbody>(components, go, *m_colliders.back(), *m_transforms.back()));
	components.push_back(m_rigidbodies.back());
}

void GameCore::CreateCollider(std::vector<std::shared_ptr<Component>>& components, GameObject& go)
{
	m_colliders.emplace_back(std::make_shared<Collider>(components, go, *m_transforms.back()));
	components.push_back(m_colliders.back());
}

void CDP::GameCore::CreatePlayerController(std::vector<std::shared_ptr<Component>>& components, GameObject& go, nlohmann::json& bullet_prefab)
{
	m_player_controlls.emplace_back(std::make_shared<PlayerControlls>(components, go, bullet_prefab));
	components.push_back(m_player_controlls.back());
}

void CDP::GameCore::CreateKillTrigger(std::vector<std::shared_ptr<Component>>& cmp, GameObject & go)
{
	m_kill_triggers.emplace_back(std::make_shared<KillTrigger>(cmp, go));
	cmp.push_back(m_kill_triggers.back());
}

void CDP::GameCore::CreateAlienLogic(std::vector<std::shared_ptr<Component>>& components, GameObject& go
										, int moveLength, double moveInterval, int dropLength
										, int fireRate, nlohmann::json bulletPrefab)
{
	m_alien_logics.emplace_back(std::make_shared<AlienLogic>(components, go, *m_transforms.back()
										, moveLength, moveInterval, dropLength
										, fireRate, bulletPrefab));
	components.push_back(m_alien_logics.back());
}

void GameCore::CreateGameManager(std::vector<std::shared_ptr<Component>>& components, GameObject& go)
{
	m_game_managers.emplace_back(std::make_shared<GameManager>(components, go));
	components.push_back(m_game_managers.back());
}

void GameCore::Run()
{

	m_time.Update();
	m_time.Update();

	while(m_running)
	{
		m_input.Update();
		m_time.Update();
		m_physics.Update();

		std::for_each(m_rigidbodies.begin(), m_rigidbodies.end(), [](std::shared_ptr<Rigidbody> c)
		{
			if (!c->enabled) return;
			c->Update();
		});

		std::for_each(m_colliders.begin(), m_colliders.end(), [](std::shared_ptr<Collider> c)
		{
			if (!c->enabled) return;
			c->Update();
		});

		std::for_each(m_transforms.begin(), m_transforms.end(), [](std::shared_ptr<Transform> c)
		{
			if (!c->enabled) return;
			c->Update();
		});

		std::for_each(m_sprites.begin(), m_sprites.end(), [](std::shared_ptr<Sprite> c)
		{
			if (!c->enabled) return;
			c->Update();
		});

		std::for_each(m_player_controlls.begin(), m_player_controlls.end(), [](std::shared_ptr<PlayerControlls> c)
		{
			if (!c->enabled) return;
			c->Update();
		});

		std::for_each(m_alien_logics.begin(), m_alien_logics.end(), [](std::shared_ptr<AlienLogic> c)
		{
			if (!c->enabled) return;
			c->Update();
		});

		m_canvas.RenderFrame();

		if (m_input.GetKey(Keys::Esc)) m_running = false;
	}
}

bool GameCore::GetLoopStatus()
{
	return m_running;
}

void CDP::GameCore::Stop()
{
	m_running = false;
}
