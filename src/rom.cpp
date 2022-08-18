#include "rom.h"

ROM* rom_init() {
	ROM* self = new ROM;

	if(self == nullptr) return nullptr;

	return self;
}

void rom_close(ROM* self) {
	if(self == nullptr) return;
	delete self;
	self = nullptr;
}

void ROM::store(uint16_t instr) {
	if (IP >= size) return;
	bytes[IP] = instr;
	IP += 2;
}

void ROM::store(uint16_t instr, uint16_t data) {
	if(IP >= size) return;
	bytes[IP++] = instr;
	bytes[IP++] = data;
}