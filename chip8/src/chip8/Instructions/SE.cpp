#include <iomanip>
#include <sstream>
#include <chip8/instructions/SE.hpp>

auto chip8::traits::Display<chip8::instructions::SEbyte>::display(const chip8::instructions::SEbyte& instruction) -> std::string {
    std::ostringstream ss;
    ss << "SE   V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "0x" << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<std::size_t>(instruction.byte);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::SEbyte>::execute(const chip8::instructions::SEbyte& instruction, chip8::Chip8& chip8) -> void {
    if (chip8.general_purpose_registers[instruction.vx] == instruction.byte) {
        chip8.program_counter += 0x02;
    }

    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::SEbyte>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SEbyte> {
    if ((ic & 0xF000) == 0x3000) return chip8::instructions::SEbyte{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08),
        .byte = static_cast<chip8::Byte>((ic & 0x00FF))
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::SEbyte>::encode(const chip8::instructions::SEbyte& instruction) -> chip8::InstructionCode {
    return 0x3000 | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8) | instruction.byte;
};







auto chip8::traits::Display<chip8::instructions::SEregister>::display(const chip8::instructions::SEregister& instruction) -> std::string {
    std::ostringstream ss;
    ss << "SE   V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vy);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::SEregister>::execute(const chip8::instructions::SEregister& instruction, chip8::Chip8& chip8) -> void {
    if (chip8.general_purpose_registers[instruction.vx] == chip8.general_purpose_registers[instruction.vy]) {
        chip8.program_counter += 0x02;
    }

    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::SEregister>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SEregister> {
    if ((ic & 0xF00F) == 0x5000) return chip8::instructions::SEregister{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08),
        .vy = static_cast<chip8::GPRegister>(((ic & 0x00F0)) >> 0x04)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::SEregister>::encode(const chip8::instructions::SEregister& instruction) -> chip8::InstructionCode {
    return 0x5000 | ((static_cast<std::uint16_t>(instruction.vx) & 0x000F) << 8) | ((static_cast<std::uint16_t>(instruction.vy) & 0x000F) << 4);
};







auto chip8::traits::Display<chip8::instructions::SE>::display(const chip8::instructions::SE& instruction) -> std::string {
    return std::visit([](auto&& v) -> std::string { return chip8::display(v); }, instruction);
};

auto chip8::traits::Instruction<chip8::instructions::SE>::execute(const chip8::instructions::SE& instruction, chip8::Chip8& chip8) -> void {
    std::visit([&chip8](auto&& v) -> void { return chip8::execute(v, chip8); }, instruction);
};

auto chip8::traits::Instruction<chip8::instructions::SE>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SE> {
    if      (auto se_byte     = chip8::decode<chip8::instructions::SEbyte>    (ic)) return chip8::instructions::SE(    se_byte.value());
    else if (auto se_register = chip8::decode<chip8::instructions::SEregister>(ic)) return chip8::instructions::SE(se_register.value());
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::SE>::encode(const chip8::instructions::SE& instruction) -> chip8::InstructionCode {
    return std::visit([](auto&& v) -> chip8::InstructionCode { return chip8::encode(v); }, instruction);
};