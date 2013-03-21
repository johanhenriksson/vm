#include "vm.h"
#include "operations.h"

/**
 * ADD
 * rd = r1 + r2 + k
 */
inline void op_add(Instruction* i)
{
	registers[i->rd] = registers[i->r1] + registers[i->r2] + i->k;
}

/**
 * SUB
 * rd = r1 - r2 - k
 */
inline void op_sub(Instruction* i)
{
	registers[i->rd] = registers[i->r1] - registers[i->r2] - i->k;
}

inline void op_div(Instruction* i)
{
	registers[i->rd] = registers[i->r1] / registers[i->r2];
}

inline void op_mul(Instruction* i)
{

}

/********************************
 *	0x20
 ********************************/

inline void op_lw(Instruction* i)
{
	word* src = (word*)(memory + registers[i->r1] + i->k);
	word* dest = registers + i->rd;
	memcpy(dest, src, sizeof(word));
}

inline void op_lb(Instruction* i)
{
	registers[i->rd] = memory[i->k];
}

inline void op_sw(Instruction* i)
{
	word* src = registers + i->r1;
	word* dest = (word*)(memory + registers[i->rd] + i->k);
	memcpy(dest, src, sizeof(word));
}

inline void op_sh(Instruction* i)
{
	memory[registers[i->rd] + i->k + 0] = registers[i->r1] & 0x00FF;
	memory[registers[i->rd] + i->k + 1] = registers[i->r1] & 0xFF00;
}

inline void op_sb(Instruction* i)
{
	memory[registers[i->rd] + i->k] = registers[i->r1] & 0xFF;
}

/********************************
 *	0x30
 ********************************/

inline void op_j(Instruction* i)
{
	pcounter = i->k;
}

inline void op_jr(Instruction* i)
{
	pcounter = registers[i->r1];
}

inline void op_jal(Instruction* i)
{
	registers[R_RA] = pcounter;
	pcounter = i->k;
}

/********************************
 *	0xF0
 ********************************/

inline void op_prti(Instruction* i)
{
	print_reg(i->r1);
}

// MakeOps

void mop_add(word address, byte rd, byte r1, byte r2, word constant)
{
	mem_put_instr(address, OP_ADD, rd, r1, r2, constant);
}

void mop_sw(word address, byte rsrc, byte rdest, word offset)
{
	mem_put_instr(address, OP_SW, rdest, rsrc, 0, offset);
}

void mop_lw(word address, byte rsrc, byte rdest, word offset)
{
	mem_put_instr(address, OP_LW, rdest, rsrc, 0, offset);
}