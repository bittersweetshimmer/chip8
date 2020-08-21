#include <iomanip>
#include <sstream>
#include <chip8/instructions/SKP.hpp>

auto chip8::traits::Display<chip8::instructions::SKP>::display(const chip8::instructions::SKP& instruction) -> std::string {
    std::ostringstream ss;
    ss << "SKP  V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::SKP>::execute(const chip8::instructions::SKP& instruction, chip8::Chip8& chip8) -> void {
    if (chip8.keyboard[chip8.general_purpose_registers[instruction.vx]] != 0x00) {
        chip8.program_counter += 0x02;
    }
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::SKP>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SKP> {
    if ((ic & 0xF0FF) == 0xE09E) return chip8::instructions::SKP{
        .vx = static_cast<GPRegister>(((ic & 0x0F00)) >> 0x08)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::SKP>::encode(const chip8::instructions::SKP& instruction) -> chip8::InstructionCode {
    return 0xE09E | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8);
};