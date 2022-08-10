#ifndef __rom__h
#define __rom__h

#include <stdint.h>

struct ROM {
	uint16_t	 bytes[16382] = { 0 };
	unsigned int DP   = 0; //Data Pointer
	size_t		 size = 16382;

	void store(uint16_t data);
	void store(uint16_t addr, uint16_t data);
};

ROM* rom_init();
void rom_close(ROM* self);

#endif