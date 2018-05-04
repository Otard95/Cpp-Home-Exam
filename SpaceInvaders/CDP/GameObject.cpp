#include <algorithm>
#include "Headers/GameObject.h"
#include "Headers/Transform.h"

using namespace CDP;

GameObject::GameObject(const std::string str)
{
	//std::cout << str << std::endl;
	m_name = str;
}

void GameObject::Enable(bool enabled) {
	std::for_each(m_components.begin(), m_components.end(), [&enabled](std::shared_ptr<Component> c) {
		c->enabled = enabled;
	});
}

std::string GameObject::GetName() const
{
	return m_name;
}

std::vector<std::shared_ptr<Component>>& GameObject::GetComponents()
{
	return m_components;
}

void CDP::GameObject::Start() {

	std::for_each(m_components.begin(), m_components.end(), [] (std::shared_ptr<Component> c) {
		c->Start();
	});

}
