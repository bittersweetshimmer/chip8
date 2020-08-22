#include <chip8/Instructions/CLS.hpp>

auto chip8::traits::Display<chip8::instructions::CLS>::display(const chip8::instructions::CLS&) -> std::string {
    return "CLS";
};

auto chip8::traits::Instruction<chip8::instructions::CLS>::execute(const chip8::instructions::CLS&, chip8::Chip8& chip8) -> void {
    chip8.display = chip8::Display{};
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::CLS>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::CLS> {
    if (ic == 0x00E0) return chip8::instructions::CLS{};
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::CLS>::encode(const chip8::instructions::CLS&) -> chip8::InstructionCode {
    return 0x00E0;
};