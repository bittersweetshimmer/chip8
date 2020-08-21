#pragma once
#include <array>
#include <span>
#include <chip8/aliases/Byte.hpp>

namespace chip8 {
    constexpr std::size_t MEMORY_SIZE = 0x1000;

    using Memory = std::array<chip8::Byte, MEMORY_SIZE>;

    template<typename T>
    constexpr auto load(Memory& memory, T src, std::size_t offset) -> void {
        auto bytes = std::as_bytes(std::span(src)); 
        for (std::size_t i = 0u; i < bytes.size(); ++i) {
            memory[i + offset] = static_cast<chip8::Byte>(bytes[i]);
        }
    }
}