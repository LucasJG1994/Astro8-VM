#include "scanner.h"
#include <map>
#include <iostream>

struct scanner {
	const char*  cur;
	const char*  start;
	const char*  offset;
	size_t		 size;
	int line;
};

static scanner scan;
static std::map<std::string, int> keywords = {
	{"nop", NOP},

	{"ain", AIN},
	{"ain.l", AIN_L},
	{"bin", BIN},
	{"bin.l", BIN_L},
	{"cin", CIN},
	{"cin.l", CIN_L},

	{"ldia", LDIA},
	{"ldib", LDIB},
	{"ldic", LDIC},

	{"inc", INA},
	{"inb", INB},
	{"inc", INC},

	{"rdexp", RDEXP},
	{"wrexp", WREXP},

	{"sta", STA},
	{"sta.l", STA_L},
	{"stb", STB},
	{"stb.l", STB_L},
	{"stc", STC},
	{"stc.l", STC_L},

	{"pha", PHA},
	{"pla", PLA},
	{"phf", PHF},
	{"plf", PLF},

	{"add", ADD},
	{"sub", SUB},
	{"mult", MULT},
	{"div", DIV},

	{"jmp", JMP},
	{"jmpz", JMPZ},
	{"jmpc", JMPC},
	{"jclr", JCLR},
	{"jreg", JREG},

	{"call", CALL},
	{"ret", RET},

	{"swp", SWP},
	{"swpc", SWPC},

	{"hlt", HLT},

	{"b", REG_B},
	{"c", REG_C}
};

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

static void scan_error(std::queue<token>* List) {
	while(List->empty() == 0) List->pop();
	delete List;

	std::cout << "Scan Error... " << std::to_string(scan.line) << std::endl;
	throw 0;
}

static std::string* scan_get_lex() {
	int length = scan.cur - scan.start;
	if(length == 0) return nullptr;

	std::string* ret = new std::string();
	if(ret == nullptr) return nullptr;

	ret->insert(0, scan.start, length);
	return ret;
}

static bool is_digit() {
	return *scan.cur >= '0' && *scan.cur <= '9';
}

static bool is_alpha() {
	return (*scan.cur >= 'a' && *scan.cur <= 'z') || (*scan.cur >= 'A' && *scan.cur <= 'Z') || *scan.cur == '.';
}

static bool is_hex() {
	return (*scan.cur >= '0' && *scan.cur <= '9') || (*scan.cur >= 'a' && *scan.cur <= 'f') ||(*scan.cur >= 'A' && *scan.cur <= 'F');
}

static int to_int(std::string s, int base){
	char* pEnd;
	int ret = std::strtol(s.c_str(), &pEnd, base);
	return ret;
}

static std::string to_lower(std::string s) {
	std::string ret = "";
	for (char c : s) {
		if(c >= 'A' && c <= 'Z') c += 32;
		ret += c;
	}
	return ret;
}

static int scan_get_hex();
static int scan_get_dec();

static void scan_number(std::queue<token>* List);
static void scan_comma(std::queue<token>* List);
static void scan_keyword(std::queue<token>* List);
static void scan_comment();
static void scan_newline();
static void scan_end_of_file(std::queue<token>* List);

std::queue<token>* scan_tokenize() {
	std::queue<token>* List = new std::queue<token>();
	while (!scan_end()) {
		switch (*scan.cur) {
			case '0': scan_number(List); break;
			case ',': scan_comma(List); break;
			case ';': scan_comment(); break;
			case ' ': scan_adv(); break;
			case '\t':scan_adv(); break;
			case '\n': scan_newline(); break;
			default: scan_keyword(List); break;
		}
	}
	scan_end_of_file(List);
	return List;
}

static int scan_get_hex() {
	scan.start = scan.cur;
	while(is_hex() && !scan_end()) scan_adv();
	
	std::string* lex = scan_get_lex();
	if(lex == nullptr) return 0;

	*lex = to_lower(*lex);

	std::string n = *lex;
	delete lex;

	return to_int(n, 16);
}

static int scan_get_dec() {
	scan.start = scan.cur;
	while(is_digit() && !scan_end()) scan_adv();

	std::string* lex = scan_get_lex();
	if(lex == nullptr) return 0;

	std::string n = *lex;
	delete lex;

	return to_int(n, 10);
}

static void scan_number(std::queue<token>* List) {
	int data;
	scan_adv();
	if (scan_match('x')) {
		scan_adv();
		data = scan_get_hex();
		List->push({"", ADDR_HEX, scan.line, data});
	}
	else if (scan_match('d')) {
		scan_adv();
		data = scan_get_dec();
		List->push({"", ADDR_DEC, scan.line, data});
	}
	else scan_error(List);
}

static void scan_comma(std::queue<token>* List) {
	scan_adv();
	List->push({",", COMMA, scan.line, 0});
}

static void scan_keyword(std::queue<token>* List) {
	scan.start = scan.cur;
	while(is_alpha() && !scan_end()) scan_adv();

	std::string* lex = scan_get_lex();
	if(lex == nullptr) { scan_adv(); return; }

	*lex = to_lower(*lex);

	if(keywords.find(*lex) == keywords.end()){ delete lex; scan_error(List); }
	List->push({*lex, keywords[*lex], scan.line, 0});
	delete lex;
}

static void scan_comment() {
	while(!scan_match('\n') && !scan_end()) scan_adv();
}

static void scan_newline() {
	scan_adv();
	scan.line++;
}

static void scan_end_of_file(std::queue<token>* List) {
	List->push({"", T_EOF, 0, 0});
}