#pragma once
#include <chip8/aliases/Memory.hpp>
#include <chip8/aliases/Display.hpp>
#include <chip8/aliases/Stack.hpp>
#include <chip8/aliases/Keyboard.hpp>
#include <chip8/aliases/Address.hpp>
#include <chip8/aliases/GeneralPurposeRegisters.hpp>
#include <chip8/aliases/InstructionCode.hpp>
#include <chip8/sprites/characters.hpp>
#include <chip8/RNG.hpp>

namespace chip8 {
    constexpr chip8::Address INITIAL_ADDRESS_REGISTER = 0x0;
    constexpr chip8::Address INITIAL_PROGRAM_COUNTER = 0x200;

    struct Chip8 {
        chip8::Memory memory = chip8::Memory{};
        chip8::Display display = chip8::Display{};
        chip8::Keyboard keyboard = chip8::Keyboard{};

        chip8::GPRegisters general_purpose_registers;

        chip8::Address address_register = INITIAL_ADDRESS_REGISTER;
        chip8::Address program_counter = INITIAL_PROGRAM_COUNTER;

        chip8::Byte stack_pointer = 0x0;
        chip8::Stack stack;

        chip8::Byte delay_timer = 0x0;
        chip8::Byte sound_timer = 0x0;

        chip8::RNG rng = chip8::RNG{};
    };

    auto fetch(const Chip8& chip8) -> chip8::InstructionCode;
}