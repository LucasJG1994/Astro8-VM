#ifndef __tokens__h
#define __tokens__h

enum token_type {
	NOP,
	AIN,
	BIN,
	CIN,
	LDIA,
	LDIB,
	RDEXP,
	WREXP,
	STA,
	STC,
	ADD,
	SUB,
	MULT,
	DIV,
	JMP,
	JMPZ,
	JMPC,
	JREG,
	LDAIN,
	STAOUT,
	LDLGE,
	STLGE,
	LDW,
	SWP ,
	SWPC,
	HLT,
	SET,

	ADDR_HEX,
	ADDR_DEC,

	T_EOF
};

#endif