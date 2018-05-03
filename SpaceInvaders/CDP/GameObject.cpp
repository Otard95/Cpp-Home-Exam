#include "Headers/GameObject.h"
#include "Headers/Transform.h"
#include <iostream>

using namespace CDP;

GameObject::GameObject(const std::string str)
{
	//std::cout << str << std::endl;
	m_name = str;
}

std::string GameObject::GetName() const
{
	return m_name;
}

std::vector<Component*>& GameObject::GetComponents()
{
	return m_components;
}

GameObject::~GameObject()
{
}

void CDP::GameObject::Update()
{
}
