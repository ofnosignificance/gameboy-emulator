#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "SDL_stuff.hpp"
#include "Common.hpp"

namespace DMG01
{
	void Generic_SDL_Window::create_window()
	{
		this->window = SDL_CreateWindow(WINDOW_NAME_DEBUG,
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										WINDOW_SIZE_X,
										WINDOW_SIZE_Y,
										1);
		if(!this->window) {
			throw std::runtime_error("Failed to create SDL window");
		}
		this->renderer = SDL_CreateRenderer(this->window, -1, 0);
		if(!this->renderer) {
			throw std::runtime_error("Failed to create SDL renderer");
		}
	}
	void Generic_SDL_Window::create_text(const char* message)
	{
		TTF_Init();
		TTF_Font* font = TTF_OpenFont(FONT_DEFAULT_DEBUG,
									  FONT_SIZE__DEFAULT_DEBUG);
		if(!font) {
			throw std::runtime_error("Couldn't load font for SDL window");
		}
	    this->surface = TTF_RenderText_Solid(font, messsage, this->white);
		this->texture = SDL_CreateTextureFromSurface(renderer, surface);
		this->rectangle.x = WINDOW_SIZE_X - surface->w * 0.5;
		this->rectangle.y = WINDOW_SIZE_Y - surface->h * 0.5;
		this->rectangle.w = surface->w;
		this->rectangle.h = surface->h;

		SDL_FreeSurface(surface);
		TTF_Quit();
	}
	bool Generic_SDL_Window::check_polling_event()
	{
		while(SDL_PollEvent(&this->event)) {
			switch(event.type) {
			case SDL_QUIT: return false;
			}
		}
		return true;
	}
	void Generic_SDL_Window::render_text()
	{
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
		SDL_RenderClear(this->renderer);
		SDL_RenderCopy(this->renderer, this->texture, NULL, &this->rectangle);
		SDL_RenderPresent(this->renderer);
		SDL_Delay(10);
	}
	void Generic_SDL_Window::clear_memory()
	{
		SDL_DestroyTexture(this->texture);
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		SDL_Quit();
	}
}
