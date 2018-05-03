#include <algorithm>
#include "Headers/Collider.h"
#include "Headers/Physics.h"

using namespace CDP;

Collider::Collider(std::vector<Component*> &components,
									 GameObject& go,
									 Transform& trans)
	: Component(components, go)
	, transform(trans) {
}

void Collider::Start() {

}

void CDP::Collider::UpdateSize(Vector2<double>& v) {
	m_bound_size.x = v.x;
	m_bound_size.y = v.y;

	m_size = m_bound_size.Length();
	m_extent = m_size / 2;
}

void CDP::Collider::UpdateSize(double x, double y) {
	m_bound_size.x = x;
	m_bound_size.y = y;

	m_size = m_bound_size.Length();
	m_extent = m_size / 2;
}

Vector2<double> Collider::BoundsSize() {
	return m_bound_size;
}

double CDP::Collider::Size() {
	return m_size;
}

double Collider::Extent() {
	return m_extent;
}

void Collider::CollisionEvent(Collider& collider) {
	
	std::for_each(m_sibling_components.begin(), m_sibling_components.end(), [&collider] (Component* c) {
		c->OnCollision(collider);
	});

}
