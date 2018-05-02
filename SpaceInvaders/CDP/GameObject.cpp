#include "Headers/GameObject.h"

using namespace CDP;

GameObject::GameObject() {
}

GameObject::~GameObject() {
}

void CDP::GameObject::Update() {

	if (m_physics_triplet) {
		// component force update
	}

	// for each component -> update

}
