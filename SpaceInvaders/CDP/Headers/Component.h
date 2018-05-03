#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <vector>
#include <memory>
#include <algorithm>
#include "CDP_fwd.h"

namespace CDP {

	class Component {

	private:
		std::vector<Component*> &m_sibling_components;

	protected:
		GameObject & m_game_object;

	public:
		Component(std::vector<Component*> &components, GameObject&);
		virtual ~Component() = default;

		template <class T>
		T* GetComponent() {

			T* out = nullptr;

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

	};

}

#endif // !__COMPONENT_H__


