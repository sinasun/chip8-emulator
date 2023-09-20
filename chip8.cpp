#include "chip8.h"
#include <chrono>
#include <cstdint>
#include <random>


uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8():randGen(std::chrono::system_clock::now().time_since_epoch().count()) {
  pc = START_ADDRESS;

  randByte = std::uniform_int_distribution<uint8_t>(0, 255U);

  for (uint8_t i = 0; i < FONTSET_SIZE; ++i) {
    memory[FONTSET_START_ADDRESS + i] = fontset[i];
  }
}

void Chip8::LoadROM(char const* filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if(file.is_open()) {
    std::streampos size = file.tellg();
    char* buffer = new char[size];

    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    for (long i = 0; i < size; ++i) {
      memory[START_ADDRESS + i] = buffer[i];
    }

    delete[] buffer;
  }
}

//Clear the display
void Chip8::OP_00E0() {
  std::memset(video, 0, sizeof(video));
}

//Return from a subroutine
void Chip8::OP_00EE() {
  pc = stack[--sp];
}

//Jump to location nnn
void Chip8::OP_1nnn() {
  pc = opcode & 0x0FFFu;
}

//Call subroutine at nnn
void Chip8::OP_2nnn() {
  stack[sp++] = pc;
  OP_1nnn();
}

//Skip next instruction if Vx == kk
void Chip8::OP_3xkk() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t kk = opcode & 0x00FFu;

  if (registers[Vx] == kk) {
    pc += 2;
  }
}

//Skip next instruction if Vx != kk
void Chip8::OP_4xkk() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t kk = opcode & 0x00FFu;

  if (registers[Vx] != kk) {
    pc += 2;
  }
}

//Skip next instruction if Vx == Vy
void Chip8::OP_5xy0() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  if (registers[Vx] == registers[Vy]) {
    pc += 2;
  }
}

// Set Vx = kk
void Chip8::OP_6xkk() {
  uint8_t Vx = (opcode & )
}

