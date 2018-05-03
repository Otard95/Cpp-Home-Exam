#include "Headers/GameObject.h"
#include "Headers/Transform.h"
#include <iostream>

using namespace CDP;

GameObject::GameObject(nlohmann::json& jsonObject)
{
	m_name = jsonObject["name"].get<std::string>();

	int i = 1;

	for (nlohmann::json::iterator it = jsonObject["components"].begin(); it != jsonObject["components"].end(); ++it)
	{
		const std::string str = it.key();

		if(it.key() == "PlayerControls") 
		{
			//TO DO: add player component.
		}
		else if (it.key() == "Transform")
		{
			Transform t = Transform(m_components, *this);
		}
	}
	std::cout << m_name << std::endl;
}

GameObject::~GameObject()
{
}

void CDP::GameObject::Update()
{
	if (m_physics_triplet)
	{
		// component force update
	}

	// for each component -> update
}
