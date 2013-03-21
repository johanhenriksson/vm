#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
 * INSTRUCTION SET
 *
 * Aritmetic & Math
 * 
 * 00	NAP		Do nothing
 * 01	ADD 	Add
 * 02	SUB 	Subtract
 * 03	MUL		Multiply
 * 04	DIV		Divide
 * 05	REM		Remainder	
 * 06	POW		Power
 * 07	ADDF	Add floats
 * 08	SUBF	Subtract floats
 * 09	MULF 	Multiply floats
 * 09	DIVF	Divide floats
 * 0A	POWF 	Power (float)
 * 0B	EXP 	Exponential (float)
 * 0C	SIN 	Sine (float)
 * 0D	COS 	Cosine (float)
 * 0E	TAN 	Tangent (float)
 * 0F	ABS 	Absolute value
 * 10	ABSF	Absolute value (float)
 * 11	AND 	And
 * 12	OR 		Or
 * 13	NOT 	Not
 * 14	XOR		Exclusive Or
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
 * 36	JGT 	Jump on Greater Than
 * 37	JLT 	Jump on Less Than
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

inline void op_lw(Instruction* i);
inline void op_lh(Instruction* i);
inline void op_lb(Instruction* i);
inline void op_sw(Instruction* i);
inline void op_sh(Instruction* i);
inline void op_sb(Instruction* i);

inline void op_j(Instruction* i);
inline void op_jr(Instruction* i);
inline void op_jal(Instruction* i);

inline void op_prti(Instruction* i);

void mop_add(word, byte, byte, byte, word);
void mop_sw(word, byte, byte, word);
void mop_lw(word, byte, byte, word);

#endif