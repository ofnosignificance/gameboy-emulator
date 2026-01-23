#pragma once

#include <SDL2/SDL.h>

namespace DMG01
{
	/** * 
	 * @name PROGRAM_NAME
	 * @brief This has to be the same name as in the Makefile,
	 * or there will be inconsistencies at some places
	 */
	constexpr const char* PROGRAM_NAME = "gameboy";
	constexpr uint32_t MEMORY_SIZE = 0xffff;
	constexpr uint32_t WINDOW_SIZE_X = 800;
	constexpr uint32_t WINDOW_SIZE_Y = 600;
	constexpr const char* WINDOW_NAME_DEBUG = "gameboy debugger";
	constexpr const char* FONT_DEFAULT_DEBUG = "./res/pixelated-elegance-font/PixelatedEleganceRegular-ovyAA.ttf";
	constexpr uint32_t FONT_SIZE_DEFAULT_DEBUG = 20;
}
