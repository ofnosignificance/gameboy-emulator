#include <SDL2/SDL.h>

#include <iostream>
#include <cstdlib>

#include "Processor.hpp"
#include "Memory.hpp"
#include "Common.hpp"

int main(int argc, char* argv[])
{
	
	DMG01::SM83 sm83;
	DMG01::Memory memory;
	while(sm83.pc < DMG01::MEMORY_SIZE) {
		const uint8_t opcode = memory.space[sm83.pc];
		sm83.pc++;
		sm83.process_opcodes(opcode, memory, sm83);
	}
}

