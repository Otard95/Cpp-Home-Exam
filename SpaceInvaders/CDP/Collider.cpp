#include "Headers/Collider.h"
#include "Headers/Physics.h"

using namespace CDP;

Collider::Collider(std::vector<std::shared_ptr<Component>> &components,
									 GameObject& go,
									 ColliderCore & core)
	: Component(components, go)
	, m_core(core)
{}

void Collider::Start() {

}

