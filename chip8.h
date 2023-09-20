#pragma once

#include "utils.h"

#include <cstdint>
#include <fstream>
#include <ios>
#include <chrono>
#include <random>
#include <cstring>

class Chip8
{
public:
    uint8_t registers[16]{};
    uint8_t memory[4096]{};
    uint16_t index{};
    uint16_t pc{};
    uint16_t stack[16]{};
    uint8_t sp{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint8_t keypad[16]{};
    uint32_t video[64 * 32]{};
    uint16_t opcode;
    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;

    Chip8();
    void LoadROM(char const* filename);
    
    void OP_00E0();
    void OP_00EE();
    void OP_1nnn();
    void OP_2nnn();
    void OP_3xkk();
    void OP_4xkk();
    void OP_5xy0();
    void OP_6xkk();
    void OP_7xkk();
    void OP_8xy0();
    void OP_8xy1();
    void OP_8xy2();
    void OP_8xy3();
    void OP_8xy4();
    void OP_8xy5();
    void OP_8xy6();
    void OP_8xy7();
    void OP_8xyE();
    void OP_9xy0();
    void OP_Annn();
    void OP_Bnnn();
    void OP_Cxkk();
    void OP_Dxyn();
    void OP_Ex9E();
    void OP_ExA1();
    void OP_Fx07();
    void OP_Fx0A();
    void OP_Fx15();
    void OP_Fx18();
    void OP_Fx1E();
    void OP_Fx29();
    void OP_Fx33();
    void OP_Fx55();
    void OP_Fx65();

  private:
    uint8_t getVx();
    uint8_t getVy();
    uint8_t getKk();
    uint8_t getNnn();
    uint8_t getN();
  };

const uint16_t START_ADDRESS = 0x200;
const uint8_t FONTSET_SIZE = 80;
const uint16_t FONTSET_START_ADDRESS = 0x50; 
