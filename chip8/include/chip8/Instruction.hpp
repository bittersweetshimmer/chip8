#pragma once
#include <chip8/Instructions/ADD.hpp>
#include <chip8/Instructions/AND.hpp>
#include <chip8/Instructions/CALL.hpp>
#include <chip8/Instructions/CLS.hpp>
#include <chip8/Instructions/DRW.hpp>
#include <chip8/Instructions/JP.hpp>
#include <chip8/Instructions/LD.hpp>
#include <chip8/Instructions/OR.hpp>
#include <chip8/Instructions/RET.hpp>
#include <chip8/Instructions/RND.hpp>
#include <chip8/Instructions/SE.hpp>
#include <chip8/Instructions/SHL.hpp>
#include <chip8/Instructions/SHR.hpp>
#include <chip8/Instructions/SKNP.hpp>
#include <chip8/Instructions/SKP.hpp>
#include <chip8/Instructions/SNE.hpp>
#include <chip8/Instructions/SUB.hpp>
#include <chip8/Instructions/SUBN.hpp>
#include <chip8/Instructions/XOR.hpp>
#include <chip8/Instructions/SYS.hpp>

#include <optional>
#include <chip8/Aliases/InstructionCode.hpp>
#include <chip8/Chip8.hpp>

#include <string>

namespace chip8 {
    using Instruction = ::std::variant<
        chip8::instructions::CLS,
        chip8::instructions::RET,
        chip8::instructions::JP,
        chip8::instructions::CALL,
        chip8::instructions::SE,
        chip8::instructions::SNE,
        chip8::instructions::LD,
        chip8::instructions::OR,
        chip8::instructions::AND,
        chip8::instructions::XOR,
        chip8::instructions::ADD,
        chip8::instructions::SUB,
        chip8::instructions::SHR,
        chip8::instructions::SUBN,
        chip8::instructions::SHL,
        chip8::instructions::RND,
        chip8::instructions::DRW,
        chip8::instructions::SKP,
        chip8::instructions::SKNP,
        chip8::instructions::SYS
    >;
}

namespace chip8::traits {
    template<>
    struct Display<chip8::Instruction> : chip8::traits::Impl {
        static auto display(const chip8::Instruction&) -> ::std::string;
    };

    template<>
    struct Instruction<chip8::Instruction> : chip8::traits::Impl {
        static auto execute(const chip8::Instruction&, chip8::Chip8& chip8) -> void;
        static auto decode(chip8::InstructionCode ic) -> ::std::optional<chip8::Instruction>;
        static auto encode(const chip8::Instruction&) -> chip8::InstructionCode;
    };
}