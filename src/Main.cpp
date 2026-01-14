#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>

#include "SDL_stuff.hpp"
#include "Debugger.hpp"
#include "Processor.hpp"
#include "Memory.hpp"
#include "Common.hpp"

int main(int argc, char* argv[])
{
	(void)argc; (void)argv;
	DMG01::SM83 sm83;
	DMG01::Memory memory;

	DMG01::Generic_SDL_Window debugger_window(800, 200);
	debugger_window.create_window();
	debugger_window.update_text("Debugger started.");
	while(sm83.pc < DMG01::MEMORY_SIZE) {
		char buffer[256];
		const uint8_t opcode = memory.space[sm83.pc];
		sm83.pc++;
		sm83.process_opcodes(opcode, memory, sm83);
		debugger_window.check_polling_event();
		snprintf(buffer, sizeof(buffer),
			"PC: 0x%04X SP: 0x%04X 0x%04X BC: 0x%04X DE: 0x%04X HL: 0x%04X",
			sm83.pc, sm83.sp, sm83.af.word, sm83.bc.word, sm83.de.word, sm83.hl.word);
		debugger_window.update_text(buffer);
		debugger_window.render_text();
	}
}

