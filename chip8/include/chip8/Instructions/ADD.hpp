#pragma once
#include <variant>
#include <chip8/Aliases/GeneralPurposeRegister.hpp>
#include <chip8/Aliases/Byte.hpp>
#include <chip8/Traits/Display.hpp>
#include <chip8/Traits/Instruction.hpp>

namespace chip8::instructions {
    /*
    7xkk - ADD Vx, byte
    Set Vx = Vx + kk.

    Adds the value kk to the value of register Vx, then stores the result in Vx.
    */
    struct ADDbyte {
        chip8::GPRegister vx;
        chip8::Byte byte;
    };

    /*
    Set Vx = Vx + Vy, set VF = carry.

    The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in Vx.
    */
    struct ADDregister {
        chip8::GPRegister vx;
        chip8::GPRegister vy;
    };

    /*
    Fx1E - ADD I, Vx

    Set I = I + Vx.

    The values of I and Vx are added, and the results are stored in I.
    */
    struct ADDaddress {
        chip8::GPRegister vx;
    };

    using ADD = std::variant<ADDbyte, ADDregister, ADDaddress>;
}

namespace chip8::traits {
    template<>
    struct Display<chip8::instructions::ADDbyte> : chip8::traits::Impl {
        static auto display(const chip8::instructions::ADDbyte&) -> std::string;
    };

    template<>
    struct Display<chip8::instructions::ADDregister> : chip8::traits::Impl {
        static auto display(const chip8::instructions::ADDregister&) -> std::string;
    };

    template<>
    struct Display<chip8::instructions::ADDaddress> : chip8::traits::Impl {
        static auto display(const chip8::instructions::ADDaddress&) -> std::string;
    };

    template<>
    struct Display<chip8::instructions::ADD> : chip8::traits::Impl {
        static auto display(const chip8::instructions::ADD&) -> std::string;
    };

    template<>
    struct Instruction<chip8::instructions::ADDbyte> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::ADDbyte&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::ADDbyte>;
        static auto encode(const chip8::instructions::ADDbyte&) -> chip8::InstructionCode;
    };

    template<>
    struct Instruction<chip8::instructions::ADDregister> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::ADDregister&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::ADDregister>;
        static auto encode(const chip8::instructions::ADDregister&) -> chip8::InstructionCode;
    };

    template<>
    struct Instruction<chip8::instructions::ADDaddress> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::ADDaddress&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::ADDaddress>;
        static auto encode(const chip8::instructions::ADDaddress&) -> chip8::InstructionCode;
    };

    template<>
    struct Instruction<chip8::instructions::ADD> : chip8::traits::Impl {
        static auto execute(const chip8::instructions::ADD&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> std::optional<chip8::instructions::ADD>;
        static auto encode(const chip8::instructions::ADD&) -> chip8::InstructionCode;
    };
}