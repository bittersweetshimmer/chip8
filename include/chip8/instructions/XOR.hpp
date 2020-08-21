#include <chip8/aliases/GeneralPurposeRegister.hpp>
#pragma once
#include <chip8/traits/Display.hpp>
#include <chip8/traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    8xy3 - XOR Vx, Vy

    Set Vx = Vx XOR Vy.

    Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corrseponding bits from two values, and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0.
    */
    struct XOR {
        chip8::GPRegister vx;
        chip8::GPRegister vy;
    };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::XOR> : chip8::traits::Impl {
        static auto display(const chip8::instructions::XOR&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::XOR> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::XOR&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::XOR>;
        static auto encode(const chip8::instructions::XOR&) -> chip8::InstructionCode;
    };
}