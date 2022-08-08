#ifndef __cpu_opcodes__h
#define __cpu_opcodes__h

enum cpu_opcodes {
	NOP = 0,
	AIN = 1,
	BIN = 2,
	CIN = 3,
	LDIA = 4,
	LDIB = 5,
	RDEXP = 6,
	WREXP = 7,
	STA = 8,
	STC = 9,
	ADD = 10,
	SUB = 11,
	MULT = 12,
	DIV = 13,
	JMP = 14,
	JMPZ = 15,
	JMPC = 16,
	JREG = 17,
	LDAIN = 18,
	STAOUT = 19,
	LDLGE = 20,
	STLGE = 21,
	LDW = 22,
	SWP = 23,
	SWPC = 24,
	HLT  = 25
};

#endif