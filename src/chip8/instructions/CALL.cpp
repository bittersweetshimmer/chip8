#include <iomanip>
#include <sstream>
#include <chip8/instructions/CALL.hpp>

auto chip8::traits::Display<chip8::instructions::CALL>::display(const chip8::instructions::CALL& instruction) -> std::string {
    std::ostringstream ss;
    ss << "CALL  " << "0x" << std::setfill('0') << std::setw(3) << std::uppercase << std::hex << instruction.address;
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::CALL>::execute(const chip8::instructions::CALL& instruction, chip8::Chip8& chip8) -> void {
    chip8.stack[chip8.stack_pointer] = chip8.program_counter;
    chip8.stack_pointer += 0x01;
    chip8.program_counter = instruction.address;
};

auto chip8::traits::Instruction<chip8::instructions::CALL>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::CALL> {
    if ((ic & 0xF000) == 0x2000) return chip8::instructions::CALL{
        .address = static_cast<chip8::Address>(((ic & 0x0FFF))),
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::CALL>::encode(const chip8::instructions::CALL& instruction) -> chip8::InstructionCode {
    return 0x2000 | (instruction.address & 0x0FFF);
};