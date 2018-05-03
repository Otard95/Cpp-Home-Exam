#include "Headers/GameObject.h"
#include "Headers/Transform.h"
#include <iostream>

using namespace CDP;

GameObject::GameObject(const std::string str)
{
	m_name = str;

	int i = 1;

	
	std::cout << m_name << std::endl;
}

GameObject::~GameObject()
{
}

void CDP::GameObject::Update()
{
}
