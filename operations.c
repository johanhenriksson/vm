#include "vm.h"
#include "operations.h"

/********************************
 *	0x00 	Math
 ********************************/

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

/**
 * EXP
 * rd = e^r1
 */
inline void op_exp(Instruction* i)
{
	float* power = (float*)(registers + i->r1);
	float* dest = (float*)(registers + i->rd);

	*dest = exp(*power);
}

inline void op_sin(Instruction* i)
{
	float* angle = (float*)(registers + i->r1);
	float* dest = (float*)(registers + i->rd);

	*dest = sinf(*angle);
}

inline void op_cos(Instruction* i)
{
	float* angle = (float*)(registers + i->r1);
	float* dest = (float*)(registers + i->rd);

	*dest = cosf(*angle);
}

inline void op_tan(Instruction* i)
{
	float* angle = (float*)(registers + i->r1);
	float* dest = (float*)(registers + i->rd);

	*dest = tanf(*angle);
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

inline void op_jz(Instruction* i)
{
	if (registers[i->r1] == 0)
		pcounter = i->k;
	else
		pcounter += 8; // Jump to next
}

inline void op_jnz(Instruction* i)
{
	if (registers[i->r1] != 0)
		pcounter = i->k;
	else
		pcounter += 8; // Jump to next
}

inline void op_jeq(Instruction* i)
{
	if (registers[i->r1] == registers[i->r2])
		pcounter = i->k;
	else
		pcounter += 8; // Jump to next
}

inline void op_jnq(Instruction* i)
{
	if (registers[i->r1] != registers[i->r2])
		pcounter = i->k;
	else
		pcounter += 8; // Jump to next
}

/********************************
 *	0x40
 ********************************/

inline void op_push(Instruction* i)
{
	word* src = (word*)(registers + i->r1);
	memcpy(stackptr, src, sizeof(word));
	stackptr -= sizeof(word);
}

inline void op_pop(Instruction* i)
{
	stackptr += sizeof(word);
	word* dest = (word*)(registers + i->rd);
	memcpy(dest, stackptr, sizeof(word));
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

void mop_sub(word address, byte rd, byte r1, byte r2, word constant)
{
	mem_put_instr(address, OP_SUB, rd, r1, r2, constant);
}

void mop_sw(word address, byte rsrc, byte rdest, word offset)
{
	mem_put_instr(address, OP_SW, rdest, rsrc, 0, offset);
}

void mop_lw(word address, byte rsrc, byte rdest, word offset)
{
	mem_put_instr(address, OP_LW, rdest, rsrc, 0, offset);
}

/* Jumps */

void mop_j(word address, word location)
{
	mem_put_instr(address, OP_J, 0, 0, 0, location);
}

void mop_jz(word address, byte reg, word location)
{
	mem_put_instr(address, OP_JZ, 0, reg, 0, location);
}

void mop_jnz(word address, byte reg, word location)
{
	mem_put_instr(address, OP_JNZ, 0, reg, 0, location);
}

void mop_jeq(word address, byte r1, byte r2, word location)
{
	mem_put_instr(address, OP_JEQ, 0, r1, r2, location);
}

/* Stack */

void mop_push(word address, byte rsrc)
{
	mem_put_instr(address, OP_PUSH, 0, rsrc, 0, 0);
}

void mop_pop(word address, byte rdest)
{
	mem_put_instr(address, OP_POP, rdest, 0, 0, 0);
}

/* Misc */
void mop_prti(word address, byte reg)
{
	mem_put_instr(address, OP_PRTI, 0, reg, 0, 0);
}

void mop_exit(word address)
{
	mem_put_instr(address, OP_EXIT, 0, 0, 0, 0);
}