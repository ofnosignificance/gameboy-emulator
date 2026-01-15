/** @file Processor.cpp */

#include <memory>
#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <cstdlib>
#include <bitset>
#include <iostream>

#include "Processor.hpp"
#include "Memory.hpp"

/** * @name Register shorthands
 * These macros are there so I don't have to write out 
 * the whole union's name every time I want to access 
 * a register.
 * @{
 */
#define R_A sm83.af.byte.higher
#define R_F sm83.af.byte.lower
#define R_AF sm83.af.word 
#define R_H sm83.hl.byte.higher
#define R_L sm83.hl.byte.lower
#define R_HL sm83.hl.word
#define R_D sm83.de.byte.higher
#define R_E sm83.de.byte.lower
#define R_DE sm83.de.word
#define R_B sm83.bc.byte.higher
#define R_C sm83.bc.byte.lower
#define R_BC sm83.bc.byte.word
#define R_PC sm83.pc
#define R_SP sm83.sp
/** @} */

/** * @name Flag shorthands 
 * Same as with the register shorthands, just 
 * convenience.
 * @{
 */
#define F_CARRY 4
#define F_HALF_CARRY 5
#define F_SUBSTRACTION 6
#define F_ZERO 7
/** @} */


namespace DMG01
{
	
	inline void SM83::add_cycles(Cycles& cycles, const uint32_t count)
	{
		cycles.total_cycles += count; 
	}

	void SM83::set_flag(SM83& sm83, uint8_t val, bool on=true)
	{
		std::bitset<8>(sm83.af.byte.lower).set(val, on);
	}

	/*
	  @brief Loads the ROM/executable into the emulator
	*/
	void SM83::load_bin(const std::string& filename, Memory& memory)
	{
		std::ifstream f((filename), std::ios_base::binary);
		if(!f) throw std::runtime_error("Failed to open the file");
		f.seekg(0, std::ios_base::end);
		auto f_size = f.tellg();
		f.seekg(0, std::ios_base::beg);
		f.read(reinterpret_cast<char*>(memory.space.get()), f_size);
	}

	template <typename T1, typename T2>
	inline void SM83::ld_imm(T1& reg, const T2& data)
	{
		reg = static_cast<T1>(data);
	}

	template <typename T1, typename T2>
	inline void SM83::ld_reg(T1& reg1, const T2& reg2)
	{
		reg1 = reg2;
	}

	template <typename T>
	inline void SM83::inc_reg(T& val)
	{
		val++;
	}

	template <typename T>
	inline void SM83::dec_reg(T& val)
	{
		val--;
	}

	inline void SM83::rlca(SM83& sm83)
	{
		R_A = (R_A >> 1 | R_A << 7);
		if(CHECK_BIT(R_F, 7)) 
			sm83.set_flag(R_F, F_CARRY, true);
		else if(!CHECK_BIT(R_F, 7)) 
			sm83.set_flag(R_F, F_CARRY, false);
	}
	/*
	  @brief Processes opcodes and calls the according function
	  @param opcode The opcode it should process
	*/
	void SM83::process_opcodes(const uint8_t opcode, Memory& memory, SM83& sm83)
	{
		switch(opcode)
		{
		case 0x00: /* NOP */
			add_cycles(cycles, 4);
			break;
		case 0x01: /* LD BC, n16 */
			ld_imm(R_BC, memory.space[R_PC++]);
			add_cycles(cycles, 12);
			break;
		case 0x02: /* LD (BC), A */
			ld_reg(memory.space[R_BC, R_A);
			add_cycles(cycles, 8);
			break;
		case 0x03: /* INC BC */ 
			inc_reg(R_BC);
			add_cycles(cycles, 8);
			break;
		case 0x04: /* INC B */
			inc_reg(R_B);
			add_cycles(cycles, 4);
			break;
		case 0x05: /* DEC B */
			dec_reg(R_B);
			add_cycles(cycles, 4);
			break;
		case 0x06: /* LD B, d6 */
			ld_imm(R_B, memory.space[R_PC++]);
			add_cycles(cycles, 8);
			break;
		case 0x07: /* RLCA */
			rlca
				add_cycles(cycles, 4);
			break;
		default:
			std::cout << "The program has seemingly run into an unrecognized opcode\n";
			break;
		}
	}
}
