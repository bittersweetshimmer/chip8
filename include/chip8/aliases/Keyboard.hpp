#pragma once
#include <array>
#include <cstdint>

namespace chip8 {
    constexpr std::size_t KEYBOARD_SIZE = 0x10;

    using Keyboard = std::array<bool, KEYBOARD_SIZE>;
}