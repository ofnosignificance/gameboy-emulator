/** @file Processor.cpp */

#include <memory>
#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <cstdlib>
#include <bitset>

#include "Memory.hpp"
#include "Processor.hpp"

#define F_CARRY 4
#define F_HALF_CARRY 5
#define F_SUBSTRACTION 6
#define F_ZERO 7

namespace DMG01
{
	
	inline void SM83::add_cycles(Cycles& cycles, const uint32_t count)
	{
		cycles.total_cycles += count; 
	}

	void Z80::set_flag(SM83& sm83, uint8_t val)
	{
		std::bitset<8>(sm83.af.byte.lower).set(val);
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

	inline void SM83::ld_reg(T1& reg1, const T2& reg2)
	{
		reg = reg2;
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

	inline void SM83::rlca(uint8_t& reg)
	{
		if()
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
			add_cycles(cycles, 1);
			break;
		case 0x01: /* LD BC, n16 */
			ld_imm(sm83.bc.word, memory.space[sm83.pc++]);
			add_cycles(cycles, 3);
			break;
		case 0x02: /* LD (BC), A */
			ld_reg(memory.space[sm83.bc.word], sm83.af.byte.higher);
			add_cycles(cycles, 1);
			break;
		case 0x03: /* INC BC */ 
			inc_reg(sm83.bc.word);
			add_cycles(cycles, 1);
			break;
		case 0x04: /* INC B */
			inc_reg(sm83.bc.byte.higher);
			add_cycles(cycles, 1);
			break;
		case 0x05: /* DEC B */
			dec_reg(sm83.bc.byte.higher);
			add_cycles(cycles, 1);
			break;
		case 0x06: /* LD B, d6 */
			ld_imm(sm83.bc.byte.higher, ram.space[sm83.pc++]);
			add_cycles(cycles, 2);
			break;
		case 0x07:
			
			add_cycles(cycles, 1);
			break;
		default:
			std::cout << "The program has seemingly run into an unrecognized opcode\n";
			break;
		}
	}
}
