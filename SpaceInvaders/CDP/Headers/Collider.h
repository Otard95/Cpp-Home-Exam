#ifndef __COLLIDER_COMPONENT_H__
#define __COLLIDER_COMPONENT_H__

#include "Component.h"
#include "Vector2.h"

namespace CDP {

	class Collider : public Component {

	public:

		Transform& transform;

		Vector2<double> bound_size;
		double size;
		double extent;

		bool is_trigger;

		Collider(std::vector<Component*>&,
						 GameObject&,
						 Transform&);
		~Collider() = default;

		void Start() override;

		void OnCollision(Collider&);

	};

}

#endif
