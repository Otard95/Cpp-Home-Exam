#pragma once
#include <vector>
#include "GameObject.h"
#include "../../nlohmann_json/json.hpp"

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

		void static Instantiate(nlohmann::json&);
		void static Destroy(GameObject*);
		// end

		// Stian

		//end
	};

}
