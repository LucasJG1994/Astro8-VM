#ifndef __scanner__h
#define __scanner__h

#include "String.h"
#include "file.h"

enum scanner_state {
	SCAN_OK, SCAN_ERR
};

void		  scan_init(file* f);
scanner_state scan_advance();

extern String*		S_LEXEME;
extern unsigned int S_LINE;
extern unsigned int S_TYPE;

#endif