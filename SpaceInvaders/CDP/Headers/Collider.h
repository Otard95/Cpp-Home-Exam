#ifndef __COLLIDER_COMPONENT_H__
#define __COLLIDER_COMPONENT_H__

#include "ColliderCore.h"
#include "Component.h"
#include <memory>

namespace CDP {

	class Collider : public Component {

	public:

		ColliderCore & m_core;

		Collider(std::vector<std::shared_ptr<Component>> &components, GameObject&, ColliderCore &core);
		~Collider() = default;

		void Start() override;
	};

}

#endif
