#pragma once
#include <string>
#include <optional>
#include <chip8/Traits/Trait.hpp>
#include <chip8/Chip8.hpp>
#include <chip8/Aliases/InstructionCode.hpp>

namespace chip8 {
    namespace traits {
        template<typename T>
        struct Instruction : Trait {
            static auto execute(const T&, chip8::Chip8& chip8) -> void = delete;
            static auto decode(chip8::InstructionCode ic) -> std::optional<T> = delete;
            static auto encode(const T&) -> chip8::InstructionCode = delete;
        };
    }

    template<typename T>
    inline auto execute(const T& t, chip8::Chip8& chip8) -> void requires traits::Instance<traits::Instruction, T> { traits::Instruction<T>::execute(t, chip8); } 
    
    template<typename T>
    inline auto decode(chip8::InstructionCode ic) -> std::optional<T> requires traits::Instance<traits::Instruction, T> { return traits::Instruction<T>::decode(ic); } 

    template<typename T>
    inline auto encode(const T& t) -> chip8::InstructionCode requires traits::Instance<traits::Instruction, T> { return traits::Instruction<T>::encode(t); } 
}