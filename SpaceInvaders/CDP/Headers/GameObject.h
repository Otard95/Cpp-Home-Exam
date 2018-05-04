#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include <memory>
#include <string>
#include "CDP_fwd.h"
#include "Triplet.h"
#include "Vector2.h"
#include "../../nlohmann_json/json.hpp"

namespace CDP {

	class GameObject {
		static std::vector<GameObject> m_game_objects;

		std::string m_name;
		std::vector<std::shared_ptr<Component>> m_components;

	public:
		GameObject(const std::string str);
		~GameObject();


		std::string GetName() const;

		std::vector<std::shared_ptr<Component>>& GetComponents();

		void Update ();
		
	};

}

#endif // !__GAMEOBJECT_H__


