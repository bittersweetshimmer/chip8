#pragma once
#include <chip8/aliases/GeneralPurposeRegister.hpp>
#include <chip8/traits/Display.hpp>
#include <chip8/traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    8xy6 - SHR Vx {, Vy}

    Set Vx = Vx SHR 1.

    If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2.
    */
    struct SHR {
        chip8::GPRegister vx;
        chip8::GPRegister vy;
    };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::SHR> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SHR&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SHR> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SHR&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SHR>;
        static auto encode(const chip8::instructions::SHR&) -> chip8::InstructionCode;
    };
}