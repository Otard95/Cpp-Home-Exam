#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <vector>
#include <memory>
#include <algorithm>
#include "CDP_fwd.h"

namespace CDP {

	class Component {

	private:
		std::vector<std::shared_ptr<Component>> &m_sibling_components;

	protected:
		GameObject & m_game_object;

	public:
		Component(std::vector<std::shared_ptr<Component>> &components, GameObject&);
		virtual ~Component() = default;

		template <class T>
		std::shared_ptr<T> GetComponent() {

			std::shared_ptr<T> out = nullptr;

			std::for_each(m_sibling_components.begin(),
										m_sibling_components.end(),
										[&out](std::shared_ptr<Component> c) {
				if (out) return;
				out = std::dynamic_pointer_cast<T>(c);
			});

			return out;

		}

		virtual void Start() {}
		virtual void Update() {}

	};

}

#endif // !__COMPONENT_H__


