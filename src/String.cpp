#include "String.h"
#include <iostream>

String* string_init(const char* copy, size_t length){
	if(copy == nullptr || length == 0) return nullptr;
	String* self = new String;
	self->bytes = new char[length];

	if (self->bytes == nullptr) {
		delete self;
		return nullptr;
	}

	self->size = length;
	std::memcpy(self->bytes, copy, length);
	self->bytes[length] = 0;
	return self;
}

void string_close(String* self) {
	if (self == nullptr) return;
	if (self->bytes == nullptr) {
		delete self;
		return;
	}

	delete[] self->bytes;
	delete   self;
	self = nullptr;
}

bool String::operator==(String* right) {
	if(bytes == nullptr) return false;
	if(right == nullptr) return false;
	if(right->bytes == nullptr) return false;
	if(std::strcmp(bytes, right->bytes) == 0) return true;
	return false;
}

bool String::operator==(const char* s) {
	if(bytes == nullptr) return false;
	if(s == nullptr) return false;
	if(std::strcmp(bytes, s) == 0) return true;
	return false;
}

void String::lower() {
	if(bytes == nullptr) return;
	for (int i = 0; i < size; i++) {
		if (bytes[i] >= 'A' && bytes[i] <= 'Z') {
			bytes[i] += 32;
		}
	}
}

int String::to_int() {
	if(bytes == nullptr) return 0;
	char* pEnd;
	int ret = std::strtol(bytes, &pEnd, 10);
	return ret;
}

int String::to_hex() {
	if(bytes == nullptr) return 0;
	char* pEnd;
	int ret = std::strtol(bytes, &pEnd, 16);
	return ret;
}