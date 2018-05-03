#ifndef __COLLIDER_COMPONENT_H__
#define __COLLIDER_COMPONENT_H__

#include "Component.h"
#include <memory>
#include "Vector2.h"

namespace CDP {

	class Collider : public Component {

	public:

		Transform& transform;

		Vector2<double> bound_size;
		double size;
		double extent;

		Collider(std::vector<Component*>&,
						 GameObject&,
						 Transform&);
		~Collider() = default;

		void Start() override;
	};

}

#endif
