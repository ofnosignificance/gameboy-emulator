#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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
		Generic_SDL_Window(const uint32_t win_x, const uint32_t win_y);
		~Generic_SDL_Window();
		void create_window();
		void update_text(const char* message);
		bool check_polling_event();
		void render_text();
	private:
		uint32_t win_x;
		uint32_t win_y;
		const SDL_Color red = {255, 0, 0, 0};
		const SDL_Color black = {0, 0, 0, 255};
		const SDL_Color white = {255, 255, 255, 255};
	};
}
