#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
 * INSTRUCTION SET
 *
 * Aritmetic & Math
 * 
 * 00	NAP		Do nothing (nap)
 *
 * 01	ADD 	Add
 * 02	SUB 	Subtract
 * 03	MUL		Multiply (Int)
 * 04	MULD 	Multiply DWORD (2 Regs)
 * 04	DIV		Divide
 * 06	POW		Power
 * 07	AND 	And
 * 08	OR 		Or
 * 09	NOT 	Not
 * 0A	XOR		Exclusive Or
 * 0B	ABS 	Absolute value
 * 0C	ADDF	Add 		(float)
 * 0D	SUBF	Subtract 	(float)
 * 0E	MULF 	Multiply 	(float)
 * 0F	DIVF	Divide 		(float)
 * 10	POWF 	Power 		(float)
 * 11	ABSF	Absolute  	(float)
 * 12	EXP 	Exponential (float)
 * 13	SIN 	Sine 		(float)
 * 14	COS 	Cosine 		(float)
 * 15	TAN 	Tangent 	(float)
 * 16	ASIN	Arcsin 		(float)
 * 17	ACOS	Arccos 		(float)
 * 18	ATAN	Arctan 		(float)
 * 
 * Memory Manipulation
 *
 * 20	LW		Load Word
 * 21	LH		Load Halfword
 * 22	LB		Load Byte
 * 23	SW		Store Word
 * 24	SH 		Store Half Word
 * 25   SB  	Store Byte
 *
 * Jump & Branch
 *
 * 30	J		Jump
 * 31	JR		Jump Register
 * 32	JAL		Jump and Link
 * 33	JZ		Jump on Zero
 * 34	JNZ		Jump on Not Zero
 * 35	JEQ		Jump on Equal
 * 36	JNQ		Jump on Not Equal
 * 37	JGT 	Jump on Greater Than
 * 38	JLT 	Jump on Less Than
 *
 * Stack Manipulation
 *
 * 40	PUSH 	Push Word
 * 41	PUSHH 	Push Halfword
 * 42	PUSHB 	Push Byte
 * 43	POP 	Pop Word
 * 44	POPH	Pop Halfword
 * 45	POPB 	Pop Byte
 *
 * Special
 *
 * F0	PRTS	Print Register
 * F1	PRTI	Print Register (as Integer)
 * FD	ECHO	Printf
 * FE	CALL	Syscall
 * FF	EXIT	Exit
 *
 */

inline void op_add(Instruction* i);
inline void op_sub(Instruction* i);

inline void op_exp(Instruction* i);
inline void op_sin(Instruction* i);
inline void op_cos(Instruction* i);
inline void op_tan(Instruction* i);

inline void op_lw(Instruction* i);
inline void op_lh(Instruction* i);
inline void op_lb(Instruction* i);
inline void op_sw(Instruction* i);
inline void op_sh(Instruction* i);
inline void op_sb(Instruction* i);

inline void op_j(Instruction* i);
inline void op_jr(Instruction* i);
inline void op_jal(Instruction* i);
inline void op_jz(Instruction* i);
inline void op_jnz(Instruction* i);
inline void op_jeq(Instruction* i);
inline void op_jnq(Instruction* i);

inline void op_push(Instruction* i);
inline void op_pop(Instruction* i);

inline void op_prti(Instruction* i);

void mop_add(word, byte, byte, byte, word);
void mop_sub(word, byte, byte, byte, word);

void mop_sw(word, byte, byte, word);
void mop_lw(word, byte, byte, word);

void mop_j(word, word);
void mop_jz(word, byte, word);
void mop_jnz(word, byte, word);
void mop_jeq(word, byte, byte, word);

void mop_prti(word, byte);
void mop_exit(word);

#endif