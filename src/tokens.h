#ifndef __tokens__h
#define __tokens__h

#include "cpu_opcodes.h"
#include <string>

enum token_type {
	REG_B = NOP + 1,
	REG_C,
	ADDR_HEX,
	ADDR_DEC,
	COMMA,
	ASSIGN,
	LABEL,
	T_EOF
};

struct token {
	std::string lexeme;
	int type;
	int line;
	int data;

	token(){}
	token(std::string lexeme, int type, int line, int data) {
		this->lexeme = lexeme;
		this->type = type;
		this->line = line;
		this->data = data;
	}

	std::string to_string() {
		std::string ret;
		ret = "TYPE: " + std::to_string(type) + "\n";
		ret += "LEX: " + lexeme + "\n";
		ret += "LINE: " + std::to_string(line) + "\n";
		return ret;
	}
};

#endif