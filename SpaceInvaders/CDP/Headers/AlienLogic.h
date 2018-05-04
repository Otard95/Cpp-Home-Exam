#ifndef __ALIENLOGIC_COMPONENT_H__
#define __ALIENLOGIC_COMPONENT_H__

#include "CDP.h"

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
		Transform& transform;
		void Update() override;
		void OnCollision(Collider&) override;

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


