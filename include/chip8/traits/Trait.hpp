#pragma once

namespace chip8::traits {
    struct Trait {
        constexpr static bool is_instance = false;
    };

    struct Impl {
        constexpr static bool is_instance = true;
    };

    template<template<typename> typename TraitT, typename T>
    concept Instance = TraitT<T>::is_instance;
}