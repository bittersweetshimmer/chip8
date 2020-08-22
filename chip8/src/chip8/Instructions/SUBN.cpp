#include <iomanip>
#include <sstream>
#include <chip8/instructions/SUBN.hpp>

auto chip8::traits::Display<chip8::instructions::SUBN>::display(const chip8::instructions::SUBN& instruction) -> std::string {
    std::ostringstream ss;
    ss << "SUBN V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vy);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::SUBN>::execute(const chip8::instructions::SUBN& instruction, chip8::Chip8& chip8) -> void {
    if (chip8.general_purpose_registers[instruction.vx] < chip8.general_purpose_registers[instruction.vy]) {
        chip8.general_purpose_registers[0xF] = 0x01;
    }
    else {
        chip8.general_purpose_registers[0xF] = 0x00;
    }

    chip8.general_purpose_registers[instruction.vx] = chip8.general_purpose_registers[instruction.vy] - chip8.general_purpose_registers[instruction.vx];
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::SUBN>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SUBN> {
    if ((ic & 0xF00F) == 0x8007) return chip8::instructions::SUBN{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08),
        .vy = static_cast<chip8::GPRegister>(((ic & 0x00F0)) >> 0x04)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::SUBN>::encode(const chip8::instructions::SUBN& instruction) -> chip8::InstructionCode {
    return 0x8007 |
        ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8) |
        ((static_cast<chip8::InstructionCode>(instruction.vy) & 0x000F) << 4);
};