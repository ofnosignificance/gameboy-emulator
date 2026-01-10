#pragma once

#include <SDL2/SDL.h>

#include "Common.hpp"

namespace DMG01
{
	class Generic_SDL_Window
	{
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event event;
		TTF_Font* font;
		SDL_Surface* surface;
		SDL_Texture* texture;
		SDL_Rect rectangle;
		SDL_Font* font;
		void create_window();
		void create_text();
		bool check_polling_event();
		void render_text();
		void clear_memory();
	private:
		const SDL_Color red = {255, 0, 0, 0};
		const SDL_Color black = {0, 0, 0, 0};
		const SDL_Color white = {255, 255, 255, 0};
	}
}
