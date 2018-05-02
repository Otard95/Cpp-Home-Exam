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

void CDP::GameObject::Instantiate(nlohmann::json&) {
	// do some json stuff
}

void CDP::GameObject::Destroy(GameObject* go) {
	//search and destroy
}
