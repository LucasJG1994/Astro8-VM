#ifndef __file__h
#define __file__h

struct file {
	const char* bytes;
	size_t		size;
};

file* file_load(const char* file_name);
void  file_close(file* self);

#endif