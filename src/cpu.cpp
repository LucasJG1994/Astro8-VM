#include "cpu.h"
#include "cpu_opcodes.h"
#include "graphics.h"
#include <stdint.h>
#include <iostream>
#include <stdint.h>
#include <SDL.h>
#include <map>
#include <vector>

typedef uint16_t u16;

#define PROG_OFFSET 0
#define CHAR_OFFSET 16383
#define VAR_OFFSET  16528
#define VRAM_OFFSET 65278

#define CHAR_SIZE 6
#define VRAM_SIZE 4

enum cpu_masks {
	OPCODE_MASK = 0x00ff,
	LB_MASK     = 0x0fff,
	CARRY		= 0x0002,
	ZERO		= 0x0001
};

static const char char_rom[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
	0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
	0x00, 0x04, 0x0E, 0x04, 0x00, 0x00,
	0x00, 0x00, 0x0E, 0x00, 0x00, 0x00,
	0x00, 0x0A, 0x04, 0x0A, 0x00, 0x00,
	0x10, 0x10, 0x08, 0x04, 0x04, 0x00,
	0x3F, 0x21, 0x21, 0x21, 0x21, 0x3F,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3F,
	0x04, 0x02, 0x01, 0x02, 0x04, 0x00,
	0x08, 0x10, 0x20, 0x10, 0x08, 0x00,
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
	0x00, 0x00, 0x3F, 0x3F, 0x00, 0x00,
	0x06, 0x09, 0x0F, 0x09, 0x09, 0x00,
	0x07, 0x09, 0x07, 0x09, 0x07, 0x00,
	0x06, 0x09, 0x01, 0x09, 0x06, 0x00,
	0x07, 0x09, 0x09, 0x09, 0x07, 0x00,
	0x0F, 0x01, 0x07, 0x01, 0x0F, 0x00,
	0x0F, 0x01, 0x07, 0x01, 0x01, 0x00, 
	0x06, 0x01, 0x0D, 0x09, 0x06, 0x00, 
	0x09, 0x09, 0x0F, 0x09, 0x09, 0x00,
	0x07, 0x02, 0x02, 0x02, 0x07, 0x00, 
	0x1E, 0x08, 0x08, 0x09, 0x06, 0x00,
	0x09, 0x05, 0x03, 0x05, 0x09, 0x00, 
	0x01, 0x01, 0x01, 0x01, 0x0F, 0x00, 
	0x11, 0x1B, 0x15, 0x11, 0x11, 0x00, 
	0x09, 0x0B, 0x0D, 0x09, 0x09, 0x00, 
	0x06, 0x09, 0x09, 0x09, 0x06, 0x00, 
	0x07, 0x09, 0x07, 0x01, 0x01, 0x00, 
	0x06, 0x09, 0x09, 0x09, 0x16, 0x00,
	0x07, 0x09, 0x07, 0x09, 0x09, 0x00, 
	0x0E, 0x01, 0x06, 0x08, 0x07, 0x00, 
	0x07, 0x02, 0x02, 0x02, 0x02, 0x00,
	0x09, 0x09, 0x09, 0x09, 0x06, 0x00,
	0x11, 0x11, 0x0A, 0x0A, 0x04, 0x00,
	0x11, 0x11, 0x15, 0x1B, 0x11, 0x00,
	0x09, 0x09, 0x06, 0x09, 0x09, 0x00,
	0x11, 0x11, 0x0A, 0x04, 0x04, 0x00,
	0x1F, 0x10, 0x0E, 0x01, 0x1F, 0x00, 
	0x06, 0x0D, 0x0B, 0x09, 0x06, 0x00, 
	0x04, 0x06, 0x04, 0x04, 0x04, 0x00,
	0x06, 0x09, 0x04, 0x02, 0x0F, 0x00,
	0x07, 0x08, 0x06, 0x08, 0x07, 0x00,
	0x09, 0x09, 0x0F, 0x08, 0x08, 0x00,
	0x0F, 0x01, 0x06, 0x08, 0x07, 0x00,
	0x06, 0x01, 0x07, 0x09, 0x06, 0x00,
	0x0F, 0x08, 0x04, 0x04, 0x04, 0x00,
	0x06, 0x09, 0x06, 0x09, 0x06, 0x00,
	0x06, 0x09, 0x0E, 0x08, 0x06, 0x00,
	0x06, 0x08, 0x04, 0x00, 0x04, 0x00,
	0x04, 0x04, 0x04, 0x00, 0x04, 0x00,
	0x0A, 0x0F, 0x0A, 0x0F, 0x0A, 0x00, 
	0x0E, 0x05, 0x06, 0x0A, 0x07, 0x00,
	0x00, 0x12, 0x08, 0x04, 0x12, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x04, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x04, 0x00,
	0x00, 0x04, 0x00, 0x04, 0x00, 0x00,
	0x00, 0x04, 0x00, 0x04, 0x02, 0x00,
	0x08, 0x04, 0x04, 0x04, 0x08, 0x00,
	0x02, 0x04, 0x04, 0x04, 0x02, 0x00,
	0x0C, 0x04, 0x04, 0x04, 0x0C, 0x00,
	0x06, 0x04, 0x04, 0x04, 0x06, 0x00,
	0x0C, 0x04, 0x06, 0x04, 0x0C, 0x00,
	0x06, 0x04, 0x0C, 0x04, 0x06, 0x00,
	0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x04, 0x00, 0x00, 0x00, 0x00,
	0x0A, 0x04, 0x0A, 0x00, 0x00, 0x00,
	0x04, 0x05, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x0E, 0x00, 0x0E, 0x00, 0x00,
	0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00,
	0x28, 0x2A, 0x11, 0x2A, 0x28, 0x00,
	0x04, 0x0A, 0x11, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x11, 0x0A, 0x04,
};

