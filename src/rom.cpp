#include "rom.h"

ROM* rom_init() {
	ROM* self = new ROM;

	if(self == nullptr) return nullptr;

	return self;
}

void rom_close(ROM* self) {
	if(self == nullptr) return;
	delete self;
}

void ROM::store(uint16_t data) {
	if (DP < size) {
		bytes[DP++] = data;
	}
}