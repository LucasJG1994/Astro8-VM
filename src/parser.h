#ifndef __parser__h
#define __parser__h

#include "rom.h"

enum parser_state {
	PARSER_OK, PARSER_ERR
};

extern parser_state par_state;

void parser_init();
ROM* parser_start();

#endif