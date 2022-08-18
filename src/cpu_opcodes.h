#ifndef __cpu_opcodes__h
#define __cpu_opcodes__h

enum cpu_opcodes {
	HLT,

	AIN,
	AIN_L,
	AIN_B,
	AIN_L_B,
	AIN_C,
	AIN_L_C,
	BIN,
	BIN_L,
	CIN,
	CIN_L,

	LDIA,
	LDIB,
	LDIC,

	INA,
	INB,
	INC,

	RDEXP,
	WREXP,

	STA,
	STA_L,
	STA_B,
	STA_L_B,
	STA_C,
	STA_L_C,
	STB,
	STB_L,
	STC,
	STC_L,

	PHA,
	PLA,
	PHF,
	PLF,

	ADD,
	SUB,
	MULT,
	DIV,

	AND,
	OR,
	NOT,
	XOR,

	JMP,
	JMPZ,
	JMPC,
	JCLR,
	JREG,

	CALL,
	RET,

	SWP,
	SWPC,

	NOP
};

#endif