#include "engine.h"
#include "graphics.h"
#include "cpu.h"
#include "file.h"
#include "scanner.h"
#include "parser.h"
#include <SDL.h>
#include <iostream>

extern unsigned int ExpansionPort;

static SDL_Event e;

cpu_state cs;

#ifndef DEBUG
void engine_init(const char* file_name) {
	file* f = file_load(file_name);

	if (f == nullptr) {
		std::cout << "Unable to load file...\n";
		exit(0);
	}

	std::cout << "Loaded file...\n";

	scan_init(f);
	parser_init();

	std::cout << "Init scanner and parser...\n";

	ROM* rom = parser_start();

	std::cout << "Created Rom...\n";
#else
void engine_init(){
	
#endif

	graphics_init();

	std::cout << "Init graphics...\n";

	cs = CPU_OK;

#ifndef DEBUG
	cpu_init(rom);
	rom_close(rom);
	file_close(f);
#else
	cpu_init();
#endif
	
	graphics_clear({0, 0, 0});
}

engine_state engine_update() {

	if(SDL_PollEvent(&e) != 0){
		switch (e.type) {
			case SDL_QUIT: { return ENG_QUIT; }
			case SDL_KEYDOWN:
				if (cs == CPU_HLT) {
					switch (e.key.keysym.sym) {
						case SDLK_LEFT:  cpu_prev(); break;
						case SDLK_RIGHT: cpu_next(); break;
					}
					cpu_display();
				}else ExpansionPort = e.key.keysym.sym; break;
			default: ExpansionPort = 168; break;
		}
	}

	if(cs == CPU_OK) cpu_update();
	graphics_update();
	return ENG_OK;
}

void engine_close() {
	graphics_close();
	
	std::cout << "Engine closed successfully\n";
}