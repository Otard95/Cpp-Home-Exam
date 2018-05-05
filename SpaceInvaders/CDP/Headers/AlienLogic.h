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

		int m_drop_length;
		bool m_has_dropped;
		bool m_drop;

		double m_time_elapsed;
		int m_start_pos_x;
		int m_start_pos_y;

		bool m_is_in_front;
		int m_fire_rate;
		double m_cooldown;
		nlohmann::json m_bullet_prefab;
		std::vector<std::weak_ptr<GameObject>> m_bullets;

	public:
		std::weak_ptr<GameManager> m_game_manager;
		Transform& m_transform;
		void Start() override;
		void Update() override;
		void OnCollision(Collider&) override;

		void CheckPosition();
		void Move();
		void Reset();
		void UpdateFrontAlien();
		void SetIsInFront(bool);

		void Drop();
		void Fire();

		AlienLogic(std::vector<std::shared_ptr<Component>> &,
									GameObject&,
									Transform&,
									int,
									double,
									int,
									int,
									nlohmann::json);
		~AlienLogic() = default;
	};
}
#endif


