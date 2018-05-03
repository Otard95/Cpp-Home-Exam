#ifndef __RIGIDBODY_COMPONENT_H__
#define __RIGIDBODY_COMPONENT_H__

#include <memory>
#include "Component.h"

namespace CDP {

	class Rigidbody : public Component {
	public:

		Collider & collider;
		Transform & transform;

		Rigidbody(std::vector<Component*> &components,
							GameObject& go,
							Collider &,
							Transform&);
		~Rigidbody() = default;

		void Start () override;

	};

}

#endif
