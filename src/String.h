#ifndef __String__h
#define __String__h

struct String {
	char*  bytes;
	size_t size;

	void	lower();
	int		to_int();
	int		to_hex();

	bool operator==(String* right);
	bool operator==(const char* s);
};

String* string_init(const char* copy, size_t length);
void	string_close(String* self);

#endif