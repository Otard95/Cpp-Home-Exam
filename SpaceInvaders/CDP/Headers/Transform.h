#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include "Vector2.h"
#include "Component.h"

namespace CDP {

	class Transform : public Component {

	private:
		Vector2<double> m_position;

	public:
		Transform(std::vector<std::shared_ptr<Component>> &components, GameObject&);
		~Transform();

		Vector2<double> const& Position();
		void Translate(const Vector2<double>&);
		void Translate(double x, double y);
		void SetPosition(const Vector2<double>&);
		void SetPosition(double x, double y);

	};

}

#endif