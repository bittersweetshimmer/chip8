#pragma once
#include <variant>
#include <chip8/Aliases/GeneralPurposeRegister.hpp>
#include <chip8/Aliases/Byte.hpp>
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    3xkk - SE Vx, byte

    Skip next instruction if Vx = kk.

    The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2.
    */
    struct SEbyte {
        chip8::GPRegister vx;
        chip8::Byte byte;
    };

    /*
    5xy0 - SE Vx, Vy

    Skip next instruction if Vx = Vy.

    The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
    */
    struct SEregister {
        chip8::GPRegister vx;
        chip8::GPRegister vy;
    };


    using SE = std::variant<SEbyte, SEregister>;
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::SEbyte> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SEbyte&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SEbyte> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SEbyte&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SEbyte>;
        static auto encode(const chip8::instructions::SEbyte&) -> chip8::InstructionCode;
    };



    template<>
    struct Display<chip8::instructions::SEregister> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SEregister&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SEregister> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SEregister&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SEregister>;
        static auto encode(const chip8::instructions::SEregister&) -> chip8::InstructionCode;
    };



    template<>
    struct Display<chip8::instructions::SE> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SE&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SE> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SE&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SE>;
        static auto encode(const chip8::instructions::SE&) -> chip8::InstructionCode;
    };
}