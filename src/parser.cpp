#include "parser.h"
#include "tokens.h"
#include <queue>
#include <map>
#include <stack>
#include <iostream>

parser_state par_state;

static std::queue<token>* token_stream;
static std::map<std::string, int> def_labels;
static std::map<std::string, std::stack<int>> undef_labels;
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

static int parser_peek() {
	return token_stream->front().type;
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

static void parser_consume(int type) {
	if (parser_match(type)) parser_adv();
	else parser_error();
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

static void _and(ROM* rom);
static void _or(ROM* rom);
static void _not(ROM* rom);
static void _xor(ROM* rom);

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

static void label(ROM* rom);
static int get_label(ROM* rom);
static void def_label(ROM* rom);

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
			case LABEL: label(rom); break;

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
	int data;
	if(parser_match(LABEL)) data = get_label(rom);
	else data = get_data();

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
	int data;
	if (parser_match(LABEL)) data = get_label(rom);
	else data = get_data();

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
	int data;
	if (parser_match(LABEL)) data = get_label(rom);
	else data = get_data();
	rom->store(BIN, data);
}

static void bin_l(ROM* rom) {
	parser_adv();
	int data;
	if (parser_match(LABEL)) data = get_label(rom);
	else data = get_data();
	rom->store(BIN_L, data);
}

static void cin(ROM* rom) {
	parser_adv();
	int data;
	if (parser_match(LABEL)) data = get_label(rom);
	else data = get_data();
	rom->store(CIN, data);
}

static void cin_l(ROM* rom) {
	parser_adv();
	int data;
	if (parser_match(LABEL)) data = get_label(rom);
	else data = get_data();
	rom->store(CIN_L, data);
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
	int data;
	if (parser_match(LABEL)) data = get_label(rom);
	else data = get_data();

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
	int data;
	if (parser_match(LABEL)) data = get_label(rom);
	else data = get_data();

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
	int data;
	if (parser_match(LABEL)) data = get_label(rom);
	else data = get_data();
	rom->store(STB, data);
}

static void stb_l(ROM* rom) {
	parser_adv();
	int data;
	if (parser_match(LABEL)) data = get_label(rom);
	else data = get_data();
	rom->store(STB_L, data);
}

static void stc(ROM* rom) {
	parser_adv();
	int data;
	if (parser_match(LABEL)) data = get_label(rom);
	else data = get_data();
	rom->store(STC, data);
}

static void stc_l(ROM* rom) {
	parser_adv();
	int data;
	if (parser_match(LABEL)) data = get_label(rom);
	else data = get_data();
	rom->store(STC_L, data);
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

static void _and(ROM* rom) {
	parser_adv();
	rom->store(AND);
}

static void _or(ROM* rom) {
	parser_adv();
	rom->store(OR);
}

static void _not(ROM* rom) {
	parser_adv();
	rom->store(NOT);
}

static void _xor(ROM* rom) {
	parser_adv();
	rom->store(XOR);
}

static void jmp(ROM* rom) {
	parser_adv();
	if (parser_match(LABEL)) {
		rom->store(JMP, get_label(rom));
		return;
	}
	rom->store(JMP, get_data());
}

static void jmpz(ROM* rom) {
	parser_adv();
	if (parser_match(LABEL)) {
		rom->store(JMPZ, get_label(rom));
		return;
	}
	rom->store(JMPZ, get_data());
}

static void jmpc(ROM* rom) {
	parser_adv();
	if (parser_match(LABEL)) {
		rom->store(JMPC, get_label(rom));
		return;
	}
	rom->store(JMPC, get_data());
}

static void jclr(ROM* rom) {
	parser_adv();
	if (parser_match(LABEL)) {
		rom->store(JCLR, get_label(rom));
		return;
	}
	rom->store(JCLR, get_data());
}

static void jreg(ROM* rom) {
	parser_adv();
	rom->store(JREG);
}

static void call(ROM* rom) {
	parser_adv();
	if (parser_match(LABEL)) {
		rom->store(CALL, get_label(rom));
		return ;
	}
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

static void label(ROM* rom) {
	if(parser_peek() == ASSIGN){ def_label(rom); return; }

	if (undef_labels.find(cur.lexeme) == undef_labels.end()) {
		if (def_labels.find(cur.lexeme) == def_labels.end()) {
			def_labels[cur.lexeme] = rom->get_IP();
		}
		else{} // Do nothing
	}
	else {
		std::stack<int> IPs = undef_labels[cur.lexeme];
		while (IPs.empty() == 0) {
			int IP = IPs.top(); IPs.pop();
			rom->insert(IP, rom->get_IP());
		}
		undef_labels.erase(cur.lexeme);
		def_labels[cur.lexeme] = rom->get_IP();
	}
	parser_adv();
}

static int get_label(ROM* rom) {
	if (def_labels.find(cur.lexeme) == def_labels.end()) {
		if (undef_labels.find(cur.lexeme) == undef_labels.end()) {
			std::stack<int> IPs;
			IPs.push(rom->get_IP());
			undef_labels[cur.lexeme] = IPs;
		}
		else {
			std::stack<int> IPs = undef_labels[cur.lexeme];
			IPs.push(rom->get_IP());
			undef_labels[cur.lexeme] = IPs;
		}
		parser_adv();
		return 0;
	}
	int IP = def_labels[cur.lexeme];
	parser_adv();
	return IP;
}

static void def_label(ROM* rom) {
	std::string label = cur.lexeme;
	parser_adv();
	parser_consume(ASSIGN);
	def_labels[label] = get_data();
}