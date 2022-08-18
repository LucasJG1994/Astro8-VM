#ifndef __rom__h
#define __rom__h

#include <stdint.h>

struct ROM {
	unsigned int bytes[0xFFFF] = { 0 };
	unsigned int IP   = 0;
	size_t size = 0xFFFF;

	void store(uint16_t instr);
	void store(uint16_t instr, uint16_t data);
	unsigned int get_IP();
	void insert(uint16_t index, uint16_t data);
};

ROM* rom_init();
void rom_close(ROM* self);

#endif