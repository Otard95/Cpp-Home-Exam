#include "Headers/Component.h"

using namespace CDP;

Component::Component(std::vector<Component*> &components,
													GameObject & gobj)
	: m_sibling_components(components)
	, m_game_object(gobj)
{}



GameObject& Component::GetGameObject()
{
	return m_game_object;
}
