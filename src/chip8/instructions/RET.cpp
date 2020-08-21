#include <chip8/instructions/RET.hpp>

auto chip8::traits::Display<chip8::instructions::RET>::display(const chip8::instructions::RET&) -> std::string {
    return "RET";
};

auto chip8::traits::Instruction<chip8::instructions::RET>::execute(const chip8::instructions::RET&, chip8::Chip8& chip8) -> void {
    chip8.stack_pointer -= 0x01;
    chip8.program_counter = chip8.stack[chip8.stack_pointer];
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::RET>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::RET> {
    if (ic == 0x00EE) return chip8::instructions::RET{};
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::RET>::encode(const chip8::instructions::RET&) -> chip8::InstructionCode {
    return 0x00EE;
};