vm
==

C virtual machine implementation

Instruction Set
(not fully implemented)

 * Aritmetic & Math
 * 
 * 00  NAP		Do nothing (nap)
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
 * 32	JAL		Jump and Link (JALR required?)
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
