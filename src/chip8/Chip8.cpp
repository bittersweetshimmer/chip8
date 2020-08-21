#include <chip8/Chip8.hpp>

auto chip8::fetch(const chip8::Chip8& chip8) -> chip8::InstructionCode {
    chip8::InstructionCode ic = 0x0000;
    ic |= chip8.memory[chip8.program_counter + 0x00] << 0x08;
    ic |= chip8.memory[chip8.program_counter + 0x01] << 0x00;
    return ic;
}