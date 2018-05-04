#include "Headers\AlienLogic.h"
#include <iostream>

using namespace CDP;

AlienLogic::AlienLogic(std::vector<std::shared_ptr<Component>>& components,
						GameObject& go,
						Transform& trans,
						int moveLength,
						double moveInterval)
	: Component(components, go)
	, m_move_length(moveLength)
	, m_move_interval(moveInterval)
	, m_direction(1)
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
		transform.SetPosition(transform.Position().x + m_move_length * m_direction
			, transform.Position().y);

		m_time_elapsed = 0;
		return;
	}
	m_time_elapsed += Time::Instance().DeltaTime();
}

void AlienLogic::OnCollision(Collider& collider)
{
	//if (collider.GetGameObject().GetName() == ""
}
