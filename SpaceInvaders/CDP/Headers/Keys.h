#ifndef __KEYS_H__
#define __KEYS_H__

#include <map>
#include <SDL.h>

namespace CDP {

	enum class Keys {

		A,
		D,
		Space,
		Esc

	};

	static std::map<Keys, SDL_Scancode> const MapKeys = {
		{ Keys::A, SDL_SCANCODE_A },
		{ Keys::D, SDL_SCANCODE_D },
		{ Keys::Space, SDL_SCANCODE_SPACE },
		{ Keys::Esc, SDL_SCANCODE_ESCAPE }
	};

}

#endif
