#pragma once
#include <map>
#include <SDL.h>

namespace CDP {

	enum class MouseButton {

		Left,
		Right,
		Middle

	};

	static std::map<MouseButton, Uint32> const MapMouseButtons = {
		{ MouseButton::Left, SDL_BUTTON_LMASK },
		{ MouseButton::Right, SDL_BUTTON_RMASK },
		{ MouseButton::Middle, SDL_BUTTON_MMASK }
	};

}