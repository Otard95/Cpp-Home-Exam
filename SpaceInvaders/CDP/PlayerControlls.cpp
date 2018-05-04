#include "Headers/PlayerControlls.h"
#include <iostream>

using namespace CDP;

PlayerControlls::PlayerControlls(std::vector<std::shared_ptr<Component>>& cmp,
																 GameObject& go)
	: Component(cmp, go)
	, m_transform(nullptr)
	, m_input(InputManager::Instance())
	, m_time(Time::Instance())
	, m_speed(200)
	, m_fire_rate(1)
{}

void CDP::PlayerControlls::SetSpeed(double speed) {
	m_speed = speed;
}

void CDP::PlayerControlls::SetFireRate(double fire_rate) {
	m_fire_rate = fire_rate;
}

void PlayerControlls::Start() {
	m_transform = GetComponent<Transform>();
}

void PlayerControlls::Update() {
	if (m_input.GetKey(Keys::A) && !m_input.GetKey(Keys::D))
		m_transform->Translate(-m_speed * m_time.DeltaTime(), 0);
	else if (m_input.GetKey(Keys::D) && !m_input.GetKey(Keys::A))
		m_transform->Translate(m_speed * m_time.DeltaTime(), 0);
}

