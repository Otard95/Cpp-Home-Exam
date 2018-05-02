#include <iostream>
#include "Headers/Canvas.h"

using namespace CDP;

Canvas::Canvas()
	: m_window(nullptr)
	, m_renderer(nullptr)
	, m_background({0,0,0,255})
{

	m_window = SDL_CreateWindow(
		"Canvas",                             //  window title
		SDL_WINDOWPOS_UNDEFINED,              //  initial m_x position
		SDL_WINDOWPOS_UNDEFINED,              //  initial m_y position
		1600,                                 //  width, in pixels
		900,                                  //  height, in pixels
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL  // flags
	);

	if (m_window == nullptr) {
		std::cerr << "Failed to create window: "
			<< SDL_GetError() << std::endl;
		return;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	if (m_renderer == nullptr) {
		std::cerr << "Failed to create renderer: "
			<< SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_window);
		return;
	}

	SDL_SetRenderDrawColor(m_renderer,
												 m_background.r,
												 m_background.g,
												 m_background.b,
												 m_background.a);

	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);
}

Canvas& Canvas::Instance() {
	static Canvas m_instance;
	return m_instance;
}

SDL_Renderer* Canvas::GetRenderer() const {
	return m_renderer;
}

void Canvas::SetTitle(std::string& title) {
	SDL_SetWindowTitle(m_window, title.c_str());
}

void Canvas::RenderFrame() const {

	SDL_RenderPresent(m_renderer);
	SDL_SetRenderDrawColor(m_renderer,
												 m_background.r,
												 m_background.g,
												 m_background.b,
												 m_background.a);
	SDL_RenderClear(m_renderer);

}

Canvas::~Canvas() {
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}
