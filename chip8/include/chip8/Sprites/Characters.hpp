#pragma once
#include <chip8/Aliases/Sprite.hpp>

namespace chip8::sprites {
    constexpr std::size_t CHARACTER_HEIGHT = 5u;
    using CharacterSprite = Sprite<CHARACTER_HEIGHT>;

    constexpr auto CHAR_0 = CharacterSprite{ 0xF0, 0x90, 0x90, 0x90, 0xF0 };
    constexpr auto CHAR_1 = CharacterSprite{ 0x20, 0x60, 0x20, 0x20, 0x70 };
    constexpr auto CHAR_2 = CharacterSprite{ 0xF0, 0x10, 0xF0, 0x80, 0xF0 };
    constexpr auto CHAR_3 = CharacterSprite{ 0xF0, 0x10, 0xF0, 0x10, 0xF0 };
    constexpr auto CHAR_4 = CharacterSprite{ 0x90, 0x90, 0xF0, 0x10, 0x10 };
    constexpr auto CHAR_5 = CharacterSprite{ 0xF0, 0x80, 0xF0, 0x10, 0xF0 };
    constexpr auto CHAR_6 = CharacterSprite{ 0xF0, 0x80, 0xF0, 0x90, 0xF0 };
    constexpr auto CHAR_7 = CharacterSprite{ 0xF0, 0x10, 0x20, 0x40, 0x40 };
    constexpr auto CHAR_8 = CharacterSprite{ 0xF0, 0x90, 0xF0, 0x90, 0xF0 };
    constexpr auto CHAR_9 = CharacterSprite{ 0xF0, 0x90, 0xF0, 0x10, 0xF0 };
    constexpr auto CHAR_A = CharacterSprite{ 0xF0, 0x90, 0xF0, 0x90, 0x90 };
    constexpr auto CHAR_B = CharacterSprite{ 0xE0, 0x90, 0xE0, 0x90, 0xE0 };
    constexpr auto CHAR_C = CharacterSprite{ 0xF0, 0x80, 0x80, 0x80, 0xF0 };
    constexpr auto CHAR_D = CharacterSprite{ 0xE0, 0x90, 0x90, 0x90, 0xE0 };
    constexpr auto CHAR_E = CharacterSprite{ 0xF0, 0x80, 0xF0, 0x80, 0xF0 };
    constexpr auto CHAR_F = CharacterSprite{ 0xF0, 0x80, 0xF0, 0x80, 0x80 };

    constexpr auto CHARACTERS = std::array<CharacterSprite, 0x10>{
        CHAR_0, CHAR_1, CHAR_2, CHAR_3,
        CHAR_4, CHAR_5, CHAR_6, CHAR_7,
        CHAR_8, CHAR_9, CHAR_A, CHAR_B,
        CHAR_C, CHAR_D, CHAR_E, CHAR_F
    };
}