#pragma once
#include <chip8/Aliases/Address.hpp>
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    0nnn - SYS addr
    
    Jump to a machine code routine at nnn.

    This instruction is only used on the old computers on which Chip-8 was originally implemented. It is ignored by modern interpreters.
    */
    struct SYS { chip8::Address address; };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::SYS> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SYS&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SYS> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SYS&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SYS>;
        static auto encode(const chip8::instructions::SYS&) -> chip8::InstructionCode;
    };
}