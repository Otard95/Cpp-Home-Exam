#include "Headers\AlienLogic.h"
#include <iostream>

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
}

void AlienLogic::Update()
{
	Move();
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
}
