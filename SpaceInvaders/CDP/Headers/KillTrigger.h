#ifndef __KILLTRIGGER_COMPONENT_H__
#define __KILLTRIGGER_COMPONENT_H__

#include "CDP.h"

namespace CDP {

	class KillTrigger : public Component {

	public:
		KillTrigger(std::vector<std::shared_ptr<Component>>&,
								GameObject&);
		~KillTrigger() = default;

		void OnCollision(Collider&) override;

	};

}

#endif