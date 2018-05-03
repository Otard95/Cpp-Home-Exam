#ifndef __RIGIDBODY_COMPONENT_H__
#define __RIGIDBODY_COMPONENT_H__

#include <memory>
#include "Component.h"
#include "Vector2.h"

namespace CDP {

	class Rigidbody : public Component {
	public:

		Collider & collider;
		Transform & transform;

		bool m_is_kinematic;
		bool m_use_gravity;

		Vector2<double> velocity;
		Rigidbody(std::vector<Component*> &components,
							GameObject& go,
							Collider &,
							Transform&);
		~Rigidbody() = default;

		void Start () override;

	};

}

#endif
