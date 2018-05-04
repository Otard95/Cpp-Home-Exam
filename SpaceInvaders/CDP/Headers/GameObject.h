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
		~GameObject() = default;

		bool enabled;

		template <class T>
		std::shared_ptr<T> GetComponent() {

			std::shared_ptr<T> out = nullptr;

			std::for_each(m_components.begin(),
										m_components.end(),
										[&out](std::shared_ptr<Component> c) {
				if (out) return;
				out = std::dynamic_pointer_cast<T>(c);
			});

			return out;

		}

		void Enable(bool);
		std::string GetName() const;

		std::vector<std::shared_ptr<Component>>& GetComponents();

		void Start();

	};

}

#endif // !__GAMEOBJECT_H__


