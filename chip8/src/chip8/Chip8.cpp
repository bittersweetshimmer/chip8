#include <fstream>
#include <chip8/Chip8.hpp>
#include <chip8/Sprites/Characters.hpp>

auto chip8::fetch(const chip8::Chip8& chip8) -> chip8::InstructionCode {
    chip8::InstructionCode ic = 0x0000;
    ic |= chip8.memory[chip8.program_counter + 0x00] << 0x08;
    ic |= chip8.memory[chip8.program_counter + 0x01] << 0x00;
    return ic;
}

auto chip8::initialize(chip8::ByteCode&& bytecode, unsigned int seed) -> chip8::Chip8 {
    chip8::Chip8 chip8;
    chip8.rng.engine.seed(seed);
    chip8.program_counter = chip8::INITIAL_PROGRAM_COUNTER;
    chip8::load(chip8.memory, chip8::sprites::CHARACTERS, 0x000);
    chip8::load(chip8.memory, std::move(bytecode), chip8::INITIAL_PROGRAM_COUNTER);

    return chip8;
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