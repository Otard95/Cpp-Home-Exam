#include "Headers/GameManager.h"
#include <iostream>

using namespace CDP;

GameManager::GameManager(std::vector<std::shared_ptr<Component>> &components, GameObject& go)
	: Component(components, go)
	, m_score_counter(0)
{}

void GameManager::AddScore()
{
	m_score_counter++;
	std::cout << "Score: " << m_score_counter << std::endl;
}