static std::map<long long int, unsigned char> key_mapping = {
	{SDLK_SPACE, 0},
	{SDLK_F1, 1},
	{SDLK_F2, 2},
	{SDLK_KP_PLUS, 3},
	{SDLK_KP_MINUS, 4},
	{SDLK_KP_MULTIPLY, 5},
	{SDLK_KP_DIVIDE, 6},
	{SDLK_F3, 7},
	{SDLK_UNDERSCORE, 8},
	{SDLK_LESS, 9},
	{SDLK_GREATER, 10},
	
	{SDLK_a, 13},
	{SDLK_b, 14},
	{SDLK_c, 15},
	{SDLK_d, 16},
	{SDLK_e, 17},
	{SDLK_f, 18},
	{SDLK_g, 19},
	{SDLK_h, 20},
	{SDLK_i, 21},
	{SDLK_j, 22},
	{SDLK_k, 23},
	{SDLK_l, 24},
	{SDLK_m, 25},
	{SDLK_n, 26},
	{SDLK_o, 27},
	{SDLK_p, 28},
	{SDLK_q, 29},
	{SDLK_r, 30},
	{SDLK_s, 31},
	{SDLK_t, 32},
	{SDLK_u, 33},
	{SDLK_v, 34},
	{SDLK_w, 35},
	{SDLK_x, 36},
	{SDLK_y, 37},
	{SDLK_z, 38},
	{SDLK_0, 39},
	{SDLK_1, 40},
	{SDLK_2, 41},
	{SDLK_3, 42},
	{SDLK_4, 43},
	{SDLK_5, 44},
	{SDLK_6, 45},
	{SDLK_7, 46},
	{SDLK_8, 47},
	{SDLK_9, 48},
	{SDLK_QUESTION, 49},
	{SDLK_EXCLAIM, 50},
	{SDLK_HASH, 51},
	{SDLK_DOLLAR, 52},
	{SDLK_PERCENT, 53},
	{SDLK_PERIOD, 54},
	{SDLK_COMMA, 55},
	{SDLK_COLON, 56},
	{SDLK_SEMICOLON, 57},
	{SDLK_LEFTPAREN, 58},
	{SDLK_RIGHTPAREN, 59},
	{SDLK_LEFTBRACKET, 60},
	{SDLK_RIGHTBRACKET, 61},
	
	{SDLK_QUOTEDBL, 64},
	{SDLK_QUOTE, 65},
	
	{SDLK_EQUALS, 68},
};

struct History {
	u16 A, B, C, IP;
	unsigned char flag;
	unsigned int ExpansionPort;
};

static std::vector<History> history;
static unsigned char history_index = 0;

static std::vector<u16> STACK;
#define PUSH(V) STACK.push_back(V)
#define POP STACK.back(); STACK.pop_back()

static u16 INS[16383] = { 0 };
static u16 CLS[0xFF][0xFF] = { 0 };
static u16 RAM[0xFFFF] = { 0 };
static u16 IP = 0;
static u16 SP = 0; // Stack Pointer
static u16 A = 0, B = 0, C = 0;
static unsigned char flag = 0;

Color palette[2] = {
	{0, 0, 0},
	{254, 254, 254}
};

//Shared Global Variable
unsigned int ExpansionPort = 0;
extern cpu_state cs;

