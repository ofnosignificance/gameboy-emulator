#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "SDL_stuff.hpp"
#include "Common.hpp"

namespace DMG01
{
	class Debugger_Window : public Generic_SDL_Window
	{
	public:
		char* debug_info_string;
		void read_debug_info();
	};
}
