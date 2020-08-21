#pragma once
#include <array>
#include <cstdint>
#include <chip8/aliases/Address.hpp>

namespace chip8 {
    constexpr std::size_t STACK_SIZE = 0x10;

    using Stack = std::array<chip8::Address, 0x10>;
}