#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <vector>
#include <memory>
#include <algorithm>
#include "CDP_fwd.h"

namespace CDP {

	class Component {

	protected:
		std::vector<Component*> &m_sibling_components;
		GameObject & m_game_object;

	public:
		Component(std::vector<Component*> &components, GameObject&);
		virtual ~Component() = default;

		template <class T>
		T* GetComponent() {

			T* out = nullptr;

			std::cout << m_sibling_components.size() << std::endl;

			std::for_each(m_sibling_components.begin(),
										m_sibling_components.end(),
										[&out](Component* c) {
				if (out) return;
				out = dynamic_cast<T*>(c);
			});

			return out;

		}


		GameObject& GetGameObject();

		virtual void Start() {}
		virtual void Update() {}

		virtual void OnCollision(Collider&) {}

	};

}

#endif // !__COMPONENT_H__


