#include <iomanip>
#include <sstream>
#include <chip8/instructions/ADD.hpp>

auto chip8::traits::Display<chip8::instructions::ADDbyte>::display(const chip8::instructions::ADDbyte& instruction) -> std::string {
    std::ostringstream ss;
    ss << "ADD  V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "0x" << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<std::size_t>(instruction.byte);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::ADDbyte>::execute(const chip8::instructions::ADDbyte& instruction, chip8::Chip8& chip8) -> void {
    chip8.general_purpose_registers[instruction.vx] += instruction.byte;
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::ADDbyte>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::ADDbyte> {
    if ((ic & 0xF000) == 0x7000) return chip8::instructions::ADDbyte{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08),
        .byte = static_cast<chip8::Byte>((ic & 0x00FF))
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::ADDbyte>::encode(const chip8::instructions::ADDbyte& instruction) -> chip8::InstructionCode {
    return 0x7000 | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8) | instruction.byte;
};







auto chip8::traits::Display<chip8::instructions::ADDregister>::display(const chip8::instructions::ADDregister& instruction) -> std::string {
    std::ostringstream ss;
    ss << "ADD  V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vy);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::ADDregister>::execute(const chip8::instructions::ADDregister& instruction, chip8::Chip8& chip8) -> void {
    chip8.general_purpose_registers[instruction.vx] += chip8.general_purpose_registers[instruction.vy];

    if (chip8.general_purpose_registers[instruction.vx] < chip8.general_purpose_registers[instruction.vy]) {
        chip8.general_purpose_registers[0xF] = 0x01;
    }
    else {
        chip8.general_purpose_registers[0xF] = 0x00;
    }

    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::ADDregister>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::ADDregister> {
    if ((ic & 0xF00F) == 0x8004) return chip8::instructions::ADDregister{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08),
        .vy = static_cast<chip8::GPRegister>(((ic & 0x00F0)) >> 0x04)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::ADDregister>::encode(const chip8::instructions::ADDregister& instruction) -> chip8::InstructionCode {
    return 0x8004 | ((static_cast<std::uint16_t>(instruction.vx) & 0x000F) << 8) | ((static_cast<std::uint16_t>(instruction.vy) & 0x000F) << 4);
};







auto chip8::traits::Display<chip8::instructions::ADDaddress>::display(const chip8::instructions::ADDaddress& instruction) -> std::string {
    std::ostringstream ss;
    ss << "ADD  I, ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::ADDaddress>::execute(const chip8::instructions::ADDaddress& instruction, chip8::Chip8& chip8) -> void {
    chip8.address_register += chip8.general_purpose_registers[instruction.vx];
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::ADDaddress>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::ADDaddress> {
    if ((ic & 0xF0FF) == 0xF01E) return chip8::instructions::ADDaddress{
        .vx = static_cast<GPRegister>(((ic & 0x0F00)) >> 0x08)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::ADDaddress>::encode(const chip8::instructions::ADDaddress& instruction) -> chip8::InstructionCode {
    return 0xF01E | ((static_cast<std::uint16_t>(instruction.vx) & 0x000F) << 8);
};







auto chip8::traits::Display<chip8::instructions::ADD>::display(const chip8::instructions::ADD& instruction) -> std::string {
    return std::visit([](auto&& v) -> std::string { return chip8::display(v); }, instruction);
};

auto chip8::traits::Instruction<chip8::instructions::ADD>::execute(const chip8::instructions::ADD& instruction, chip8::Chip8& chip8) -> void {
    std::visit([&chip8](auto&& v) -> void { return chip8::execute(v, chip8); }, instruction);
};

auto chip8::traits::Instruction<chip8::instructions::ADD>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::ADD> {
    if      (auto add_byte     = chip8::decode<chip8::instructions::ADDbyte>    (ic)) return chip8::instructions::ADD(    add_byte.value());
    else if (auto add_register = chip8::decode<chip8::instructions::ADDregister>(ic)) return chip8::instructions::ADD(add_register.value());
    else if (auto add_address  = chip8::decode<chip8::instructions::ADDaddress> (ic)) return chip8::instructions::ADD( add_address.value());
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::ADD>::encode(const chip8::instructions::ADD& instruction) -> chip8::InstructionCode {
    return std::visit([](auto&& v) -> chip8::InstructionCode { return chip8::encode(v); }, instruction);
};