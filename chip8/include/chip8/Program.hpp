#pragma once
#include <vector>
#include <optional>
#include <filesystem>
#include <chip8/Instruction.hpp>
#include <chip8/Aliases/ByteCode.hpp>

namespace chip8 {
    using Program = ::std::vector<chip8::Instruction>;

    auto compile(const chip8::Program& program) -> chip8::ByteCode;
    auto decompile(const chip8::ByteCode& program) -> std::optional<chip8::Program>;
}