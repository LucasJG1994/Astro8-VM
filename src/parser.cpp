#include "parser.h"
#include "scanner.h"
#include "tokens.h"
#include "String.h"
#include <iostream>

parser_state par_state;

void parser_init() {
	if (scan_advance() != SCAN_OK) {
		par_state = PARSER_ERR;
		return;
	}
}

static void parser_adv() {
	if (scan_advance() != SCAN_OK || par_state != PARSER_OK) {
		par_state = PARSER_ERR;
		return;
	}
}

static bool parser_match(token_type type) {
	return S_TYPE == type;
}

ROM* parser_start() {
	ROM* rom = rom_init();
	while (S_TYPE != T_EOF) {
		switch(S_TYPE){
			case NOP: rom->store(NOP); rom->store(0); parser_adv(); break;
			case AIN:
				rom->store(AIN);
				parser_adv();
				if(parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if(parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case BIN:
				rom->store(BIN);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case CIN:
				rom->store(CIN);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case LDIA:
				rom->store(LDIA);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case LDIB:
				rom->store(LDIB);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case RDEXP: rom->store(RDEXP); rom->store(0); parser_adv(); break;
			case WREXP: rom->store(WREXP); rom->store(0); parser_adv(); break;
			case STA:
				rom->store(STA);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case STC:
				rom->store(STC);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case ADD: rom->store(ADD); rom->store(0); parser_adv(); break;
			case SUB: rom->store(SUB); rom->store(0); parser_adv(); break;
			case MULT: rom->store(MULT); rom->store(0); parser_adv(); break;
			case DIV: rom->store(DIV); rom->store(0); parser_adv(); break;
			case JMP:
				rom->store(JMP);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case JMPZ:
				rom->store(JMPZ);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case JMPC:
				rom->store(JMPC);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case JREG: rom->store(JREG); rom->store(0); parser_adv(); break;
			case LDAIN: rom->store(LDAIN); rom->store(0); parser_adv(); break;
			case STAOUT: rom->store(STAOUT); rom->store(0); parser_adv(); break;
			case LDLGE:
				rom->store(LDLGE);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case STLGE:
				rom->store(STLGE);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case LDW:
				rom->store(LDW);
				parser_adv();
				if (parser_match(ADDR_HEX)) rom->store(S_LEXEME->to_hex());
				if (parser_match(ADDR_DEC)) rom->store(S_LEXEME->to_int());
				parser_adv();
				break;
			case SWP: rom->store(SWP); rom->store(0); parser_adv(); break;
			case SWPC: rom->store(SWPC); rom->store(0); parser_adv(); break;
			case HLT: rom->store(HLT); rom->store(0); parser_adv(); break;
			default: {
				std::cout << "Parser Error... " << S_LINE << std::endl;
				rom_close(rom);
				return nullptr;
			}
		}
	}
	return rom;
}