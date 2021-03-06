#include <iomanip>
#include <sstream>
#include <chip8/Instructions/DRW.hpp>

auto chip8::traits::Display<chip8::instructions::DRW>::display(const chip8::instructions::DRW& instruction) -> std::string {
    std::ostringstream ss;
    ss << "DRW  V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vx) << ", ";
    ss << "V" << std::uppercase << std::hex << static_cast<std::size_t>(instruction.vy) << ", ";
    ss << static_cast<std::size_t>(instruction.nibble);
    return ss.str();
};

auto chip8::traits::Instruction<chip8::instructions::DRW>::execute(const chip8::instructions::DRW& instruction, chip8::Chip8& chip8) -> void {
    chip8.general_purpose_registers[0xF] = 0x00;

    for (std::size_t height = 0u; height < instruction.nibble; ++height) {
        const auto offset_y = (chip8.general_purpose_registers[instruction.vy] + height) * chip8::DISPLAY_WIDTH;

        chip8::Byte byte = chip8.memory[chip8.address_register + height];

        for (std::size_t bit = 0u; bit < 0x08; ++bit) {
            const auto offset_x = chip8.general_purpose_registers[instruction.vx] + bit;
            const auto offset = offset_y + offset_x;

            const auto previous = chip8.display[offset % chip8::DISPLAY_SIZE];

            chip8.display[offset % chip8::DISPLAY_SIZE] ^= (0xFF * ((byte >> (7u - bit)) & 0b1));

            if ((previous != 0x00) && (chip8.display[offset % chip8::DISPLAY_SIZE] != previous)) {
                chip8.general_purpose_registers[0xF] = 0x01;
            }
        }
    }

    chip8.program_counter += 0x02;
};

auto chip8::traits::Instruction<chip8::instructions::DRW>::decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::DRW> {
    if ((ic & 0xF000) == 0xD000) return chip8::instructions::DRW{
        .vx     = static_cast<chip8::GPRegister>(((ic & 0x0F00)) >> 0x08),
        .vy     = static_cast<chip8::GPRegister>(((ic & 0x00F0)) >> 0x04),
        .nibble = static_cast<chip8::Byte>((ic & 0x000F))
    };
    else return std::nullopt;
};

auto chip8::traits::Instruction<chip8::instructions::DRW>::encode(const chip8::instructions::DRW& instruction) -> chip8::InstructionCode {
    return 0xD000 | 
        ((static_cast<chip8::InstructionCode>(instruction.vx) & 0x000F) << 8) |
        ((static_cast<chip8::InstructionCode>(instruction.vy) & 0x000F) << 4) |
        instruction.nibble;
};