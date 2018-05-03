#ifndef __PHYSICS_H__
#define __PHYSICS_H__

namespace CDP {

	class Physics {

		Physics () = default;
		static Physics m_instance;

	public:
		static Physics& Instance ();
		Physics (Physics const &) = delete;
		Physics& operator= (const Physics&) = delete;
		~Physics () = default;

		void Update ();

	};

}

#endif
