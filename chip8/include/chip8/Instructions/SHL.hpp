#pragma once
#include <chip8/Aliases/GeneralPurposeRegister.hpp>
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    8xyE - SHL Vx {, Vy}

    Set Vx = Vx SHL 1.

    If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
    */
    struct SHL {
        chip8::GPRegister vx;
        chip8::GPRegister vy;
    };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::SHL> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SHL&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SHL> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SHL&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SHL>;
        static auto encode(const chip8::instructions::SHL&) -> chip8::InstructionCode;
    };
}