#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <vector>
#include "Time.h"
#include "Rigidbody.h"
#include "Collider.h"

namespace CDP {

	class Physics {

		Physics ();
		static Physics m_instance;

		Time& m_time;

		std::vector<std::shared_ptr<Rigidbody>> m_rigidbodies;
		std::vector<std::shared_ptr<Collider>> m_colliders;
		//std::shared_ptr<std::vector<Transform>> m_transforms;

	public:
		static Physics& Instance ();
		void Init (std::vector<std::shared_ptr<Rigidbody>>& rigidbodies,
									 std::vector<std::shared_ptr<Collider>>& colliders
									 /*std::vector<Transform> * transforms*/);
		Physics (Physics const &) = delete;
		Physics& operator= (const Physics&) = delete;
		~Physics () = default;

		void Update ();

	};

}

#endif
