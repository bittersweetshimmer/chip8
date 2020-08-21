#pragma once
#include <chip8/Aliases/GeneralPurposeRegister.hpp>
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    8xy1 - OR Vx, Vy

    Set Vx = Vx OR Vy.

    Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corrseponding bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
    */
    struct OR {
        chip8::GPRegister vx;
        chip8::GPRegister vy;
    };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::OR> : chip8::traits::Impl {
        static auto display(const chip8::instructions::OR&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::OR> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::OR&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::OR>;
        static auto encode(const chip8::instructions::OR&) -> chip8::InstructionCode;
    };
}