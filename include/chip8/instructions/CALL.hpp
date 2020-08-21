#pragma once
#include <chip8/aliases/Address.hpp>
#include <chip8/traits/Display.hpp>
#include <chip8/traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    2nnn - CALL addr

    Call subroutine at nnn.

    The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn.
    */
    struct CALL { chip8::Address address; };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::CALL> : chip8::traits::Impl {
        static auto display(const chip8::instructions::CALL&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::CALL> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::CALL&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::CALL>;
        static auto encode(const chip8::instructions::CALL&) -> chip8::InstructionCode;
    };
}