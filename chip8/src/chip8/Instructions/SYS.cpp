#include <iomanip>
#include <sstream>
#include <chip8/Instructions/SYS.hpp>

auto chip8::traits::Display<chip8::instructions::SYS>::display(const chip8::instructions::SYS& instruction) -> std::string {
    std::ostringstream ss;
    ss << "SYS  " << "0x" << std::setfill('0') << std::setw(3) << std::uppercase << std::hex << instruction.address;
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::SYS>::execute(const chip8::instructions::SYS& instruction, chip8::Chip8& chip8) -> void {
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::SYS>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SYS> {
    if ((ic & 0xF000) == 0x0000) return chip8::instructions::SYS{
        .address = static_cast<chip8::Address>(((ic & 0x0FFF))),
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::SYS>::encode(const chip8::instructions::SYS& instruction) -> chip8::InstructionCode {
    return 0x0000 | (instruction.address & 0x0FFF);
};