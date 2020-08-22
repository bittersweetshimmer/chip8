#include <iomanip>
#include <sstream>
#include <chip8/instructions/LD.hpp>

auto chip8::traits::Display<chip8::instructions::LDbyte>::display(const chip8::instructions::LDbyte& instruction) -> std::string {
    std::ostringstream ss;
    ss << "LD   V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "0x" << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << static_cast<std::size_t>(instruction.byte);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::LDbyte>::execute(const chip8::instructions::LDbyte& instruction, chip8::Chip8& chip8) -> void {
    chip8.general_purpose_registers[instruction.vx] = instruction.byte;
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::LDbyte>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDbyte> {
    if ((ic & 0xF000) == 0x6000) return chip8::instructions::LDbyte{
        .vx   = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08),
        .byte = static_cast<chip8::Byte>       ((ic & 0x00FF))
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LDbyte>::encode(const chip8::instructions::LDbyte& instruction) -> chip8::InstructionCode {
    return 0x6000 |
        ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8) |
        instruction.byte;
};







auto chip8::traits::Display<chip8::instructions::LDregister>::display(const chip8::instructions::LDregister& instruction) -> std::string {
    std::ostringstream ss;
    ss << "LD   V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vy);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::LDregister>::execute(const chip8::instructions::LDregister& instruction, chip8::Chip8& chip8) -> void {
    chip8.general_purpose_registers[instruction.vx] = chip8.general_purpose_registers[instruction.vy];
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::LDregister>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDregister> {
    if (((ic & 0xF00F)) == 0x8000) return chip8::instructions::LDregister{
        .vx = static_cast<GPRegister>(((ic & 0x0F00)) >> 0x08),
        .vy = static_cast<GPRegister>(((ic & 0x00F0)) >> 0x04)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LDregister>::encode(const chip8::instructions::LDregister& instruction) -> chip8::InstructionCode {
    return 0x8000 |
        ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8) |
        ((static_cast<chip8::InstructionCode>(instruction.vy) & 0x000F) << 4);
};







auto chip8::traits::Display<chip8::instructions::LDkeyPress>::display(const chip8::instructions::LDkeyPress& instruction) -> std::string {
    std::ostringstream ss;
    ss << "LD   V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "K";
    return ss.str();  
};

auto chip8::traits::Instruction<chip8::instructions::LDkeyPress>::execute(const chip8::instructions::LDkeyPress& instruction, chip8::Chip8& chip8) -> void {
    for (std::size_t key = 0x0; key < chip8::KEYBOARD_SIZE; ++key) {
        if (chip8::get_key(chip8.keyboard, key) && !chip8::get_key(chip8.previous_keyboard, key)) {
            chip8.general_purpose_registers[instruction.vx] = key;
            chip8.program_counter += 0x02;

            break;
        }
    }   
};

auto chip8::traits::Instruction<chip8::instructions::LDkeyPress>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDkeyPress> {
    if ((ic & 0xF0FF) == 0xF00A) return chip8::instructions::LDkeyPress{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LDkeyPress>::encode(const chip8::instructions::LDkeyPress& instruction) -> chip8::InstructionCode {
    return 0xF00A | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8);
};







auto chip8::traits::Display<chip8::instructions::LDgetDelay>::display(const chip8::instructions::LDgetDelay& instruction) -> std::string {
    std::ostringstream ss;
    ss << "LD   V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "DT";
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::LDgetDelay>::execute(const chip8::instructions::LDgetDelay& instruction, chip8::Chip8& chip8) -> void {
    chip8.general_purpose_registers[instruction.vx] = chip8.delay_timer;
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::LDgetDelay>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDgetDelay> {
    if ((ic & 0xF0FF) == 0xF007) return chip8::instructions::LDgetDelay{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LDgetDelay>::encode(const chip8::instructions::LDgetDelay& instruction) -> chip8::InstructionCode {
    return 0xF007 | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8);
};







auto chip8::traits::Display<chip8::instructions::LDsetDelay>::display(const chip8::instructions::LDsetDelay& instruction) -> std::string {
    std::ostringstream ss;
    ss << "LD   DT, ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::LDsetDelay>::execute(const chip8::instructions::LDsetDelay& instruction, chip8::Chip8& chip8) -> void {
    chip8.delay_timer = chip8.general_purpose_registers[instruction.vx];
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::LDsetDelay>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDsetDelay> {
    if ((ic & 0xF0FF) == 0xF015) return chip8::instructions::LDsetDelay{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LDsetDelay>::encode(const chip8::instructions::LDsetDelay& instruction) -> chip8::InstructionCode {
    return 0xF015 | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8);
};







auto chip8::traits::Display<chip8::instructions::LDsetSound>::display(const chip8::instructions::LDsetSound& instruction) -> std::string {
    std::ostringstream ss;
    ss << "LD   ST, ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::LDsetSound>::execute(const chip8::instructions::LDsetSound& instruction, chip8::Chip8& chip8) -> void {
    chip8.sound_timer = chip8.general_purpose_registers[instruction.vx];
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::LDsetSound>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDsetSound> {
    if ((ic & 0xF0FF) == 0xF018) return chip8::instructions::LDsetSound{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LDsetSound>::encode(const chip8::instructions::LDsetSound& instruction) -> chip8::InstructionCode {
    return 0xF018 | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8);
};







auto chip8::traits::Display<chip8::instructions::LDsprite>::display(const chip8::instructions::LDsprite& instruction) -> std::string {
    std::ostringstream ss;
    ss << "LD   F, ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::LDsprite>::execute(const chip8::instructions::LDsprite& instruction, chip8::Chip8& chip8) -> void {
    chip8.address_register = chip8.general_purpose_registers[instruction.vx] * 5u;
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::LDsprite>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDsprite> {
    if ((ic & 0xF0FF) == 0xF029) return chip8::instructions::LDsprite{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LDsprite>::encode(const chip8::instructions::LDsprite& instruction) -> chip8::InstructionCode {
    return 0xF029 | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8);
};







auto chip8::traits::Display<chip8::instructions::LDbcd>::display(const chip8::instructions::LDbcd& instruction) -> std::string {
    std::ostringstream ss;
    ss << "LD   B, ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::LDbcd>::execute(const chip8::instructions::LDbcd& instruction, chip8::Chip8& chip8) -> void {
    chip8.memory[chip8.address_register + 0x00] = chip8.general_purpose_registers[instruction.vx] / 100u;
    chip8.memory[chip8.address_register + 0x01] = (chip8.general_purpose_registers[instruction.vx] / 10u) % 10u;
    chip8.memory[chip8.address_register + 0x02] = chip8.general_purpose_registers[instruction.vx] % 10u;
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::LDbcd>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDbcd> {
    if ((ic & 0xF0FF) == 0xF033) return chip8::instructions::LDbcd{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LDbcd>::encode(const chip8::instructions::LDbcd& instruction) -> chip8::InstructionCode {
    return 0xF033 | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8);
};







auto chip8::traits::Display<chip8::instructions::LDstore>::display(const chip8::instructions::LDstore& instruction) -> std::string {
    std::ostringstream ss;
    ss << "LD   [I], ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::LDstore>::execute(const chip8::instructions::LDstore& instruction, chip8::Chip8& chip8) -> void {
    for (std::size_t i = 0u; i <= instruction.vx; ++i) {
        chip8.memory[chip8.address_register + i] = chip8.general_purpose_registers[i];
    }

    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::LDstore>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDstore> {
    if ((ic & 0xF0FF) == 0xF055) return chip8::instructions::LDstore{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LDstore>::encode(const chip8::instructions::LDstore& instruction) -> chip8::InstructionCode {
    return 0xF055 | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8);
};







auto chip8::traits::Display<chip8::instructions::LDread>::display(const chip8::instructions::LDread& instruction) -> std::string {
    std::ostringstream ss;
    ss << "LD   V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", [I]";
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::LDread>::execute(const chip8::instructions::LDread& instruction, chip8::Chip8& chip8) -> void {
    for (std::size_t i = 0u; i <= instruction.vx; ++i) {
        chip8.general_purpose_registers[i] = chip8.memory[chip8.address_register + i];
    }

    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::LDread>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDread> {
    if ((ic & 0xF0FF) == 0xF065) return chip8::instructions::LDread{
        .vx = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08)
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LDread>::encode(const chip8::instructions::LDread& instruction) -> chip8::InstructionCode {
    return 0xF065 | ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8);
};







auto chip8::traits::Display<chip8::instructions::LDaddress>::display(const chip8::instructions::LDaddress& instruction) -> std::string {
    std::ostringstream ss;
    ss << "LD   I, ";
    ss << "0x" << std::setfill('0') << std::setw(3) << std::uppercase << std::hex << instruction.address;
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::LDaddress>::execute(const chip8::instructions::LDaddress& instruction, chip8::Chip8& chip8) -> void {
    chip8.address_register = instruction.address;
    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::LDaddress>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LDaddress> {
    if ((ic & 0xF000) == 0xA000) return chip8::instructions::LDaddress{
        .address = static_cast<Address>((ic & 0x0FFF))
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LDaddress>::encode(const chip8::instructions::LDaddress& instruction) -> chip8::InstructionCode {
    return 0xA000 | (instruction.address & 0x0FFF);
};







auto chip8::traits::Display<chip8::instructions::LD>::display(const chip8::instructions::LD& instruction) -> std::string {
    return std::visit([](auto&& v) -> std::string { return chip8::display(v); }, instruction);
};

auto chip8::traits::Instruction<chip8::instructions::LD>::execute(const chip8::instructions::LD& instruction, chip8::Chip8& chip8) -> void {
    std::visit([&chip8](auto&& v) -> void { return chip8::execute(v, chip8); }, instruction);
};

auto chip8::traits::Instruction<chip8::instructions::LD>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::LD> {
    if      (auto ld_byte      = chip8::decode<chip8::instructions::LDbyte>    (ic)) return chip8::instructions::LD(     ld_byte.value());
    else if (auto ld_register  = chip8::decode<chip8::instructions::LDregister>(ic)) return chip8::instructions::LD( ld_register.value());
    else if (auto ld_getdelay  = chip8::decode<chip8::instructions::LDgetDelay>(ic)) return chip8::instructions::LD( ld_getdelay.value());
    else if (auto ld_keypress  = chip8::decode<chip8::instructions::LDkeyPress>(ic)) return chip8::instructions::LD( ld_keypress.value());
    else if (auto ld_set_delay = chip8::decode<chip8::instructions::LDsetDelay>(ic)) return chip8::instructions::LD(ld_set_delay.value());
    else if (auto ld_set_sound = chip8::decode<chip8::instructions::LDsetSound>(ic)) return chip8::instructions::LD(ld_set_sound.value());
    else if (auto ld_sprite    = chip8::decode<chip8::instructions::LDsprite>  (ic)) return chip8::instructions::LD(   ld_sprite.value());
    else if (auto ld_bcd       = chip8::decode<chip8::instructions::LDbcd>     (ic)) return chip8::instructions::LD(      ld_bcd.value());
    else if (auto ld_store     = chip8::decode<chip8::instructions::LDstore>   (ic)) return chip8::instructions::LD(    ld_store.value());
    else if (auto ld_read      = chip8::decode<chip8::instructions::LDread>    (ic)) return chip8::instructions::LD(     ld_read.value());
    else if (auto ld_address   = chip8::decode<chip8::instructions::LDaddress> (ic)) return chip8::instructions::LD(  ld_address.value());
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::LD>::encode(const chip8::instructions::LD& instruction) -> chip8::InstructionCode {
    return std::visit([](auto&& v) -> chip8::InstructionCode { return chip8::encode(v); }, instruction);
};