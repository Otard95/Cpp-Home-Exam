#include "Headers/InputManager.h"
#include "Headers/Keys.h"
#include <iostream>

using namespace CDP;

InputManager::InputManager()
	: m_num_keys(0)
	, m_keys(SDL_GetKeyboardState(&m_num_keys))
	, m_prev_keys(std::unique_ptr<Uint8>(new Uint8[m_num_keys]))
	, m_mouse_pos(Vector2<int>())
	, m_mouse_prev_pos(Vector2<int>())
	, m_mouse_btn_state(0)
	, m_mouse_prev_btn_state(0) {
	UpdateMouseState();
}

InputManager& InputManager::Instance() {

	static InputManager m_instance;
	static int m_num_instances = 0;
	m_num_instances++;

	if (m_num_instances > 1)
	{
		std::cout
			<< "Warning: More than one refrance to InputManager!\n"
			<< "         This may result in unwanted behaviour." 
			<< std::endl;
	}

	return m_instance;

}

bool InputManager::GetKeyDown(Keys key_code) const {
	return (m_keys[MapKeys.at(key_code)] != 0 &&
					m_prev_keys.get()[MapKeys.at(key_code)] == 0);
}

bool InputManager::GetKey(Keys key_code) const {
	return (m_keys[MapKeys.at(key_code)] != 0);
}

bool InputManager::GetKeyUp(Keys key_code) const {
	return (m_keys[MapKeys.at(key_code)] == 0 &&
					m_prev_keys.get()[MapKeys.at(key_code)] != 0);
}

Vector2<int> InputManager::GetMousePos() const {
	return m_mouse_pos;
}

Vector2<int> InputManager::GetMouseMovement() const {
	return m_mouse_pos - m_mouse_prev_pos;
}

bool InputManager::GetMouseButtonDown(MouseButton mouse_button) const {
	return (GetMouseButton(mouse_button) &&
					!(m_mouse_prev_btn_state & MapMouseButtons.at(mouse_button)));
}

bool InputManager::GetMouseButton(MouseButton mouse_button) const {
	return (m_mouse_btn_state & MapMouseButtons.at(mouse_button));
}

bool InputManager::GetMouseButtonUp(MouseButton mouse_button) const {
	return (!GetMouseButton(mouse_button) &&
					(m_mouse_prev_btn_state & MapMouseButtons.at(mouse_button)));
}

void InputManager::Update() {

	memcpy(m_prev_keys.get(), m_keys, m_num_keys * sizeof(Uint8));

	SDL_PumpEvents();
	UpdateMouseState();

}

InputManager::~InputManager() {
	m_prev_keys.reset();
	SDL_QuitEvent();
}

void InputManager::UpdateMouseState() {

	// Longwinded but no copy-constructor used
	m_mouse_prev_pos.SetCoords(m_mouse_pos.x, m_mouse_pos.y);
	m_mouse_prev_btn_state = m_mouse_btn_state;

	int x, y;
	m_mouse_btn_state = SDL_GetMouseState(&x, &y);
	m_mouse_pos.SetCoords(x, y);

}
