#include "scanner.h"
#include "tokens.h"
#include <iostream>

struct scanner {
	const char*  cur;
	const char*  start;
	const char*  offset;
	size_t		 size;
	unsigned int line;
};

static scanner scan;

//Shared Global Variables
String*		 S_LEXEME = nullptr;
unsigned int S_LINE;
unsigned int S_TYPE;

void scan_init(file* f) {
	scan.cur    = f->bytes;
	scan.start  = f->bytes;
	scan.offset = f->bytes;
	scan.size   = f->size;
	scan.line   = 1;
}

static bool scan_end() {
	return ((scan.cur - scan.offset) >= (scan.size - 1)) || *scan.cur == 0;
}

static void scan_adv() {
	scan.cur++;
}

static char scan_peek() {
	return scan.cur[1];
}

static bool scan_match(char c) {
	return *scan.cur == c;
}

static void scan_consume(char c) {
	if(scan_match(c)) scan_adv();
}

static bool is_digit() {
	return *scan.cur >= '0' && *scan.cur <= '9';
}

static bool is_alpha() {
	return (*scan.cur >= 'a' && *scan.cur <= 'z') || (*scan.cur >= 'A' && *scan.cur <= 'Z');
}

static bool is_hex() {
	return (*scan.cur >= '0' && *scan.cur <= '9') || (*scan.cur >= 'a' && *scan.cur <= 'f') ||(*scan.cur >= 'A' && *scan.cur <= 'F');
}

static void make_token(token_type type) {
	S_LINE = scan.line;
	S_TYPE = type;
}

scanner_state scan_advance() {
	while (!scan_end()) {
		std::cout << "PASS...\n";
		switch (*scan.cur) {
			case '0': {
				scan_adv();
				if (scan_match('x') || scan_match('X')) {
					scan_adv();
					scan.start = scan.cur;
					while (is_hex()) {
						scan_adv();
					}

					string_close(S_LEXEME);
					S_LEXEME = string_init(scan.start, (scan.cur - scan.start));
					if (S_LEXEME == nullptr) {
						return SCAN_ERR;
					}

					make_token(ADDR_HEX);
					return SCAN_OK;
				}
				else if (scan_match('d') || scan_match('D')) {
					scan_adv();
					scan.start = scan.cur;
					while (is_digit()) {
						scan_adv();
					}

					string_close(S_LEXEME);
					S_LEXEME = string_init(scan.start, (scan.cur - scan.start));
					if (S_LEXEME == nullptr) {
						return SCAN_ERR;
					}

					make_token(ADDR_DEC);
					return SCAN_OK;
				}
				return SCAN_ERR;
			}
			case ';':
				while(!scan_match('\n')) scan_adv();
				scan.line++;
				break;
			case ' ': break;
			case '\t': break;
			case '\n': scan.line++; break;
			default:
				scan.start = scan.cur;
				while (is_alpha()) {
					scan_adv();
				}

				string_close(S_LEXEME);
				S_LEXEME = string_init(scan.start, (scan.cur - scan.start));
				if (S_LEXEME == nullptr) {
					return SCAN_ERR;
				}

				S_LEXEME->lower();

				if		(*S_LEXEME == "nop")	{ make_token(NOP);    return SCAN_OK; }
				else if (*S_LEXEME == "ain")	{ make_token(AIN);    return SCAN_OK; }
				else if (*S_LEXEME == "bin")	{ make_token(BIN);    return SCAN_OK; }
				else if (*S_LEXEME == "cin")	{ make_token(CIN);    return SCAN_OK; }
				else if (*S_LEXEME == "ldia")	{ make_token(LDIA);   return SCAN_OK; }
				else if (*S_LEXEME == "ldib")	{ make_token(LDIB);   return SCAN_OK; }
				else if (*S_LEXEME == "rdexp")	{ make_token(RDEXP);  return SCAN_OK; }
				else if (*S_LEXEME == "wrexp")	{ make_token(WREXP);  return SCAN_OK; }
				else if (*S_LEXEME == "sta")	{ make_token(STA);	  return SCAN_OK; }
				else if (*S_LEXEME == "stc")	{ make_token(STC);    return SCAN_OK; }
				else if (*S_LEXEME == "add")	{ make_token(ADD);    return SCAN_OK; }
				else if (*S_LEXEME == "sub")	{ make_token(SUB);    return SCAN_OK; }
				else if (*S_LEXEME == "mult")	{ make_token(MULT);   return SCAN_OK; }
				else if (*S_LEXEME == "div")	{ make_token(DIV);    return SCAN_OK; }
				else if (*S_LEXEME == "jmp")	{ make_token(JMP);    return SCAN_OK; }
				else if (*S_LEXEME == "jmpz")	{ make_token(JMPZ);   return SCAN_OK; }
				else if (*S_LEXEME == "jmpc")	{ make_token(JMPC);   return SCAN_OK; }
				else if (*S_LEXEME == "jreg")	{ make_token(JREG);   return SCAN_OK; }
				else if (*S_LEXEME == "ldain")	{ make_token(LDAIN);  return SCAN_OK; }
				else if (*S_LEXEME == "staout")	{ make_token(STAOUT); return SCAN_OK; }
				else if (*S_LEXEME == "ldlge")	{ make_token(LDLGE);  return SCAN_OK; }
				else if (*S_LEXEME == "stlge")	{ make_token(STLGE);  return SCAN_OK; }
				else if (*S_LEXEME == "ldw")	{ make_token(LDW);    return SCAN_OK; }
				else if (*S_LEXEME == "swp")	{ make_token(SWP);    return SCAN_OK; }
				else if (*S_LEXEME == "swpc")	{ make_token(SWPC);   return SCAN_OK; }
				else if (*S_LEXEME == "hlt")	{ make_token(HLT);    return SCAN_OK; }

				return SCAN_ERR;
		}
		scan_adv();
	}
	std::cout << "END\n";
	string_close(S_LEXEME);
	S_LEXEME = nullptr;
	S_LINE   = 0;
	S_TYPE   = T_EOF;
}