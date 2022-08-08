#include "file.h"
#include <stdio.h>

#define MAX_ROM_SIZE 32764

file* file_load(const char* file_name) {
	FILE* fp;
	long long int length;
	if(fopen_s(&fp, file_name, "r") != 0) return nullptr;

	fseek(fp, 0L, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	if(length >= MAX_ROM_SIZE) {
		fclose(fp);
		return nullptr;
	}
	
	char* byte_array = new char[length];

	fread(byte_array, sizeof(char), length, fp);
	fclose(fp);

	file* self = new file;
	self->bytes = byte_array;
	self->size = length;
	return self;
}

void file_close(file* self) {
	if(self == nullptr) return;
	if (self->bytes == nullptr) {
		delete self;
		return;
	}

	delete[] self->bytes;
	delete self;
}
