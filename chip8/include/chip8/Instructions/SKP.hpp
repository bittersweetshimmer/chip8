#pragma once
#include <chip8/Aliases/GeneralPurposeRegister.hpp>
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    Ex9E - SKP Vx
    
    Skip next instruction if key with the value of Vx is pressed.

    Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
    */
    struct SKP {
        chip8::GPRegister vx;
    };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::SKP> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SKP&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SKP> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SKP&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SKP>;
        static auto encode(const chip8::instructions::SKP&) -> chip8::InstructionCode;
    };
}