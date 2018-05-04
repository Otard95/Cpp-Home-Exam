#ifndef __PLAYERCONTROLLS_COMPONENT_H__
#define __PLAYERCONTROLLS_COMPONENT_H__

#include <memory>
#include "CDP.h"
#include "../../nlohmann_json/json.hpp"

namespace CDP {

	class PlayerControlls : public Component {

		std::shared_ptr<Transform> m_transform;
		InputManager& m_input;
		Time& m_time;

		double m_speed;
		double m_fire_rate;

		nlohmann::json m_bullet_prefab;

	public:
		PlayerControlls(std::vector<std::shared_ptr<Component>> &,
										GameObject&,
										nlohmann::json&);
		~PlayerControlls() = default;

		void SetSpeed(double speed);
		void SetFireRate(double fire_rate);

		void Start() override;
		void Update() override;

	};

}

#endif
