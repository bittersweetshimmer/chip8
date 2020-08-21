#pragma once
#include <chip8/aliases/GeneralPurposeRegister.hpp>
#include <chip8/traits/Display.hpp>
#include <chip8/traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    8xy2 - AND Vx, Vy

    Set Vx = Vx AND Vy.

    Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corrseponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.
    */
    struct AND {
        chip8::GPRegister vx;
        chip8::GPRegister vy;
    };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::AND> : chip8::traits::Impl {
        static auto display(const chip8::instructions::AND&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::AND> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::AND&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::AND>;
        static auto encode(const chip8::instructions::AND&) -> chip8::InstructionCode;
    };
}