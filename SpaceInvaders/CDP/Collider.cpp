#include "Headers/Collider.h"
#include "Headers/Physics.h"

using namespace CDP;

Collider::Collider(std::vector<std::shared_ptr<Component>> &components,
									 GameObject& go,
									 Transform& trans)
	: Component(components, go)
	, transform(trans)
{}

void Collider::Start() {

}

