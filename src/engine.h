#ifndef __engine__h
#define __engine__h

enum engine_state{
	ENG_OK, ENG_QUIT, ENG_ERR
};

#ifndef DEBUG
void		 engine_init(const char* file_name);
#else
void		 engine_init(); //Run engine without requesting ROM.
#endif

engine_state engine_update();
void		 engine_close();

#endif