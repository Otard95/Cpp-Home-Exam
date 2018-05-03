#include "Headers/Collider.h"
#include "Headers/Physics.h"

using namespace CDP;

Collider::Collider(std::vector<Component*> &components,
									 GameObject& go,
									 Transform& trans)
	: Component(components, go)
	, transform(trans)
{}

void Collider::Start() {

}