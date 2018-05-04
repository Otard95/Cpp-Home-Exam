#include "Headers\AlienLogic.h"
#include <iostream>
#include "Headers/GameCore.h"

using namespace CDP;

AlienLogic::AlienLogic(std::vector<std::shared_ptr<Component>>& components,
                       GameObject& go,
                       Transform& trans,
                       int moveLength,
                       double moveInterval,
                       int dropLength)
	: Component(components, go)
	  , m_move_length(moveLength)
	  , m_move_interval(moveInterval)
	  , m_direction(1)
	  , m_drop_steps(0)
	  , m_drop_limit(14)
	  , m_drop_length(dropLength)
	  , m_time_elapsed(0)
	  , transform(trans)
{
	m_start_pos_x = transform.Position().x;
	m_start_pos_y = transform.Position().y;
}

void AlienLogic::Start()
{
	std::weak_ptr<GameObject> wgo = GameCore::Instance().FindGameObject("GameManager");
	std::shared_ptr<GameObject> go;
	if ((go = wgo.lock()))
	{
		m_game_manager = go->GetComponent<GameManager>();
	}
}


void AlienLogic::Update()
{
	Move();
	CheckPosition();
}

void AlienLogic::CheckPosition()
{
	if (transform.Position().y >= 800)
	{
		std::cout << "#############################################\n";
		std::cout << "##                                         ##\n";
		std::cout << "##               GAME OVER!                ##\n";
		std::cout << "##                                         ##\n";
		std::cout << "#############################################" << std::endl;

		GameCore::Instance().Stop();
	}
}

void AlienLogic::Move()
{
	//	std::cout << m_move_interval << std::endl;
	if (m_time_elapsed >= m_move_interval)
	{
		m_time_elapsed = 0;

		if (m_drop_steps == m_drop_limit)
		{
			transform.SetPosition(transform.Position().x, transform.Position().y + m_drop_length);
			m_direction *= -1;
			m_drop_steps = 0;
			return;
		}
		transform.SetPosition(transform.Position().x + m_move_length * m_direction
		                      , transform.Position().y);

		m_drop_steps++;
		return;
	}
	m_time_elapsed += Time::Instance().DeltaTime();
}

void AlienLogic::OnCollision(Collider& collider)
{
	collider.GetGameObject().Enable(false);
	m_game_object.Enable(false);
	std::shared_ptr<GameManager> gm = m_game_manager.lock();
	if (gm) gm->AddScore();
}

void AlienLogic::Reset()
{
	transform.SetPosition(m_start_pos_x, m_start_pos_y);
	m_direction = 1;
	m_drop_steps = 0;
	m_time_elapsed = 0;

	if(m_move_interval >= 0.2)
	{
		m_move_interval -= 0.1;
	}

	std::cout << m_move_interval << std::endl;
}

