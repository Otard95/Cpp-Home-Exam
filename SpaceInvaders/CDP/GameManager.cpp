#include "Headers/GameManager.h"
#include "Headers/GameCore.h"
#include <iostream>

using namespace CDP;

GameManager::GameManager(std::vector<std::shared_ptr<Component>>& components, GameObject& go)
	: Component(components, go)
	  , m_score_counter(0)
{
}

void GameManager::AddScore()
{
	m_score_counter++;
	std::cout << "Score: " << m_score_counter << std::endl;

	if (GetScore() == 55)
	{
		std::cout << "#############################################\n";
		std::cout << "##                                         ##\n";
		std::cout << "##                 You won!                ##\n";
		std::cout << "##                                         ##\n";
		std::cout << "#############################################" << std::endl;

		GameCore::Instance().Stop();
	}
}

int GameManager::GetScore()
{
	return m_score_counter;
}
