#include "engine.h"
#include "graphics.h"
#include "cpu.h"
#include "file.h"
#include "scanner.h"
#include "parser.h"
#include "debug.h"
#include <SDL.h>
#include <queue>

extern unsigned int ExpansionPort;

static SDL_Event e;

cpu_state cs;

#ifndef DEBUG
void engine_init(const char* file_name) {
	debug_init();
	file* f = file_load(file_name);

	if (f == nullptr) {
		debug_log("Unable to load file...");
		exit(0);
	}

	debug_log("Loaded file...");

	std::queue<token>* token_stream;
	ROM* rom;
	scan_init(f);
	try{ 
		token_stream = scan_tokenize();

		scan_log();

		debug_log("Scanner Done...");

		parser_init(token_stream);
		rom = parser_start();

		debug_log("Parser Done...");
		debug_log("Created Rom...");
	}
	catch(int c){
		token_stream = nullptr;
		rom = nullptr;
	}

	
#else
void engine_init(){
	
#endif

	graphics_init();

	debug_log("Init graphics...");

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
	
	debug_log("Engine closed successfully...");
	debug_close();
}