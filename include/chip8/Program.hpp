#pragma once
#include <vector>
#include <optional>
#include <filesystem>
#include <chip8/Instruction.hpp>

namespace chip8 {
    using Program = std::vector<chip8::Instruction>;
    using ByteCode = std::vector<chip8::Byte>;

    auto compile(const Program& program) -> ByteCode;
    auto decompile(const ByteCode& program) -> std::optional<Program>;
    auto read_file(const std::filesystem::path& path) -> std::optional<ByteCode>;
}