#ifndef __COLLIDER_COMPONENT_H__
#define __COLLIDER_COMPONENT_H__

#include "Component.h"
#include <memory>

namespace CDP {

	class Collider : public Component {

	public:

		Transform& transform;

		Collider(std::vector<Component*>&,
						 GameObject&,
						 Transform&);
		~Collider() = default;

		void Start() override;
	};

}

#endif
