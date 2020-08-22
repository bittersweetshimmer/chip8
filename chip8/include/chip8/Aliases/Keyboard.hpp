#pragma once
#include <array>
#include <cstdint>

namespace chip8 {
    constexpr std::size_t KEYBOARD_SIZE = 0x10;

    using Keyboard = std::uint16_t;

    constexpr auto set_key(Keyboard& keyboard, chip8::Byte key, bool flag) -> void {
        keyboard = (keyboard & ~(0b1 << key)) | (flag << key); 
    }

    constexpr auto get_key(const Keyboard& keyboard, chip8::Byte key) -> bool {
        return (keyboard >> key) & 0b1;
    }
}