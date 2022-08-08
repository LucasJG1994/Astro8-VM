#include "engine.h"

#ifndef DEBUG
int main(int argc, char** argv) {

	if(argc == 2){
		engine_init(argv[1]);

		while (engine_update() == ENG_OK);

		engine_close();
	}
#else
int main(){
	engine_init();

	while(engine_update() == ENG_OK);

	engine_close();
#endif
}