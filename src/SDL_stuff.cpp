#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>

#include "SDL_stuff.hpp"
#include "Common.hpp"

namespace DMG01
{
	Generic_SDL_Window::Generic_SDL_Window(const uint32_t win_x, const uint32_t win_y)
	{
		this->win_x = win_x;
		this->win_y = win_y;
	}
	Generic_SDL_Window::~Generic_SDL_Window()
	{
		SDL_DestroyTexture(this->texture);
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		TTF_Quit();
		SDL_Quit();
	}
	void Generic_SDL_Window::create_window()
	{
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			throw std::runtime_error("SDL couldn't be intitalized");
		}
		if(TTF_Init() < 0) {
			throw std::runtime_error("SDL_ttf couldn't be initalized");
		}
		this->window = SDL_CreateWindow(WINDOW_NAME_DEBUG,
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										this->win_x,
										this->win_y,
										SDL_WINDOW_OPENGL);
		if(!this->window) {
			throw std::runtime_error("Failed to create SDL window");
		}
		this->renderer = SDL_CreateRenderer(this->window, -1, 0);
		if(!this->renderer) {
			throw std::runtime_error("Failed to create SDL renderer");
		}
		this->font = TTF_OpenFont(FONT_DEFAULT_DEBUG,
								  FONT_SIZE_DEFAULT_DEBUG);
		if(!font) {
			throw std::runtime_error("Couldn't load font for SDL window");
		}
	}

	void Generic_SDL_Window::update_text(const char* message)
	{
		if(this->texture) SDL_DestroyTexture(this->texture);
		SDL_Surface* tmp_surface = TTF_RenderText_Solid(this->font, message, this->white);
		if(!tmp_surface) return;
		this->texture = SDL_CreateTextureFromSurface(this->renderer, tmp_surface);
		this->rectangle.x = 0;
		this->rectangle.y = 0;
		this->rectangle.w = tmp_surface->w;
		this->rectangle.h = tmp_surface->h;
		SDL_FreeSurface(tmp_surface);
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
		SDL_SetRenderDrawColor(this->renderer, 
							   this->black.r, 
							   this->black.g, 
							   this->black.b,
							   this->black.a); 
		SDL_RenderClear(this->renderer);
		if(this->texture) {
			SDL_RenderCopy(this->renderer, this->texture, NULL, &this->rectangle);
		}
		SDL_RenderPresent(this->renderer);
	}

}
