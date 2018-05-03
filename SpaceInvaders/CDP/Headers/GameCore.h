#pragma once
#include <vector>
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

		/**
		 * ## Components
		*/
		std::vector<Rigidbody> m_rigidbodies;
		std::vector<Collider> m_colliders;
		std::vector<Transform> m_transforms;
		std::vector<Sprite> m_sprites;

		//end
	};

}
