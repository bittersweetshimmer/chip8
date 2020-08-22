#include <iomanip>
#include <sstream>
#include <chip8/Instructions/RND.hpp>

auto chip8::traits::Display<chip8::instructions::RND>::display(const chip8::instructions::RND& instruction) -> std::string {
    std::ostringstream ss;
    ss << "RND  V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "0x" << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<std::size_t>(instruction.byte);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::RND>::execute(const chip8::instructions::RND& instruction, chip8::Chip8& chip8) -> void {
    chip8.general_purpose_registers[instruction.vx] = chip8.rng.next() & instruction.byte;
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::RND>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::RND> {
    if ((ic & 0xF000) == 0xC000) return chip8::instructions::RND{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08),
        .byte = static_cast<chip8::Byte>((ic & 0x00FF))
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::RND>::encode(const chip8::instructions::RND& instruction) -> chip8::InstructionCode {
    return 0xC000 |
        ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8) |
        instruction.byte;
};