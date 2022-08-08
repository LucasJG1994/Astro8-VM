#ifndef __cpu__h
#define __cpu__h

#include "rom.h"

enum cpu_state {
	CPU_OK, CPU_HLT, CPU_ERR
};
#ifndef DEBUG
void	  cpu_init(ROM* rom);
#else
void	  cpu_init(); //To run emulator with requesting for a ROM.
#endif

void	  cpu_update();
void	  cpu_prev();
void	  cpu_next();
void	  cpu_display();

#endif