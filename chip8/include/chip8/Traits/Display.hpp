#pragma once
#include <string>
#include <chip8/Traits/Trait.hpp>

namespace chip8 {
    namespace traits {
        template<typename T>
        struct Display : Trait {
            static auto display(const T&) -> std::string = delete;
        };
    }

    template<typename T>
    inline auto display(const T& t) -> std::string requires traits::Instance<traits::Display, T> { return traits::Display<T>::display(t); } 
}