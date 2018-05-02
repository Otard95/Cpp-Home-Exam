#ifndef __KEYS_H__
#define __KEYS_H__

#include <map>
#include <SDL.h>

namespace CDP {

	enum class Keys {

		W,
		A,
		S,
		D,
		Shift,
		Esc

	};

	static std::map<Keys, SDL_Scancode> const MapKeys = {
		{ Keys::W, SDL_SCANCODE_W },
		{ Keys::A, SDL_SCANCODE_A },
		{ Keys::S, SDL_SCANCODE_S },
		{ Keys::D, SDL_SCANCODE_D },
		{ Keys::Shift, SDL_SCANCODE_LSHIFT },
		{ Keys::Esc, SDL_SCANCODE_ESCAPE }
	};

}

#endif
