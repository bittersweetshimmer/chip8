#include <iomanip>
#include <sstream>
#include <chip8/Instructions/AND.hpp>

auto chip8::traits::Display<chip8::instructions::AND>::display(const chip8::instructions::AND& instruction) -> std::string {
    std::ostringstream ss;
    ss << "AND  V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vy);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::AND>::execute(const chip8::instructions::AND& instruction, chip8::Chip8& chip8) -> void {
    chip8.general_purpose_registers[instruction.vx] &= chip8.general_purpose_registers[instruction.vy];
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::AND>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::AND> {
    if ((ic & 0xF00F) == 0x8002) return chip8::instructions::AND{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08),
        .vy = static_cast<chip8::GPRegister>(((ic & 0x00F0)) >> 0x04)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::AND>::encode(const chip8::instructions::AND& instruction) -> chip8::InstructionCode {
    return 0x8002 |
        ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8) |
        ((static_cast<chip8::InstructionCode>(instruction.vy) & 0x000F) << 4);
};