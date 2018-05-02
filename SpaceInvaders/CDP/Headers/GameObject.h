#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include <memory>
#include "CDP_fwd.h"
#include "Triplet.h"
#include "Vector2.h"

namespace CDP {

	class GameObject {

		std::unique_ptr<Triplet<Vector2<double>,
										ColliderCore,
										RigidbodyCore>> m_physics_triplet;
		std::vector<std::shared_ptr <Component>> m_components;

	public:
		GameObject();
		~GameObject();

		void Update ();

	};

}

#endif // !__GAMEOBJECT_H__


