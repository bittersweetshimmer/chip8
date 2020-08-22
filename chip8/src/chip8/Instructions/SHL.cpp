#include <iomanip>
#include <sstream>
#include <chip8/Instructions/SHL.hpp>

auto chip8::traits::Display<chip8::instructions::SHL>::display(const chip8::instructions::SHL& instruction) -> std::string {
    std::ostringstream ss;
    ss << "SHL  V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << "{, ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vy) << "}";
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::SHL>::execute(const chip8::instructions::SHL& instruction, chip8::Chip8& chip8) -> void {
    chip8.general_purpose_registers[0xF] = (chip8.general_purpose_registers[instruction.vx] >> 0x7) & 0b1;
            
    chip8.general_purpose_registers[instruction.vx] <<= 0b1;
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::SHL>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SHL> {
    if ((ic & 0xF00F) == 0x800E) return chip8::instructions::SHL{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08),
        .vy = static_cast<chip8::GPRegister>(((ic & 0x00F0)) >> 0x04)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::SHL>::encode(const chip8::instructions::SHL& instruction) -> chip8::InstructionCode {
    return 0x800E | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8) | ((static_cast<chip8::InstructionCode>(instruction.vy) & 0x000F) << 4);
};