#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <vector>
#include <map>
#include "ColliderCore.h"
#include "RigidbodyCore.h"
#include "Collider.h"

namespace CDP {

	class Physics {

		Physics () = default;
		static Physics m_instance;
		
		std::map<RigidbodyCore, ColliderCore> m_rigidbody_object_sets;
		std::vector<ColliderCore> m_collider_cores;

	public:
		static Physics& Instance ();
		Physics (Physics const &) = delete;
		Physics& operator= (const Physics&) = delete;
		~Physics () = default;

		void Update ();

	};


}

#endif
