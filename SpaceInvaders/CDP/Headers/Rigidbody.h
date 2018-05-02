#ifndef __RIGIDBODY_COMPONENT_H__
#define __RIGIDBODY_COMPONENT_H__

#include <memory>
#include "RigidbodyCore.h"
#include "Component.h"

namespace CDP {

	class Rigidbody : public Component {
	public:

		RigidbodyCore& m_core;

		Rigidbody(std::vector<std::shared_ptr<Component>> &components,
							GameObject& go,
							RigidbodyCore& core);
		~Rigidbody() = default;

		void Start () override;

	};

}

#endif
