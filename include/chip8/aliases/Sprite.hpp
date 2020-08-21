#pragma once
#include <array>
#include <chip8/aliases/Byte.hpp>

namespace chip8 {
    template<std::size_t Height>
    using Sprite = std::array<chip8::Byte, Height>;
}