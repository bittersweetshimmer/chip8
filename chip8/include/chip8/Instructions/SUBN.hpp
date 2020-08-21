#pragma once
#include <chip8/Aliases/GeneralPurposeRegister.hpp>
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    8xy7 - SUBN Vx, Vy
    Set Vx = Vy - Vx, set VF = NOT borrow.

    If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
    */
    struct SUBN {
        chip8::GPRegister vx;
        chip8::GPRegister vy;
    };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::SUBN> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SUBN&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SUBN> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SUBN&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SUBN>;
        static auto encode(const chip8::instructions::SUBN&) -> chip8::InstructionCode;
    };
}