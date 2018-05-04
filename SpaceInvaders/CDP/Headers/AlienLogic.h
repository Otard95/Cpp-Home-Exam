#ifndef __ALIENLOGIC_COMPONENT_H__
#define __ALIENLOGIC_COMPONENT_H__

#include "CDP.h"
#include "GameManager.h"

namespace CDP
{
	class AlienLogic : public Component
	{
	private:
		int m_move_length;
		double m_move_interval;
		int m_direction;
		int m_drop_steps;
		int m_drop_limit;
		int m_drop_length;
		double m_time_elapsed;

	public:
		std::weak_ptr<GameManager> m_game_manager;
		Transform& transform;
		void Start() override;
		void Update() override;
		void OnCollision(Collider&) override;

		void CheckPosition();
		void Move();

		AlienLogic(std::vector<std::shared_ptr<Component>> &,
									GameObject&,
									Transform&,
									int,
									double,
									int);
		~AlienLogic() = default;
	};
}
#endif


