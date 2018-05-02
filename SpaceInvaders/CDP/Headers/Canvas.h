#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <string>
#include <SDL.h>
#include "Color.h"

namespace CDP {

	class Canvas {

	private:
		Canvas();

		static Canvas m_instance;

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		Color m_background;

	public:
		static Canvas& Instance();
		Canvas(Canvas const &) = delete;
		Canvas& operator=(const Canvas&) = delete;

		SDL_Renderer* GetRenderer() const;
		void SetTitle(std::string& title);
		void RenderFrame() const;

		~Canvas();
	};

}

#endif