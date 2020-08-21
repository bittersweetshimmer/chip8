#include <chip8/RNG.hpp>

auto chip8::RNG::next() -> chip8::Byte {
    return this->distribution(this->engine) % 0x100;
}