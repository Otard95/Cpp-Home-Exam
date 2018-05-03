#include <iostream>
#include "Headers\Sprite.h"
#include "Headers\Transform.h"
#include "Headers\Canvas.h"
#include <SDL.h>

using namespace CDP;

Sprite::Sprite(std::vector<Component*> &components,
							 GameObject& gobj,
							 std::string texture_file)
	: Component(components, gobj)
	, m_renderer(Canvas::Instance().GetRenderer())
	, m_texture_file(texture_file)
	, m_texture(nullptr)
{}

Sprite::~Sprite() {
	if (m_texture != nullptr) SDL_DestroyTexture(m_texture);
}

void Sprite::Start() {

	m_transform = GetComponent<Transform>();

	SDL_Surface* surface = SDL_LoadBMP(m_texture_file.c_str());
	// Make sure the surface was loaded.
	if (surface == nullptr) {
		std::cerr << "Sprite - Failed to load texture image: "
			<< SDL_GetError() << std::endl;
		return;
	}

	// Create the texture from the suface
	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	// make sure the texture was created
	if (m_texture == nullptr) {
		std::cout << "Sprite - Failed to create texture from surface: "
			<< SDL_GetError() << std::endl;
		SDL_FreeSurface(surface);
		return;
	}
	
	// Use surface hight and width
	m_coords.h = surface->h;
	m_coords.w = surface->w;
	// Set anchor point to center of sprite
	m_anchor_point_offset.x = surface->w / 2;
	m_anchor_point_offset.y = surface->h / 2;
	// Use transform's position
	m_coords.x = m_transform->Position().x - m_anchor_point_offset.x;
	m_coords.y = m_transform->Position().y - m_anchor_point_offset.y;

	SDL_FreeSurface(surface);

}

void Sprite::Update() {

	m_transform->SetPosition(60, 60);
	// Update coords
	m_coords.x = m_transform->Position().x - m_anchor_point_offset.x;
	m_coords.y = m_transform->Position().y - m_anchor_point_offset.y;
	// Render Sprite
	if (m_texture != nullptr) SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_coords);

}
