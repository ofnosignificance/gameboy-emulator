#include <SDL2/SDL.h>

#include <iostream>
#include <cstdlib>

#include "Processor.hpp"
#include "Memory.hpp"
#include "Common.hpp"

namespace DMG01 {
	int main(int argc, char* argv[])
	{
	
		SM83 sm83;
		Memory memory;
		while(sm83.pc < MEMORY_SIZE && window_debugger != NULL) {
			memory.space[sm83.pc];
			sm83.pc++;
			sm83.process_opcode(opcode, memory, sm83);
			display_debug_info();
			while(SDL_PollEvent(&event)) {
				if(event.type == SDL_QUIT) window_debugger = NULL;
			}
		}
	}


}
