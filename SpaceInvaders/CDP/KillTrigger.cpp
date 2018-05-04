#include "Headers/KillTrigger.h"
#include "Headers/GameCore.h"
#include <iostream>

using namespace CDP;

KillTrigger::KillTrigger(std::vector<std::shared_ptr<Component>> &cmp,
												 GameObject & go)
	: Component(cmp, go)
{}

void KillTrigger::OnCollision(Collider& col) {
	GameCore::Instance().Destroy(std::shared_ptr<GameObject>(&col.GetGameObject()));
}

