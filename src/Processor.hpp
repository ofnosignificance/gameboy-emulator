#pragma once

#include <cstdint>
#include "Memory.hpp"

namespace DMG01
{
	class SM83
	{
    public:
		struct Cycles
		{
			uint32_t total_cycles;
		};
		union Registers
		{
			uint16_t word;
			struct
			{
				uint8_t higher;
				uint8_t lower;
			} byte;
		};
		Registers af;
		Registers hl;
		Registers de;
		Registers bc;
		uint16_t pc;
		uint16_t sp;
		Cycles cycles;
		bool stop_state;
		inline void add_cycles(Cycles& cycles, const uint32_t count);
		inline void set_flag(uint8_t& f, uint8_t index, bool on=true);
		inline bool test_flag(uint8_t& f, const uint8_t index);
		void load_bin(const std::string& filename, Memory& memory);
		template <typename T1, typename T2>
		inline void ld_imm(T1& reg, const T2& data);
		template <typename T1, typename T2>
		inline void ld_reg(T1& reg1, const T2& reg2);
		template <typename T>
		inline void inc_reg(T& val);
		template <typename T>
		inline void dec_reg(T& val);
		inline void rlca(SM83& sm83);
		template <typename T1, typename T2>
		inline void add_reg(T1& aug, const T2& add);
		inline void rrca(SM83& sm83);
		inline void stop(SM83& sm83, Memory& memory);
		void process_opcodes(const uint8_t opcode, Memory& memory, SM83& sm83);
	};   
}
