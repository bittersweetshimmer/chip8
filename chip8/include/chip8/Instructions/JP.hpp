#pragma once
#include <variant>
#include <chip8/Aliases/Address.hpp>
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    1nnn - JP addr

    Jump to location nnn.

    The interpreter sets the program counter to nnn.
    */
    struct JPabsolute { chip8::Address address; };

    /*
    Bnnn - JP V0, addr
    Jump to location nnn + V0.

    The program counter is set to nnn plus the value of V0.
    */
    struct JPoffset { chip8::Address offset; };


    using JP = std::variant<JPabsolute, JPoffset>;
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::JPabsolute> : chip8::traits::Impl {
        static auto display(const chip8::instructions::JPabsolute&) -> std::string;
    };

    template<>
    struct Display<chip8::instructions::JPoffset> : chip8::traits::Impl {
        static auto display(const chip8::instructions::JPoffset&) -> std::string;
    };

    template<>
    struct Display<chip8::instructions::JP> : chip8::traits::Impl {
        static auto display(const chip8::instructions::JP&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::JPabsolute> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::JPabsolute&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::JPabsolute>;
        static auto encode(const chip8::instructions::JPabsolute&) -> chip8::InstructionCode;
    };

    template<>
    struct Instruction<chip8::instructions::JPoffset> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::JPoffset&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::JPoffset>;
        static auto encode(const chip8::instructions::JPoffset&) -> chip8::InstructionCode;
    };

    template<>
    struct Instruction<chip8::instructions::JP> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::JP&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::JP>;
        static auto encode(const chip8::instructions::JP&) -> chip8::InstructionCode;
    };
}