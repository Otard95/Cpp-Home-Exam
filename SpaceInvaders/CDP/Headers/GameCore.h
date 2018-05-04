#pragma once
#include <vector>
#include "../../nlohmann_json/json.hpp"
#include "CDP.h"
#include "PlayerControlls.h"
#include "AlienLogic.h"
#include "KillTrigger.h"

namespace CDP {

	class GameCore {
	private:
		void AddComponent(GameObject& go, std::string type, nlohmann::json& jo);
		bool m_running;
		Canvas& m_canvas;
		InputManager& m_input;
		Physics& m_physics;
		Time& m_time;

		static GameCore m_instance;

	public:
		static GameCore& Instance();
		GameCore(const GameCore&) = delete;
		GameCore& operator= (const GameCore&) = delete;

		std::vector<std::shared_ptr<GameObject>> m_game_objects;

		GameCore();
		~GameCore();
		
		void Initialize(nlohmann::json&);
		std::weak_ptr<GameObject> Instantiate(nlohmann::json & jsonObject);


		void InstantiateAliens(nlohmann::json jsonObject);
		void Destroy(std::shared_ptr<GameObject>);
		void DestroyComponent(std::shared_ptr<Component>);

		void Run();

		void CreateTransform(std::vector<std::shared_ptr<Component>>&, GameObject&);
		void CreateSprite(std::vector<std::shared_ptr<Component>>&, GameObject& go, std::string texture);
		void CreateRigidbody(std::vector<std::shared_ptr<Component>>&, GameObject& go);
		void CreateCollider(std::vector<std::shared_ptr<Component>>&, GameObject& go);
		void CreatePlayerController(std::vector<std::shared_ptr<Component>>&, GameObject& go, nlohmann::json&);
		void CreateKillTrigger(std::vector<std::shared_ptr<Component>>&, GameObject& go);
		void CreateAlienLogic(std::vector<std::shared_ptr<Component>>& components, GameObject & go, int moveLength, double moveInterval, int dropLength);

		/**
		 * ## Components
		*/
		std::vector<std::shared_ptr<Rigidbody>> m_rigidbodies;
		std::vector<std::shared_ptr<Collider>> m_colliders;
		std::vector<std::shared_ptr<Transform>> m_transforms;
		std::vector<std::shared_ptr<Sprite>> m_sprites;
		std::vector<std::shared_ptr<PlayerControlls>> m_player_controlls;
		std::vector<std::shared_ptr<KillTrigger>> m_kill_triggers;
		std::vector<std::shared_ptr<AlienLogic>> m_alien_logics;
	};

}
