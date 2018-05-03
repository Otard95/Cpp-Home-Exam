#pragma once
#include <vector>
#include "../../nlohmann_json/json.hpp"
#include "CDP.h"

namespace CDP {

	class GameCore {
	private:
		void AddComponent(GameObject& go, std::string type, nlohmann::json& jo);

	public:
		// Richard
		static GameCore& instance() {
			static GameCore gameCore;
			return gameCore;
		}

		std::vector<CDP::GameObject> m_game_objects;

		GameCore();
		~GameCore();

		void Instantiate(nlohmann::json&);
		void Destroy(GameObject*);

		
		// end

		// Stian

		void CreateTransform(std::vector<std::shared_ptr<Component>>&, GameObject&);
		std::shared_ptr<Transform> CreateRigidbody(std::vector<std::shared_ptr<Component>>& components, GameObject& go);
		std::shared_ptr<Transform> CreateCollider(std::vector<std::shared_ptr<Component>>& components, GameObject& go, Transform& transform);

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
