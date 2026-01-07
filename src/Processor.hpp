#pragma once

#include <cstdint>
#include "Memory.hpp"

namespace DMG01
{
	class SM83
	{
    public:
		union Registers
		{
			uint16_t word;
			struct byte
			{
				uint8_t higher;
				uint8_t lower;
			};
		};
		Registers af;
		Registers hl;
		Registers de;
		Registers bc;
		uint16_t pc;
		uint16_t sp;
		inline void add_cycles(Cycles& cycles, const uint32_t count);
		void load_bin(const std::string& filename, Memory& memory);
		template <typename T1, typename T2>
		inline void ld_imm(T1& reg, const T2& data);
		
		void process_opcodes(const uint8_t opcode, Memory& memory, Registers& registers);
	};   
}
