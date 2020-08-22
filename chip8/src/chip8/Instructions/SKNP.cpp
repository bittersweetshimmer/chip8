#include <iomanip>
#include <sstream>
#include <chip8/Instructions/SKNP.hpp>

auto chip8::traits::Display<chip8::instructions::SKNP>::display(const chip8::instructions::SKNP& instruction) -> std::string {
    std::ostringstream ss;
    ss << "SKNP V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::SKNP>::execute(const chip8::instructions::SKNP& instruction, chip8::Chip8& chip8) -> void {
    if (!chip8::get_key(chip8.keyboard, chip8.general_purpose_registers[instruction.vx])) {
        chip8.program_counter += 0x02;
    }
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::SKNP>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SKNP> {
    if ((ic & 0xF0FF) == 0xE0A1) return chip8::instructions::SKNP{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::SKNP>::encode(const chip8::instructions::SKNP& instruction) -> chip8::InstructionCode {
    return 0xE0A1 | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8);
};