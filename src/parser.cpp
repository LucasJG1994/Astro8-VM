#include "parser.h"
#include "tokens.h"
#include <queue>
#include <iostream>

parser_state par_state;

static std::queue<token>* token_stream;
static token cur;
static ROM* rom = rom_init();

void parser_init(std::queue<token>* List) {
	token_stream = List;
	cur = token_stream->front();
	token_stream->pop();
}

static void parser_adv() {
	cur = token_stream->front();
	token_stream->pop();
}

static bool parser_match(int type) {
	return cur.type == type;
}

static void parser_error() {
	while (token_stream->empty() == 0) {
		token_stream->pop();
	}
	delete token_stream;
	rom_close(rom);

	std::cout << "Parser Error:\n";
	std::cout << cur.to_string();
	throw 0;
}

static void nop(ROM* rom);

static void ain(ROM* rom);
static void ain_l(ROM* rom);
static void bin(ROM* rom);
static void bin_l(ROM* rom);
static void cin(ROM* rom);
static void cin_l(ROM* rom);

static void ldia(ROM* rom);
static void ldib(ROM* rom);
static void ldic(ROM* rom);

static void ina(ROM* rom);
static void inb(ROM* rom);
static void inc(ROM* rom);

static void rdexp(ROM* rom);
static void wrexp(ROM* rom);

static void sta(ROM* rom);
static void sta_l(ROM* rom);
static void stb(ROM* rom);
static void stb_l(ROM* rom);
static void stc(ROM* rom);
static void stc_l(ROM* rom);

static void pha(ROM* rom);
static void pla(ROM* rom);
static void phf(ROM* rom);
static void plf(ROM* rom);

static void add(ROM* rom);
static void sub(ROM* rom);
static void mult(ROM* rom);
static void div(ROM* rom);

static void jmp(ROM* rom);
static void jmpz(ROM* rom);
static void jmpc(ROM* rom);
static void jclr(ROM* rom);
static void jreg(ROM* rom);

static void call(ROM* rom);
static void ret(ROM* rom);

static void swp(ROM* rom);
static void swpc(ROM* rom);

static void hlt(ROM* rom);

static int get_data() {
	if (parser_match(ADDR_HEX)) {
		int data = cur.data;
		parser_adv();
		return data;
	}
	else if (parser_match(ADDR_DEC)) { 
		int data = cur.data; 
		parser_adv();
		return data;
	}
	else parser_error();
}

ROM* parser_start() {
	while (!parser_match(T_EOF)) {
		switch(cur.type){
			case NOP: nop(rom); break;

			case AIN: ain(rom); break;
			case AIN_L: ain_l(rom); break;
			case BIN: bin(rom); break;
			case BIN_L: bin_l(rom); break;
			case CIN: cin(rom); break;
			case CIN_L: cin_l(rom); break;

			case LDIA: ldia(rom); break;
			case LDIB: ldib(rom); break;
			case LDIC: ldic(rom); break;

			case INA: ina(rom); break;
			case INB: inb(rom); break;
			case INC: inc(rom); break;

			case RDEXP: rdexp(rom); break;
			case WREXP: wrexp(rom); break;

			case STA: sta(rom); break;
			case STA_L: sta_l(rom); break;
			case STB: stb(rom); break;
			case STB_L: stb_l(rom); break;
			case STC: stc(rom); break;
			case STC_L: stc_l(rom); break;

			case PHA: pha(rom); break;
			case PLA: pla(rom); break;
			case PHF: phf(rom); break;
			case PLF: plf(rom); break;

			case ADD: add(rom); break;
			case SUB: sub(rom); break;
			case MULT: mult(rom); break;
			case DIV: div(rom); break;

			case JMP: jmp(rom); break;
			case JMPZ: jmpz(rom); break;
			case JMPC: jmpc(rom); break;
			case JCLR: jclr(rom); break;
			case JREG: jreg(rom); break;

			case CALL: call(rom); break;
			case RET: ret(rom); break;

			case SWP: swp(rom); break;
			case SWPC: swpc(rom); break;

			case HLT: hlt(rom); break;
			default: parser_error();
		}
	}
	return rom;
}

static void nop(ROM* rom) {
	parser_adv();
	rom->store(NOP);
}

static void ain(ROM* rom) {
	parser_adv();
	int data = get_data();

	if (parser_match(COMMA)) {
		parser_adv();

		if (parser_match(REG_B)) {
			parser_adv();
			rom->store(AIN_B, data);
		}
		else if (parser_match(REG_C)) {
			parser_adv();
			rom->store(AIN_C, data);
		}
		else parser_error();
		return;
	}

	rom->store(AIN, data);
}

