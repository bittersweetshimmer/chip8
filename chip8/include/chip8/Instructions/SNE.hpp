#pragma once
#include <variant>
#include <chip8/Aliases/GeneralPurposeRegister.hpp>
#include <chip8/Aliases/Byte.hpp>
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    4xkk - SNE Vx, byte

    Skip next instruction if Vx != kk.

    The interpreter compares register Vx to kk, and if they are not equal, increments the program counter by 2.
    */
    struct SNEbyte {
        chip8::GPRegister vx;
        chip8::Byte byte;
    };

    /*
    9xy0 - SNE Vx, Vy

    Skip next instruction if Vx != Vy.

    The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
    */
    struct SNEregister {
        GPRegister vx;
        GPRegister vy;
    };


    using SNE = std::variant<SNEbyte, SNEregister>;
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::SNEbyte> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SNEbyte&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SNEbyte> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SNEbyte&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SNEbyte>;
        static auto encode(const chip8::instructions::SNEbyte&) -> chip8::InstructionCode;
    };



    template<>
    struct Display<chip8::instructions::SNEregister> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SNEregister&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SNEregister> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SNEregister&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SNEregister>;
        static auto encode(const chip8::instructions::SNEregister&) -> chip8::InstructionCode;
    };



    template<>
    struct Display<chip8::instructions::SNE> : chip8::traits::Impl {
        static auto display(const chip8::instructions::SNE&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::SNE> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::SNE&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::SNE>;
        static auto encode(const chip8::instructions::SNE&) -> chip8::InstructionCode;
    };
}