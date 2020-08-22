#include <iomanip>
#include <sstream>
#include <chip8/Instructions/JP.hpp>

auto chip8::traits::Display<chip8::instructions::JPabsolute>::display(const chip8::instructions::JPabsolute& instruction) -> std::string {
    std::ostringstream ss;
    ss << "JP   " << "0x" << std::setfill('0') << std::setw(3) << std::uppercase << std::hex << instruction.address;
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::JPabsolute>::execute(const chip8::instructions::JPabsolute& instruction, chip8::Chip8& chip8) -> void {
    chip8.program_counter = instruction.address;
};

auto chip8::traits::Instruction<chip8::instructions::JPabsolute>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::JPabsolute> {
    if ((ic & 0xF000) == 0x1000) return chip8::instructions::JPabsolute{
        .address = static_cast<chip8::Address>((ic & 0x0FFF))
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::JPabsolute>::encode(const chip8::instructions::JPabsolute& instruction) -> chip8::InstructionCode {
    return 0x1000 | (instruction.address & 0x0FFF);
};







auto chip8::traits::Display<chip8::instructions::JPoffset>::display(const chip8::instructions::JPoffset& instruction) -> std::string {
    std::ostringstream ss;
    ss << "JP   V0, " << "0x" << std::setfill('0') << std::setw(3) << std::uppercase << std::hex << instruction.offset;
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::JPoffset>::execute(const chip8::instructions::JPoffset& instruction, chip8::Chip8& chip8) -> void {
    chip8.program_counter = chip8.general_purpose_registers[0x0] + instruction.offset;
};

auto chip8::traits::Instruction<chip8::instructions::JPoffset>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::JPoffset> {
    if ((ic & 0xF000) == 0xB000) return chip8::instructions::JPoffset{
        .offset = static_cast<chip8::Address>((ic & 0x0FFF))
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::JPoffset>::encode(const chip8::instructions::JPoffset& instruction) -> chip8::InstructionCode {
    return 0xB000 | (instruction.offset & 0x0FFF);
};







auto chip8::traits::Display<chip8::instructions::JP>::display(const chip8::instructions::JP& instruction) -> std::string {
    return std::visit([](auto&& v) -> std::string { return chip8::display(v); }, instruction);
};

auto chip8::traits::Instruction<chip8::instructions::JP>::execute(const chip8::instructions::JP& instruction, chip8::Chip8& chip8) -> void {
    std::visit([&chip8](auto&& v) -> void { return chip8::execute(v, chip8); }, instruction);
};

auto chip8::traits::Instruction<chip8::instructions::JP>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::JP> {
    if      (auto jp_absolute = chip8::decode<chip8::instructions::JPabsolute>(ic)) return chip8::instructions::JP(jp_absolute.value());
    else if (auto jp_offset   = chip8::decode<chip8::instructions::JPoffset>  (ic)) return chip8::instructions::JP(  jp_offset.value());
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::JP>::encode(const chip8::instructions::JP& instruction) -> chip8::InstructionCode {
    return std::visit([](auto&& v) -> chip8::InstructionCode { return chip8::encode(v); }, instruction);
};