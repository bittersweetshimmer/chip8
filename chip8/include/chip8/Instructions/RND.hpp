#pragma once
#include <chip8/Aliases/GeneralPurposeRegister.hpp>
#include <chip8/Aliases/Byte.hpp>
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    Cxkk - RND Vx, byte

    Set Vx = random byte AND kk.

    The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND.
    */
    struct RND {
        chip8::GPRegister vx;
        chip8::Byte byte;
    };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::RND> : chip8::traits::Impl {
        static auto display(const chip8::instructions::RND&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::RND> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::RND&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::RND>;
        static auto encode(const chip8::instructions::RND&) -> chip8::InstructionCode;
    };
}