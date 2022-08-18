#ifndef __parser__h
#define __parser__h

#include "rom.h"
#include "tokens.h"
#include <queue>

enum parser_state {
	PARSER_OK, PARSER_ERR
};

extern parser_state par_state;

void parser_init(std::queue<token>* token_stream);
ROM* parser_start();

#endif