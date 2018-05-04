#include "Headers/GameManager.h"
#include "Headers/GameCore.h"
#include <iostream>

using namespace CDP;

GameManager::GameManager(std::vector<std::shared_ptr<Component>>& components, GameObject& go)
	: Component(components, go)
	, m_total_score(0)
	, m_round_score(0)  
{
}

void GameManager::AddScore()
{
	m_total_score++;
	m_round_score++;
	std::cout << "Score: " << m_total_score << std::endl;

	if (m_round_score == GameCore::Instance().m_alien_logics.size())
	{
		std::cout << "#############################################\n";
		std::cout << "##                                         ##\n";
		std::cout << "##              Stage cleared!             ##\n";
		std::cout << "##                                         ##\n";
		std::cout << "#############################################" << std::endl;

		NextLevel();
	}
}

void GameManager::NextLevel()
{
	m_round_score = 0;

	for(auto it = GameCore::Instance().m_alien_logics.begin(); it != GameCore::Instance().m_alien_logics.end(); ++it)
	{
		auto al = it->get();
		al->Reset();

		auto go = it->get()->GetGameObject();
		go.Enable(true);
	}
}
