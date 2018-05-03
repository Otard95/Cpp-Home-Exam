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

		Vector2<double> velocity;

		Rigidbody(std::vector<std::shared_ptr<Component>> &components,
							GameObject& go,
							Collider &,
							Transform&);
		~Rigidbody() = default;

		void Start () override;

	};

}

#endif
