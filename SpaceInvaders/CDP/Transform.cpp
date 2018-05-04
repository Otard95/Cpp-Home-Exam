#include "Headers/Transform.h"
#include <iostream>

using namespace CDP;

Transform::Transform(std::vector<std::shared_ptr<Component>>& components, GameObject& gobj)
	: Component(components, gobj)
	  , m_position(Vector2<double>())
{
}

Transform::~Transform()
{
}

Vector2<double> const& Transform::Position()
{
	return m_position;
}

void Transform::Translate(const Vector2<double>& translation)
{
	m_position += translation;
}

void Transform::Translate(double x, double y)
{
	m_position.x += x;
	m_position.y += y;
}

void Transform::SetPosition(const Vector2<double>& v)
{
	m_position = v;
}

void Transform::SetPosition(double x, double y)
{
	m_position.x = x;
	m_position.y = y;
	//std::cout << "position set to " << x << ", " << y << std::endl;
}
