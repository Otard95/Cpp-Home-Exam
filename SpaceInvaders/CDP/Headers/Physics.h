#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <vector>
#include "Rigidbody.h"
#include "Collider.h"

namespace CDP {

	class Physics {

		Physics () = default;
		static Physics m_instance;

		std::shared_ptr<std::vector<Rigidbody>> m_rigidbodies;
		std::shared_ptr<std::vector<Collider>> m_colliders;
		//std::shared_ptr<std::vector<Transform>> m_transforms;

	public:
		static Physics& Instance ();
		Physics& Init (std::vector<Rigidbody> * rigidbodies,
									 std::vector<Collider> * colliders
									 /*std::vector<Transform> * transforms*/);
		Physics (Physics const &) = delete;
		Physics& operator= (const Physics&) = delete;
		~Physics () = default;

		void Update ();

	};

}

#endif
