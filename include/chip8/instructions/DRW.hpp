#pragma once
#include <chip8/aliases/GeneralPurposeRegister.hpp>
#include <chip8/aliases/Byte.hpp>
#include <chip8/traits/Display.hpp>
#include <chip8/traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    Dxyn - DRW Vx, Vy, nibble

    Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.

    The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR, and section 2.4, Display, for more information on the Chip-8 screen and sprites.
    */
    struct DRW {
        chip8::GPRegister vx;
        chip8::GPRegister vy;
        chip8::Byte nibble;
    };
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::DRW> : chip8::traits::Impl {
        static auto display(const chip8::instructions::DRW&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::DRW> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::DRW&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::DRW>;
        static auto encode(const chip8::instructions::DRW&) -> chip8::InstructionCode;
    };
}