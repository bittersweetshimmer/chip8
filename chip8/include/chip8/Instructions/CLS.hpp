#pragma once
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    00E0 - CLS

    Clear the display.
    */
    struct CLS {};
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::CLS> : chip8::traits::Impl {
        static auto display(const chip8::instructions::CLS&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::CLS> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::CLS&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::CLS>;
        static auto encode(const chip8::instructions::CLS&) -> chip8::InstructionCode;
    };
}