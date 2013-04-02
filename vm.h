#ifndef VM_H
#define VM_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define ENTRY_POINT 1024
#define MEM_SIZE	2048
#define REG_COUNT	256

typedef unsigned char byte;
typedef unsigned int word;
typedef unsigned short hword;
typedef unsigned long dword;

typedef struct
{
	byte op;
	byte rd;
	byte r1;
	byte r2;
	word k;
} Instruction;

extern int cycles;
extern int pcounter;
extern int* stackptr;
extern byte* memory;
extern word* registers;

void vm_init();
void vm_load(char*);
void vm_exit();
void vm_run();
void vm_exec();

inline Instruction* mem_load_instr(int);
inline int mem_load_int(int);
inline Instruction* mem_put_instr(word address, byte op, byte rd, byte r1, byte r2, word k);

void print_instr(Instruction*);
void print_reg(byte);

/* Registers */
#define R_ZERO		0
#define R_K0		1
#define R_K1		2
#define R_SP		200
#define R_FP
#define R_GP
#define R_RA		6
#define R_HI
#define R_LO

/* Opcodes */
#define OP_NAP	 	0x00
#define OP_ADD	 	0x01
#define OP_SUB	 	0x02
#define OP_MUL		0x03
#define OP_DIV		0x04

#define OP_EXP		0x12
#define OP_SIN		0x13
#define OP_COS		0x14
#define OP_TAN		0x15

#define OP_LW 		0x20
#define OP_LH		0x21
#define OP_LB		0x22
#define OP_SW		0x23
#define OP_SH		0x24
#define OP_SB 		0x25

#define OP_J		0x30
#define OP_JR		0x31
#define OP_JAL		0x32
#define OP_JZ 		0x33
#define OP_JNZ		0x34
#define OP_JEQ		0x35
#define OP_JNQ		0x36
#define OP_JGT		0x37
#define OP_JLT		0x38

#define OP_PUSH		0x40
#define OP_POP		0x43

#define OP_PRTS 	0xF0
#define OP_PRTI		0xF1
#define OP_EXIT		0xFF
/*
const char* instruction_name(int opcode)
{
	switch(opcode)
	{
		case OP_NAP: return "NAP";
		case OP_ADD: return "ADD";
		case OP_SUB: return "SUB";
		case OP_DIV: return "DIV";
		case OP_MUL: return "MUL";

		case OP_LW: return "LW";
		case OP_SW: return "SW";
	}
	return "NON"; // Unrecognized opcode
}
*/
#endif