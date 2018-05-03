#ifndef __COLLIDER_COMPONENT_H__
#define __COLLIDER_COMPONENT_H__

#include "Component.h"
#include "Vector2.h"

namespace CDP {

	class Collider : public Component {

		Vector2<double> m_bound_size;
		double m_size;
		double m_extent;

	public:

		Transform& transform;

		bool is_trigger;

		Collider(std::vector<Component*>&,
						 GameObject&,
						 Transform&);
		~Collider() = default;

		void Start() override;

		void UpdateSize(Vector2<double>&);
		void UpdateSize(double x, double y);

		Vector2<double> BoundsSize();
		double Size();
		double Extent();

		void OnCollision(Collider&);

	};

}

#endif
