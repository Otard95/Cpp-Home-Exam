#include "Headers/GameCore.h"

using namespace CDP;

// Richard

GameCore::GameCore()
{
}


GameCore::~GameCore()
{
}

// end

// Stian

std::shared_ptr<Transform> GameCore::CreateTransform(std::vector<std::shared_ptr<Component>> &components, GameObject& go )
{
	m_transforms.push_back(Transform(components, go));
}


// end