static void decoder();
static void GPU();

#ifndef DEBUG
void cpu_init(ROM* rom) {
	if(rom == nullptr) { cs = CPU_HLT; return; }
	std::memcpy(INS, rom->bytes, rom->size);
#else
void cpu_init(){
	//RAM[ CHAR_OFFSET ] = 13;
	RAM[ CHAR_OFFSET ] = 13;
	RAM[ CHAR_OFFSET + 10 ] = 17;
#endif
}

void cpu_update() {
	decoder( );
	GPU();
}

static void decoder() {
	for(int i = 0; i < 16; i++){
	if(IP >= 0xFFFE) {
		cs = CPU_HLT;
		std::cout << "CPU has halted...\n";
		history_index = history.size() - 1;
		cpu_display();
		return;
	}

	History hs;
	hs.A = A;
	hs.B = B;
	hs.C = C;
	hs.IP = IP;
	hs.flag = flag;
	hs.ExpansionPort = ExpansionPort;

	history.push_back(hs);

	if(history.size() > 255) history.erase(history.begin());

	u16 instruction = INS[IP++];

	u16 opcode	= instruction & OPCODE_MASK;

	switch (opcode) {
		case NOP	: IP++; break;

		case AIN	: A = RAM[ INS[IP++] ]; break;
		case AIN_L	: A = CLS[SP][ INS[IP++] & 0xFF ]; break;
		case AIN_B	: A = RAM[ INS[IP++] + B ]; break;
		case AIN_L_B: A = CLS[SP][ (INS[IP++] & 0xFF) + B ]; break;
		case AIN_C	: A = RAM[ INS[IP++] + C ]; break;
		case AIN_L_C: A = CLS[SP][ (INS[IP++] & 0xFF) + C ]; break;
		case BIN	: B = RAM[ INS[IP++] ]; break;
		case BIN_L	: B = CLS[SP][ INS[IP++] & 0xFF ]; break;
		case CIN	: C = RAM[ INS[IP++] ]; break;
		case CIN_L	: C = CLS[SP][ INS[IP++] & 0xFF ]; break;

		case LDIA	: A = INS[IP++]; break;
		case LDIB	: B = INS[IP++]; break;
		case LDIC	: C = INS[IP++]; break;

		case INA	: A++; IP++; break;
		case INB	: B++; IP++; break;
		case INC	: C++; IP++; break;

		//case RDEXP	: A = key_mapping[ExpansionPort]; IP++; break;
		//case WREXP	: ExpansionPort = A; IP++; break;

		case STA	: RAM[ INS[IP++] ] = A; break;
		case STA_L	: CLS[SP][ INS[IP++] & 0xFF ] = A; break;
		case STA_B	: RAM[ INS[IP++] + B] = A; break;
		case STA_L_B: CLS[SP][ (INS[IP++] & 0xFF) + B ] = A; break;
		case STA_C	: RAM[ INS[IP++] + C] = A; break;
		case STA_L_C: CLS[SP][ (INS[IP++] & 0xFF) + C ] = A; break;
		case STB	: RAM[ INS[IP++] ] = B; break;
		case STB_L	: CLS[SP][ INS[IP++] & 0xFF ] = B; break;
		case STC	: RAM[ INS[IP++] ] = C; break;
		case STC_L	: CLS[SP][ INS[IP++] & 0xFF ] = C; break;

		case PHA	: PUSH(A); break;
		case PLA	: A = POP; break;
		case PHF	: PUSH(flag); break;
		case PLF	: flag = POP; break;

		case ADD:
			A += B;
			flag |= (A == 0)	? ZERO: 0;
			flag |= (A & 0x8000)? CARRY:0;
			IP++;
			break;
		case SUB:
			A -= B;
			flag |= (A == 0)	? ZERO: 0;
			flag |= (A & 0x8000)? CARRY:0;
			IP++;
			break;
		case MULT:
			A *= B;
			flag |= (A == 0)	? ZERO: 0;
			flag |= (A & 0x8000)? CARRY:0;
			IP++;
			break;
		case DIV:
			flag = 0;
			if(B == 0){ flag |= ZERO; break;}
			A /= B;
			flag |= (A == 0)	? ZERO: 0;
			flag |= (A & 0x8000)? CARRY:0;
			IP++;
			break;

		case JMP	: IP = INS[ IP ] * 2; break;
		case JMPZ	: IP = (flag & ZERO) ? INS[ IP ] * 2: IP + 1; break;
		case JMPC	: IP = (flag & CARRY)? INS[ IP ] * 2: IP + 1; break;
		case JCLR	: IP = (flag == 0)	 ? INS[ IP ] * 2: IP + 1; break;
		case JREG	: IP = A * 2; break;

		case CALL: 
			SP++; 
			CLS[SP][ 0 ] = IP + 1;
			CLS[SP][ 1 ] = flag;
			IP = INS[ IP ] * 2;
			break;
		case RET: 
			IP = CLS[SP][ 0 ]; 
			flag = CLS[SP][ 1 ];
			SP--; 
			break;

		case SWP:
			C = A;
			A = B;
			B = C;
			IP++;
			break;
		case SWPC:
			B = A;
			A = C;
			C = B;
			IP++;
			break;

		case HLT: 
			cs = CPU_HLT;
			std::cout << "CPU has halted...\n";
			history_index = history.size() - 1;
			cpu_display();
			break;
	}
	}
}

static void GPU() {
	Color col;
	u16 val;
	const char* c;

	for (int i = 0; i < 100; i++) {
		val = RAM[CHAR_OFFSET + i] % 73;
		RAM[ VRAM_OFFSET + ((i % VRAM_SIZE) + VRAM_SIZE * (0 / VRAM_SIZE)) ] ^= char_rom[val * CHAR_SIZE + 0];
		RAM[ VRAM_OFFSET + ((i % VRAM_SIZE) + VRAM_SIZE * (1 / VRAM_SIZE)) ] ^= char_rom[val * CHAR_SIZE + 1];
		RAM[ VRAM_OFFSET + ((i % VRAM_SIZE) + VRAM_SIZE * (2 / VRAM_SIZE)) ] ^= char_rom[val * CHAR_SIZE + 2];
		RAM[ VRAM_OFFSET + ((i % VRAM_SIZE) + VRAM_SIZE * (3 / VRAM_SIZE)) ] ^= char_rom[val * CHAR_SIZE + 3];
		RAM[ VRAM_OFFSET + ((i % VRAM_SIZE) + VRAM_SIZE * (4 / VRAM_SIZE)) ] ^= char_rom[val * CHAR_SIZE + 4];
		RAM[ VRAM_OFFSET + ((i % VRAM_SIZE) + VRAM_SIZE * (5 / VRAM_SIZE)) ] ^= char_rom[val * CHAR_SIZE + 5];
	}

	for (int i = 0; i < 257; i++) {
		val = RAM[ VRAM_OFFSET + i ];
		graphics_plot(((i % VRAM_SIZE) * 16) + 0, i / VRAM_SIZE, palette[(val & 0x0001) >> 0]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 1, i / VRAM_SIZE, palette[(val & 0x0002) >> 1]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 2, i / VRAM_SIZE, palette[(val & 0x0004) >> 2]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 3, i / VRAM_SIZE, palette[(val & 0x0008) >> 3]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 4, i / VRAM_SIZE, palette[(val & 0x0010) >> 4]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 5, i / VRAM_SIZE, palette[(val & 0x0020) >> 5]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 6, i / VRAM_SIZE, palette[(val & 0x0040) >> 6]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 7, i / VRAM_SIZE, palette[(val & 0x0080) >> 7]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 8, i / VRAM_SIZE, palette[(val & 0x0100) >> 8]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 9, i / VRAM_SIZE, palette[(val & 0x0200) >> 9]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 10, i / VRAM_SIZE, palette[(val & 0x0400) >> 10]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 11, i / VRAM_SIZE, palette[(val & 0x0800) >> 11]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 12, i / VRAM_SIZE, palette[(val & 0x1000) >> 12]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 13, i / VRAM_SIZE, palette[(val & 0x2000) >> 13]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 14, i / VRAM_SIZE, palette[(val & 0x4000) >> 14]);
		graphics_plot(((i % VRAM_SIZE) * 16) + 15, i / VRAM_SIZE, palette[(val & 0x8000) >> 15]);
	}
}

void cpu_prev() {
	if(history_index > 0) history_index--;
}

void cpu_next() {
	if(history_index < history.size() - 1) history_index++;
}

void cpu_display() {
	std::cout << "\n====================================\n";
	std::cout << "REG: " << history[history_index].A << " , " << history[history_index].B << " , " << history[history_index].C <<std::endl;
	std::cout << "IP: " << history[history_index].IP << std::endl;
	std::cout << "FLAG: " << (int)history[history_index].flag << std::endl;
	std::cout << "EXP: " << history[history_index].ExpansionPort << std::endl;
	std::cout << "\n====================================\n";
}