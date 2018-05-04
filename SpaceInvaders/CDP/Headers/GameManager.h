#ifndef __GAMEMANAGER_COMPONENT_H__
#define __GAMEMANAGER_COMPONENT_H__

#include "CDP.h"

namespace CDP
{
	class GameManager : public Component
	{
	private: 
		int m_total_score;
		int m_round_score;

	public:
		GameManager(std::vector<std::shared_ptr<Component>> &, GameObject&);
		~GameManager() = default;

		void AddScore();
	};
}

#endif