static void ain_l(ROM* rom) {
	parser_adv();
	int data = get_data();

	if (parser_match(COMMA)) {
		parser_adv();

		if (parser_match(REG_B)) {
			parser_adv();
			rom->store(AIN_L_B, data);
		}
		else if (parser_match(REG_C)) {
			parser_adv();
			rom->store(AIN_L_C, data);
		}
		else parser_error();
		return;
	}

	rom->store(AIN_L, data);
}

static void bin(ROM* rom) {
	parser_adv();
	rom->store(BIN, get_data());
}

static void bin_l(ROM* rom) {
	parser_adv();
	rom->store(BIN_L, get_data());
}

static void cin(ROM* rom) {
	parser_adv();
	rom->store(CIN, get_data());
}

static void cin_l(ROM* rom) {
	parser_adv();
	rom->store(CIN_L, get_data());
}

static void ldia(ROM* rom) {
	parser_adv();
	rom->store(LDIA, get_data());
}

static void ldib(ROM* rom) {
	parser_adv();
	rom->store(LDIB, get_data());
}

static void ldic(ROM* rom) {
	parser_adv();
	rom->store(LDIC, get_data());
}

static void ina(ROM* rom) {
	parser_adv();
	rom->store(INA);
}

static void inb(ROM* rom) {
	parser_adv();
	rom->store(INB);
}

static void inc(ROM* rom) {
	parser_adv();
	rom->store(INC);
}

static void rdexp(ROM* rom) {
	parser_adv();
	rom->store(RDEXP);
}

static void wrexp(ROM* rom) {
	parser_adv();
	rom->store(WREXP);
}

static void sta(ROM* rom) {
	parser_adv();
	int data = get_data();

	if (parser_match(COMMA)) {
		parser_adv();

		if (parser_match(REG_B)) {
			parser_adv();
			rom->store(STA_B, data);
		}
		else if (parser_match(REG_C)) {
			parser_adv();
			rom->store(STA_C, data);
		}
		else parser_error();
		return;
	}

	rom->store(STA, data);
}

static void sta_l(ROM* rom) {
	parser_adv();
	int data = get_data();

	if (parser_match(COMMA)) {
		parser_adv();

		if (parser_match(REG_B)) {
			parser_adv();
			rom->store(STA_L_B, data);
		}
		else if (parser_match(REG_C)) {
			parser_adv();
			rom->store(STA_L_C, data);
		}
		else parser_error();
		return;
	}

	rom->store(STA_L, data);
}

static void stb(ROM* rom) {
	parser_adv();
	rom->store(STB, get_data());
}

static void stb_l(ROM* rom) {
	parser_adv();
	rom->store(STB_L, get_data());
}

static void stc(ROM* rom) {
	parser_adv();
	rom->store(STC, get_data());
}

static void stc_l(ROM* rom) {
	parser_adv();
	rom->store(STC_L, get_data());
}

static void pha(ROM* rom) {
	parser_adv();
	rom->store(PHA);
}

static void pla(ROM* rom) {
	parser_adv();
	rom->store(PLA);
}

static void phf(ROM* rom) {
	parser_adv();
	rom->store(PHF);
}

static void plf(ROM* rom) {
	parser_adv();
	rom->store(PLF);
}

static void add(ROM* rom) {
	parser_adv();
	rom->store(ADD);
}

static void sub(ROM* rom) {
	parser_adv();
	rom->store(SUB);
}

static void mult(ROM* rom) {
	parser_adv();
	rom->store(MULT);
}

static void div(ROM* rom) {
	parser_adv();
	rom->store(DIV);
}

static void jmp(ROM* rom) {
	parser_adv();
	rom->store(JMP, get_data());
}

static void jmpz(ROM* rom) {
	parser_adv();
	rom->store(JMPZ, get_data());
}

static void jmpc(ROM* rom) {
	parser_adv();
	rom->store(JMPC, get_data());
}

static void jclr(ROM* rom) {
	parser_adv();
	rom->store(JCLR, get_data());
}

static void jreg(ROM* rom) {
	parser_adv();
	rom->store(JREG);
}

static void call(ROM* rom) {
	parser_adv();
	rom->store(CALL, get_data());
}

static void ret(ROM* rom) {
	parser_adv();
	rom->store(RET);
}

static void swp(ROM* rom) {
	parser_adv();
	rom->store(SWP);
}

static void swpc(ROM* rom) {
	parser_adv();
	rom->store(SWPC);
}

static void hlt(ROM* rom) {
	parser_adv();
	rom->store(HLT);
}
