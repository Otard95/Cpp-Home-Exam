#include "Headers/Transform.h"

using namespace CDP;

Transform::Transform(std::vector<std::shared_ptr<Component>> &components, GameObject& gobj)
	: Component(components, gobj)
{}

Vector2<double> const& Transform::Position() {
	return m_position;
}

void Transform::Translate(const Vector2<double> &translation) {
	m_position += translation;
}

void Transform::Translate(double x, double y) {
	m_position.x += x;
	m_position.y += y;
}

void Transform::SetPosition(const Vector2<double> &v) {
	m_position = v;
}

void Transform::SetPosition(double x, double y) {
	m_position.x = x;
	m_position.y = y;
}
