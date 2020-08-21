#include <iostream>
#include <iomanip>
#include <fstream>
#include <chip8/Program.hpp>

auto chip8::compile(const chip8::Program& program) -> chip8::ByteCode {
    chip8::ByteCode bytes;
    bytes.reserve(program.size() * 2u);

    for (const auto& instruction: program) {
        const auto opcode = chip8::encode(instruction);

        bytes.push_back((opcode & 0xFF00) >> 0x8);
        bytes.push_back((opcode & 0x00FF) >> 0x0);
    }

    return bytes;
}

auto chip8::decompile(const chip8::ByteCode& bytecode) -> std::optional<chip8::Program> {
    chip8::Program program;
    program.reserve(bytecode.size() / 2u);

    for (std::size_t i = 0; i < bytecode.size(); i += 2) {
        std::uint16_t opcode = 0x00;
        opcode |= bytecode[i + 0x01] << 0x08;
        opcode |= bytecode[i + 0x00] << 0x00;
        
        const auto maybe_instruction = chip8::decode<chip8::Instruction>(opcode);

        if (!maybe_instruction.has_value()) return std::nullopt;
        else program.emplace_back(maybe_instruction.value());
    }

    return program;
}

auto chip8::read_file(const std::filesystem::path& path) -> std::optional<chip8::ByteCode> {
    std::ifstream input_file(path, std::ios_base::binary);
    
    if (input_file.fail()) {
        return std::nullopt;
    }

    input_file.seekg(0, std::ios_base::end);
    const std::size_t input_length = input_file.tellg();
    input_file.seekg(0, std::ios_base::beg);

    chip8::ByteCode input;
    input.reserve(input_length);
    std::copy( 
        std::istreambuf_iterator<char>(input_file),
        std::istreambuf_iterator<char>(),
        std::back_inserter(input)
    );

    return input;
}