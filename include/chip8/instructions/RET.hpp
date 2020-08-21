#pragma once
#include <chip8/traits/Display.hpp>
#include <chip8/traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    00EE - RET

    Return from a subroutine.

    The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
    */
    struct RET {};
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::RET> : chip8::traits::Impl {
        static auto display(const chip8::instructions::RET&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::RET> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::RET&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::RET>;
        static auto encode(const chip8::instructions::RET&) -> chip8::InstructionCode;
    };
}