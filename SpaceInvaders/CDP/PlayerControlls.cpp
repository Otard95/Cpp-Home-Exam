#include "Headers/PlayerControlls.h"
#include "Headers/GameCore.h"
#include <iostream>

using namespace CDP;

PlayerControlls::PlayerControlls(std::vector<std::shared_ptr<Component>>& cmp,
																 GameObject& go,
																 nlohmann::json& bullet_prefab)
	: Component(cmp, go)
	, m_transform(nullptr)
	, m_input(InputManager::Instance())
	, m_time(Time::Instance())
	, m_speed(200)
	, m_fire_rate(1)
	, m_cooldown(0)
	, m_bullet_prefab(bullet_prefab)
{}

void PlayerControlls::SetSpeed(double speed) {
	m_speed = speed;
}

void PlayerControlls::SetFireRate(double fire_rate) {

	m_fire_rate = fire_rate;
}

void PlayerControlls::Start() {
	// get the transform component
	m_transform = GetComponent<Transform>();

	std::weak_ptr<GameObject> wgo = GameCore::Instance().FindGameObject("GameManager");
	std::shared_ptr<GameObject> go;
	if ((go = wgo.lock()))
	{
		m_game_manager = go->GetComponent<GameManager>();
	}
}

void PlayerControlls::Update() {
	
	// Movement
	if (m_input.GetKey(Keys::A) && !m_input.GetKey(Keys::D))
		m_transform->Translate(-m_speed * m_time.DeltaTime(), 0);
	else if (m_input.GetKey(Keys::D) && !m_input.GetKey(Keys::A))
		m_transform->Translate(m_speed * m_time.DeltaTime(), 0);

	// Shooting
	if (m_input.GetKeyDown(Keys::Space) && m_cooldown <= 0) {
		if (m_bullets.size() > 5)
		{ // reuse bullet objects
			for (auto it = m_bullets.begin(); it != m_bullets.end(); ++it){
				std::shared_ptr<GameObject> go = it->lock();
				if (go->enabled) continue;
				go->GetComponent<Transform>()->SetPosition(m_transform->Position().x, m_transform->Position().y - 45);
				go->GetComponent<Rigidbody>()->velocity.y = m_bullet_prefab["components"][3]["velocity"]["y"];
				go->Enable(true);
				m_cooldown = m_fire_rate;
				break;
			}
		}
		else
		{ // create a new bullet
			m_bullet_prefab["components"][0]["pos"]["x"] = m_transform->Position().x;
			m_bullet_prefab["components"][0]["pos"]["y"] = m_transform->Position().y - 45;
			m_bullets.push_back(GameCore::Instance().Instantiate(m_bullet_prefab));
			m_cooldown = m_fire_rate;
		}
	} else { // gun is on cooldown
		m_cooldown -= m_time.DeltaTime();
	}

}
void PlayerControlls::OnCollision(Collider& collider)
{
	if (collider.GetGameObject().GetName() == "AlienBullet")
	{
		std::shared_ptr<GameManager> gm = m_game_manager.lock();
		gm->GameOver();
	}
}

