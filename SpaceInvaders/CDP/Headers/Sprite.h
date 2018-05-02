#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include <string>
#include <memory>
#include <SDL.h>
#include "Component.h"
#include "Vector2.h"

namespace CDP {

	class Sprite : public Component {

	private:
		// SDL Requirements
		SDL_Renderer * const m_renderer;
		// Texture
		Vector2<double> m_anchor_point_offset;
		std::string m_texture_file;
		SDL_Texture* m_texture;
		SDL_Rect m_coords;

		// Required Components
		std::shared_ptr<Transform> m_transform;

	public:
		Sprite(std::vector<std::shared_ptr<Component>> &components, GameObject&, std::string);
		~Sprite();

		void Start() override;
		void Update() override;

	};

}

#endif // !__SPRITE_COMPONENT_H__
