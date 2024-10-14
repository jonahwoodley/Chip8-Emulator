#pragma once

#include <cstdint>
#include <array>
#include <cstring>
#include <iostream>
#include <fstream>

#include <SDL.h>

#include "audio_manager.hpp"

const uint16_t CLEAR_DISPLAY = 0x0000;
const uint16_t RET = 0x000E;
const uint16_t JMP = 0x1000;
const uint16_t CALL = 0x2000;
const uint16_t SE_VX_BYTE = 0x3000;
const uint16_t SNE_VX_BYTE = 0x4000;
const uint16_t SE_VX_VY = 0x5000;
const uint16_t LD_VX_BYTE = 0x6000;
const uint16_t ADD_VX_BYTE = 0x7000;

// 0x8000 Group
const uint16_t LD_VX_VY = 0x0000;
const uint16_t OR_VX_VY = 0x0001;
const uint16_t AND_VX_VY = 0x0002;
const uint16_t XOR_VX_VY = 0x0003;
const uint16_t ADD_VX_VY = 0x0004;
const uint16_t SUB_VX_VY = 0x0005;
const uint16_t SHR_VX = 0x0006;
const uint16_t SUBN_VX_VY = 0x0007;
const uint16_t SHL_VX = 0x000E;

const uint16_t SNE_VX_VY = 0x9000;
const uint16_t LD_I = 0xA000;
const uint16_t JP_V0 = 0xB000;
const uint16_t RND_VX_BYTE = 0xC000;
const uint16_t DRW_VX_VY_N = 0xD000;

// 0xE000 Group
const uint16_t SKP_VX = 0x009E;
const uint16_t SKNP_VX = 0x00A1;

// 0x7000 Group
const uint16_t LD_VX_DT = 0x0007;
const uint16_t LD_VX_K = 0x000A;
const uint16_t LD_DT_VX = 0x0015;
const uint16_t LD_ST_VX = 0x0018;
const uint16_t ADD_I_VX = 0x001E;
const uint16_t LD_F_VX = 0x0029;
const uint16_t LD_B_VX = 0x0033;
const uint16_t LD_I_VX = 0x0055;
const uint16_t LD_VX_I = 0x0065;

class Chip8 {
public:
	Chip8();
	void init();
	void loadRom(const char* filename);
	void emulateCycle();
	void cleanUp();
	bool drawFlag;
	bool romLoaded;
	uint8_t memory[4096];
	uint8_t soundTimer;
	uint8_t sp; // Stack pointer
	uint8_t key[16];
	uint8_t gfx[64 * 32];
	uint8_t V[16]; // [V0 - VF]
	uint16_t stack[16];
	size_t romSize;
	uint32_t gamePixels[2048];

private:
	uint16_t opcode;
	uint16_t I;
	uint16_t pc; // Program counter
	uint8_t delayTimer;

	AudioManager audioManager;
};