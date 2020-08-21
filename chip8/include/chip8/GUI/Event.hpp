#pragma once
#include <variant>
#include <chip8/GUI/Events/KeyEvent.hpp>
#include <chip8/GUI/Events/DropFileEvent.hpp>
#include <chip8/GUI/Events/WindowResizeEvent.hpp>

namespace chip8::gui {
    using Event = std::variant<
        chip8::gui::ev::KeyEvent,
        chip8::gui::ev::DropFileEvent,
        chip8::gui::ev::WindowResizeEvent
    >;
}