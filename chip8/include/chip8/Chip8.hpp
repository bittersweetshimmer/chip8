#pragma once
#include <filesystem>
#include <optional>
#include <chip8/Aliases/Memory.hpp>
#include <chip8/Aliases/Display.hpp>
#include <chip8/Aliases/Stack.hpp>
#include <chip8/Aliases/Keyboard.hpp>
#include <chip8/Aliases/Address.hpp>
#include <chip8/Aliases/GeneralPurposeRegisters.hpp>
#include <chip8/Aliases/InstructionCode.hpp>
#include <chip8/Aliases/ByteCode.hpp>
#include <chip8/RNG.hpp>

namespace chip8 {
    constexpr chip8::Address INITIAL_PROGRAM_COUNTER = 0x200;

    struct Chip8 {
        chip8::Memory memory = chip8::Memory{};
        chip8::Display display = chip8::Display{};
        chip8::Keyboard keyboard = chip8::Keyboard{};
        chip8::Keyboard previous_keyboard = chip8::Keyboard{};

        chip8::GPRegisters general_purpose_registers;

        chip8::Address address_register = 0x0;
        chip8::Address program_counter = 0x0;

        chip8::Byte stack_pointer = 0x0;
        chip8::Stack stack = chip8::Stack{};

        chip8::Byte delay_timer = 0x0;
        chip8::Byte sound_timer = 0x0;

        chip8::RNG rng = chip8::RNG{};
    };

    auto fetch(const Chip8& chip8) -> chip8::InstructionCode;
    auto initialize(chip8::ByteCode&& bytecode, unsigned int seed = 1u) -> chip8::Chip8;
    auto read_file(const std::filesystem::path& path) -> std::optional<chip8::ByteCode>;
}