#include "debug.h"
#include <stdio.h>

static FILE* fp;

void debug_init() {
	if(fopen_s(&fp, "Assembler_log.txt", "w") != 0) fp == nullptr;
}

void debug_log(std::string msg) {
	if(fp == nullptr) return;
	msg += "\n";
	fwrite(msg.c_str(), sizeof(char), msg.size(), fp);
}

void debug_close() {
	if(fp == nullptr) return;
	fclose(fp);
}