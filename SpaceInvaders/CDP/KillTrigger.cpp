#include "Headers/KillTrigger.h"
#include "Headers/GameCore.h"
#include <iostream>

using namespace CDP;

KillTrigger::KillTrigger(std::vector<std::shared_ptr<Component>> &cmp,
												 GameObject & go)
	: Component(cmp, go)
{}

void KillTrigger::OnCollision(Collider& col) {
		if (!(GetGameObject().GetName() == "AlienBullet" && col.GetGameObject().GetName() == "Invader") ||
			(GetGameObject().GetName() == "Bullet" && col.GetGameObject().GetName() == "Player"))
			m_game_object.Enable(false);
}

