#pragma once
#include <vector>
#include "GameObject.h"
#include "CDP.h"

namespace CDP {

	class GameCore {
	public:
		// Richard
		static GameCore& instance() {
			static GameCore gameCore;
			return gameCore;
		}

		std::vector<CDP::GameObject> m_game_objects;

		GameCore();
		~GameCore();
		// end

		// Stian

		std::shared_ptr<Transform> CreateTransform(std::vector<std::shared_ptr<Component>> &, GameObject&);

		/**
		 * ## Components
		*/
		std::vector<Rigidbody> m_rigidbodies;
		std::vector<Collider> m_colliders;
		std::vector<Transform> m_transforms;


		//end
	};

}
