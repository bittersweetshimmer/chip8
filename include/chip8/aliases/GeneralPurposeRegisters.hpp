#pragma once
#include <array>
#include <chip8/aliases/Byte.hpp>

namespace chip8 {
    constexpr std::size_t GENERAL_PURPOSE_REGISTERS_SIZE = 0x10;

    using GPRegisters = std::array<chip8::Byte, GENERAL_PURPOSE_REGISTERS_SIZE>;
}