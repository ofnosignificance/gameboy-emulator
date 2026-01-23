#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <string>

#include "SDL_stuff.hpp"
#include "Debugger.hpp"
#include "Processor.hpp"
#include "Memory.hpp"
#include "Common.hpp"

static inline void show_help()
{
	std::cout << "Usage: ./PROGRAM_NAME [EXECUTABLE] [OPTIONS]\n";
	std::cout << "Emulate a given DMG-01 ROM/executable.\n";
	std::cout << "The first argument is always the file to be executed\n";
}


int main(int argc, char* argv[])
{
	if(argc < 2) {
		show_help(); 
		return EXIT_FAILURE;
	}
	DMG01::SM83 sm83;
	DMG01::Memory memory;
	std::string exec_file(argv[1]);
	sm83.load_bin(exec_file, memory);
	DMG01::Generic_SDL_Window debugger_window(800, 600);
	debugger_window.create_window();
	debugger_window.update_text("Debugger started.");
	static bool should_display = true;
	sm83.stop_state = false;
	while((sm83.pc < DMG01::MEMORY_SIZE) && should_display) {
		char buffer[256];
		if(!sm83.stop_state) {
			const uint8_t opcode = memory.space[sm83.pc];
			sm83.pc++;
			sm83.process_opcodes(opcode, memory, sm83);
		}
		should_display = debugger_window.check_polling_event();
		snprintf(buffer, sizeof(buffer),
				 "PC: 0x%04X SP: 0x%04X 0x%04X BC: 0x%04X DE: 0x%04X HL: 0x%04X",
				 sm83.pc, sm83.sp, sm83.af.word, sm83.bc.word, sm83.de.word, sm83.hl.word);
		debugger_window.update_text(buffer);
		debugger_window.render_text();

		SDL_Delay(1);
	}
	return EXIT_SUCCESS;
}

