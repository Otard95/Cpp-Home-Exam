#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include <memory>
#include <string>
#include "CDP_fwd.h"
#include "RigidbodyCore.h"
#include "ColliderCore.h"
#include "Triplet.h"
#include "Vector2.h"
#include "../../nlohmann_json/json.hpp"

namespace CDP {

	class GameObject {
		static std::vector<GameObject> m_game_objects;

		std::string m_name;
		std::unique_ptr<Triplet<Vector2<double>,
										ColliderCore,
										RigidbodyCore>> m_physics_triplet;
		std::vector<std::shared_ptr <Component>> m_components;

	public:
		GameObject(nlohmann::json&);
		~GameObject();

		void Update ();
	};

}

#endif // !__GAMEOBJECT_H__


