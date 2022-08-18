#ifndef __rom__h
#define __rom__h

#include <stdint.h>

struct ROM {
	uint16_t bytes[16382] = { 0 };
	unsigned int IP   = 0;
	size_t size = 16382;

	void store(uint16_t instr);
	void store(uint16_t instr, uint16_t data);
};

ROM* rom_init();
void rom_close(ROM* self);

#endif