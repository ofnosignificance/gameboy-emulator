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
#include "Common.hpp"

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
#define R_BC sm83.bc.word
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

#define ADD_CYC(val) add_cycles(cycles, val)

namespace DMG01
{
	
	inline void SM83::add_cycles(Cycles& cycles, const uint32_t count)
	{
		cycles.total_cycles += count; 
	}

	inline void SM83::set_flag(uint8_t& f, const uint8_t index, const bool on)
	{
		std::bitset<8>(f).set(index, on);
	}
	
	inline bool SM83::test_flag(uint8_t& f, const uint8_t index)
	{
		return std::bitset<8>(f).test(index);
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
		if(sm83.test_flag(R_F, F_CARRY)) 
			sm83.set_flag(R_F, F_CARRY, true);
		else if(sm83.test_flag(R_F, F_CARRY)) 
			sm83.set_flag(R_F, F_CARRY, false);
	}
	
	template <typename T1, typename T2>
	inline void SM83::add_reg(T1& aug, const T2& add)
	{
		aug =+ add;
	}
	
	inline void SM83::rrca(SM83& sm83)
	{
		R_A = (R_A << 1 | R_A >> 7);
		if(sm83.test_flag(R_F, F_CARRY)) 
			sm83.set_flag(R_F, F_CARRY, true);
		else if(sm83.test_flag(R_F, F_CARRY)) 
			sm83.set_flag(R_F, F_CARRY, false);
	}

	inline void SM83::stop(SM83& sm83, Memory& memory)
	{
		R_PC++;
		memory.space[0xff04] = 0x00;
		sm83.stop_state = true;
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
			ADD_CYC(4);
			break;
		case 0x01: /* LD BC, n16 */
			ld_imm(R_BC, memory.space[R_PC++]);
			ADD_CYC(12);
			break;
		case 0x02: /* LD (BC), A */
			ld_reg(memory.space[R_BC], R_A);
			ADD_CYC(8);
			break;
		case 0x03: /* INC BC */ 
			inc_reg(R_BC);
			ADD_CYC(8);
			break;
		case 0x04: /* INC B */
			inc_reg(R_B);
			ADD_CYC(4);
			break;
		case 0x05: /* DEC B */
			dec_reg(R_B);
			ADD_CYC(4);
			break;
		case 0x06: /* LD B, d6 */
			ld_imm(R_B, memory.space[R_PC++]);
			ADD_CYC(8);
			break;
		case 0x07: /* RLCA */
			rlca(sm83);
			ADD_CYC(4);
			break;
		case 0x08: /* LD (a16), SP */
			ld_imm(memory.space[R_PC++], R_SP);
			ADD_CYC(20);
			break;
		case 0x09:
			add_reg(R_HL, R_BC);
			ADD_CYC(8);
			break;
		case 0x0a:
			ld_reg(R_A, memory.space[R_BC]);
			ADD_CYC(8);
			break;
		case 0x0b:
			dec_reg(R_BC);
			ADD_CYC(8);
			break;
		case 0x0c:
			inc_reg(R_C);
			ADD_CYC(4);
			break;
		case 0x0d:
			dec_reg(R_C);
			ADD_CYC(4);
			break;
		case 0x0e:
			ld_imm(R_C, memory.space[R_PC++]);
			ADD_CYC(8);
			break;
		case 0x0f:
			rrca(sm83);
			ADD_CYC(4);
			break;
		case 0x10:
			stop(sm83, memory);
			ADD_CYC(4);
			break;
		case 0x11:
			ld_imm(R_DE, memory.space[R_PC++]);
			ADD_CYC(12);
			break;
		case 0x12:
			ld_imm(memory.space[R_DE], R_A);
			ADD_CYC(8);
			break;
		case 0x13:
			inc_reg(R_DE);
			ADD_CYC(8);
			break;
		case 0x14:
			inc_reg(R_D);
			ADD_CYC(4);
			break;
		case 0x15:
			dec_reg(R_D);
			ADD_CYC(4);
			break;
		case 0x16:
			ld_reg(R_DE, memory.space[R_PC++]);
			ADD_CYC(8);
			break;
		case 0x017:
			ADD_CYC
			break;
		default:
			std::cout << "The program has seemingly run into an unrecognized opcode\n";
			break;
		}
	}
}
