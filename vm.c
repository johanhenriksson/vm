#include "vm.h"

bool running;

int cycles;
int pcounter;
int exitval;
int* stackptr;

byte* memory;
word* registers;

int main(int argc, char* argv[]) 
{
	char* image = "image";
	if (argc > 1)
		image = argv[1];

	vm_init();

	int in = 532;
	Instruction* i;
	printf("Input: %d\n", in);
	registers[1] = 4; // destination address register

	mop_add(8,  1, R_ZERO, R_ZERO, 4);  // r1 = 4
	mop_add(16, 2, R_ZERO, R_ZERO, in); // r2 = in

	mop_sw(24, // Instruction address
	   	   2,  // Source Word Register = r2
		   1,  // Destination Address Register = r1
		   0); // Offset = 0

	mop_lw(32, // Instruction address
		   1,  // Source address register = r1
		   7,  // Destination register = r7
		   0); // Offset
	
	mop_j(64, 8);

	vm_run(8);

	print_reg(2);
	print_reg(7); // print destination r7

	vm_exit();

/*
	vm_init();
	vm_load(image);
	vm_run(ENTRY_POINT);
*/	
	return exitval;
}

void vm_init()
{
	printf("\nVM\nInitializing...\n");
	pcounter = ENTRY_POINT;
	exitval = 0;
	cycles = 0;
	running = true;

	printf("MEMORY SIZE: %d\nREGISTER COUNT: %d\n", MEM_SIZE, REG_COUNT);

	// Allocate memory
	memory 		= (byte*)calloc(MEM_SIZE,  1);
	registers 	= (word*)calloc(REG_COUNT, 4);

	stackptr 	= (int*)(registers + R_SP);
	*stackptr 	= MEM_SIZE;
}

/**
 * Loads an image into virtual memory
 * Sets instruction pointer to ENTRY_POINT
 */
void vm_load(char* image)
{
	printf("Loading image '%s'...\n", image);

	FILE *fp = fopen(image, "rb");
	if (fp == NULL) 
	{
	    printf("Error reading image '%s'\n", image);
	    vm_exit(-1);
	    return;
	}

	fseek(fp, 0L, SEEK_END);
	dword imgsize = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	printf("IMAGE SIZE: %lu\n", imgsize);
	if (imgsize > (MEM_SIZE - ENTRY_POINT))
	{
		printf("Error: Image size does not fit within allocated memory\n");
		fclose(fp);
		vm_exit(-1);
		return;
	}

	size_t blocks_read = fread(memory + ENTRY_POINT, imgsize, 1, fp);
	if (blocks_read != 1) 
	{
		printf("Error: Could not read image into memory\n");
		fclose(fp);
		vm_exit(-1);
		return;
	}

	pcounter = ENTRY_POINT; // Set program counter to image entry point
	fclose(fp);
}

void vm_run(int at)
{
	pcounter = at;
	while(running)
	{
		vm_exec();
	}
}

void vm_exit(int val)
{
	if (!running) return;

	free(memory);
	free(registers);

	running = false;
	exitval = val;

	printf("Exited with value %d\n\n", val);
}

/**
 * Runs the instruction at the program counters position in memory.
 */
void vm_exec()
{
	cycles++;
	Instruction* op = mem_load_instr(pcounter);
	print_instr(op);

	switch(op->op)
	{
		case OP_NAP: break;

		case OP_ADD:
			op_add(op);
			break;

		case OP_SUB:
			op_sub(op);
			break;

		case OP_LW:
			op_lw(op);
			break;

		case OP_SW:
			op_sw(op);
			break;

		case OP_SB:
			op_sb(op);
			break;

		case OP_J:
			op_j(op);
			return; // Jump

		case OP_PRTI:
			op_prti(op);
			break;

		case OP_EXIT:
			vm_exit(op->k);
			return;

		/* Unsupported operation */
		default:
			printf("Error: Invalid operation at %d\n", pcounter);
			print_instr(op);
			vm_exit(-1);
			return;
	}

	pcounter = pcounter + 8;
}

/*
 *	Memory Access
 */

inline Instruction* mem_load_instr(int address)
{
	Instruction* ptr = (Instruction*)(memory + address);
	return ptr;
}

/**
 * Sets memory at address to a a given instruction
 * @returns Instruction* Instruction pointer
 */
inline Instruction* mem_put_instr(word address, byte op, byte rd, byte r1, byte r2, word k)
{
	Instruction* ip = (Instruction*)(memory + address);
	ip->op = op;
	ip->rd = rd;
	ip->r1 = r1;
	ip->r2 = r2;
	ip->k = k;
	return ip;
}

inline int mem_load_int(int offset)
{
	int* ptr = (int*)(memory + offset);
	return *ptr;
}

void print_instr(Instruction* instr)
{
	switch(instr->op)
	{
		case OP_NAP:
			printf("NAP\n");
			return;

		case OP_ADD: 
			printf("ADD   R%d = R%d(%d) + R%d(%d) + %d\n", 
				   instr->rd, 
				   instr->r1, registers[instr->r1], 
				   instr->r2, registers[instr->r2], 
				   instr->k);
			return;

		case OP_LW:
			printf("LW    R%d = M[0x%x](%d)\n", 
				   instr->rd,
				   instr->r1 + instr->k, mem_load_int(registers[instr->r1] + instr->k));
			return;

		case OP_SW:
			printf("SW    M[0x%x] = R%d(%d)\n",
				   instr->rd + instr->k,
				   instr->r1, registers[instr->r1]);
			return;

		case OP_J:
			printf("J     0x%x\n", instr->k);
			return;

		case OP_EXIT:
			printf("EXIT  %d\n", instr->k);
			return;
	}
	printf("0x%x", instr->op);
	printf(" RD=%d R1=%d R2=%d K=%d\n", instr->rd, instr->r1, instr->r2, instr->k);
}

void print_reg(byte reg)
{
	printf("R[%d]=%d\n", reg, registers[reg]);
}
