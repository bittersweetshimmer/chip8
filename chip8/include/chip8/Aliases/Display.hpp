#pragma once
#include <array>
#include <chip8/Aliases/Byte.hpp>

namespace chip8 {
    constexpr std::size_t DISPLAY_WIDTH = 0x40;
    constexpr std::size_t DISPLAY_HEIGHT = 0x20;
    constexpr std::size_t DISPLAY_SIZE = DISPLAY_WIDTH * DISPLAY_HEIGHT;

    using Display = std::array<chip8::Byte, DISPLAY_SIZE>;
}