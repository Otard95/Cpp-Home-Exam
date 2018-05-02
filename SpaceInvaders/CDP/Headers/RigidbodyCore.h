#ifndef __RIGIDBODY_CORE_H__
#define __RIGIDBODY_CORE_H__

#include "Vector2.h"

namespace CDP {

	struct RigidbodyCore {

		Vector2<double> m_velocity;
		bool m_use_gravity;

	};

}

#endif
