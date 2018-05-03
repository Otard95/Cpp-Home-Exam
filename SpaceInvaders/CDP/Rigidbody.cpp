#include "Headers/Physics.h"
#include "Headers/Rigidbody.h"

using namespace CDP;

Rigidbody::Rigidbody(std::vector<std::shared_ptr<Component>> &components,
										 GameObject& go,
										 Collider& col,
										 Transform& trans)
:	Component(components, go)
,	collider(col)
,	transform(trans)
{}

void Rigidbody::Start(){}
