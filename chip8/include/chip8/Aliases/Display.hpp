#pragma once
#include <array>

namespace chip8 {
    constexpr std::size_t DISPLAY_WIDTH = 0x40;
    constexpr std::size_t DISPLAY_HEIGHT = 0x20;
    constexpr std::size_t DISPLAY_SIZE = DISPLAY_WIDTH * DISPLAY_HEIGHT;

    using Display = std::array<std::uint8_t, DISPLAY_SIZE>;
}