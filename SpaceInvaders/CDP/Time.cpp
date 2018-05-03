#include "Headers\Time.h"

using namespace CDP;

Time::Time()
	: m_last(std::chrono::high_resolution_clock::now())
{}

Time & CDP::Time::Instance() {
	static Time m_instance;
	return m_instance;
}

void Time::Update() {
	m_last = m_current;
	m_current = std::chrono::high_resolution_clock::now();
	m_delta_time = m_current - m_last;
}

double Time::DeltaTime() {
	return m_delta_time.count();
}
