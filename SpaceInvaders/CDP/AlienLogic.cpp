#include "Headers\AlienLogic.h"
#include <iostream>
#include <random>
#include <ctime>
#include "Headers/GameCore.h"

using namespace CDP;

AlienLogic::AlienLogic(std::vector<std::shared_ptr<Component>>& components,
						GameObject& go,
						Transform& trans,
						int moveLength,
						double moveInterval,
						int dropLength,
						int fireRate,
						nlohmann::json bulletPrefab)
	: Component(components, go)
	, m_move_length(moveLength)
	, m_move_interval(moveInterval)
	, m_direction(1)
	, m_drop_length(dropLength)
	, m_has_dropped(false)
	, m_drop(false)
	, m_time_elapsed(0)
	, m_is_in_front(false)
	, m_fire_rate(fireRate)
	, m_bullet_prefab(bulletPrefab)
	, m_cooldown(fireRate)
	, m_transform(trans)
{}

void AlienLogic::Start()
{
	m_start_pos_x = m_transform.Position().x;
	m_start_pos_y = m_transform.Position().y;

	UpdateFrontAlien();

	std::weak_ptr<GameObject> wgo = GameCore::Instance().FindGameObject("GameManager");
	std::shared_ptr<GameObject> go;
	if ((go = wgo.lock()))
	{
		m_game_manager = go->GetComponent<GameManager>();
	}

	/* initialize seed */
	std::random_device rand;
	std::mt19937 generator(rand());
	std::uniform_real_distribution<double> distribution(m_fire_rate, m_fire_rate * 2);

	m_cooldown = distribution(generator);
}


void AlienLogic::Update()
{
	Move();
	CheckPosition();

	Fire();
}

void AlienLogic::CheckPosition()
{
	if (GameCore::Instance().GetLoopStatus() && m_transform.Position().y >= 800)
	{
		std::shared_ptr<GameManager> gm = m_game_manager.lock();
		gm->GameOver();
	}
}

void AlienLogic::Move()
{
	if (m_time_elapsed >= m_move_interval)
	{
		m_time_elapsed = 0;
		
		if (m_drop)
		{
			m_transform.SetPosition(m_transform.Position().x, m_transform.Position().y + m_drop_length);
			m_direction *= -1;
			m_has_dropped = true;
			m_drop = false;
			return;
		}
		m_transform.SetPosition(m_transform.Position().x + m_move_length * m_direction
		                      , m_transform.Position().y);

		m_has_dropped = false;
		return;
	}
	m_time_elapsed += Time::Instance().DeltaTime();
}

void AlienLogic::OnCollision(Collider& collider)
{
	std::string name = collider.GetGameObject().GetName();
	if (name == "Bullet")
	{
		collider.GetGameObject().Enable(false);
		m_game_object.Enable(false);
		std::shared_ptr<GameManager> gm = m_game_manager.lock();
		if (gm) gm->AddScore();
		UpdateFrontAlien();
	}
	else if (!m_has_dropped && (name == "LeftWall" || name == "RightWall"))
	{
		for (auto it = GameCore::Instance().m_alien_logics.begin(); it != GameCore::Instance().m_alien_logics.end(); ++it)
		{
			it->get()->Drop();	
		}
	}
}

void AlienLogic::Drop()
{
	m_drop = true;	
}

void AlienLogic::Reset()
{
	m_transform.SetPosition(m_start_pos_x, m_start_pos_y);
	m_direction = 1;
	m_time_elapsed = 0;
	m_is_in_front = false;
	m_drop = false;
	m_has_dropped = false;

	//increase speed by lowering the interval between movements
	if(m_move_interval >= 0.2)
	{
		m_move_interval -= 0.1;
	}
	//reduce time between shots
	if (m_fire_rate >= 3.0)
	{
		m_fire_rate -= 0.5;
	}

	UpdateFrontAlien();
}

void AlienLogic::UpdateFrontAlien()
{
	std::shared_ptr<AlienLogic> currentFrontAlien = nullptr;
	
	for (auto it = GameCore::Instance().m_alien_logics.begin(); it != GameCore::Instance().m_alien_logics.end(); ++it)
	{
		std::shared_ptr<AlienLogic> alien = *it;

		//find all enabled objects in same column
		if (alien->GetGameObject().enabled && alien->m_transform.Position().x == m_transform.Position().x)
		{
			alien->SetIsInFront(false);
			//check which one is closest to the player
			if (currentFrontAlien == nullptr)
			{
				currentFrontAlien = alien;
			}
			else if (alien->m_transform.Position().y > currentFrontAlien->m_transform.Position().y)
			{
				currentFrontAlien = alien;
			}
		}
	}

	if (currentFrontAlien != nullptr)
	{
		currentFrontAlien->SetIsInFront(true);
	}	
}

void AlienLogic::SetIsInFront(bool status)
{
	m_is_in_front = status;
}

void AlienLogic::Fire()
{
	if (m_is_in_front)
	{
		if (m_cooldown <= 0.0)
		{
			/* initialize seed */
			std::random_device rand;
			std::mt19937 generator(rand());
			std::uniform_real_distribution<double> distribution(m_fire_rate, m_fire_rate * 2);

			if (m_bullets.size() > 5)
			{ // reuse bullet objects
				for (auto it = m_bullets.begin(); it != m_bullets.end(); ++it) {
					std::shared_ptr<GameObject> go = it->lock();
					if (go->enabled) continue;
					go->GetComponent<Transform>()->SetPosition(m_transform.Position().x, m_transform.Position().y);
					go->GetComponent<Rigidbody>()->velocity.y = m_bullet_prefab["components"][3]["velocity"]["y"];
					go->Enable(true);
					m_cooldown = distribution(generator);
					break;
				}
			}
			else
			{ // create a new bullet
				m_bullet_prefab["components"][0]["pos"]["x"] = m_transform.Position().x;
				m_bullet_prefab["components"][0]["pos"]["y"] = m_transform.Position().y;
				m_bullets.push_back(GameCore::Instance().Instantiate(m_bullet_prefab));

				m_cooldown = distribution(generator);
			}
		}
		else
		{
			m_cooldown -= Time::Instance().DeltaTime();
		}
	}
}

