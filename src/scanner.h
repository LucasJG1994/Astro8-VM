#ifndef __scanner__h
#define __scanner__h

#include "file.h"
#include "tokens.h"
#include <queue>

enum scanner_state {
	SCAN_OK, SCAN_ERR
};

void scan_init(file* f);
std::queue<token>* scan_tokenize();

#endif