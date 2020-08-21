#pragma once
#include <chip8/aliases/GeneralPurposeRegister.hpp>
#include <chip8/traits/Display.hpp>
#include <chip8/traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    8xy5 - SUB Vx, Vy

    Set Vx = Vx - Vy, set VF = NOT borrow.

    If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
    */
    struct SUB {
        chip8::GPRegister vx;
        chip8::GPRegister vy;
    };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::SUB> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SUB&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SUB> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SUB&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SUB>;
        static auto encode(const chip8::instructions::SUB&) -> chip8::InstructionCode;
    };
}