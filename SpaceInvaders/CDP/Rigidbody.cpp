#include "Headers/Physics.h"
#include "Headers/Rigidbody.h"

using namespace CDP;

Rigidbody::Rigidbody(std::vector<std::shared_ptr<Component>> &components,
										 GameObject& go,
										 RigidbodyCore& core)
:	Component(components, go)
,	m_core(core)
{}
