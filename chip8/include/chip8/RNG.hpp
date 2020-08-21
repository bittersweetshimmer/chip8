#pragma once
#include <random>
#include <chip8/Aliases/Byte.hpp>

namespace chip8 {
    struct RNG {
    public:
        auto next() -> chip8::Byte;

        std::default_random_engine engine;
        std::uniform_int_distribution<int> distribution;
    };
}