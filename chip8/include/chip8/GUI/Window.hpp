#pragma once

#include <optional>
#include <set>
#include <queue>

#include <gloomy/gloomy.hpp>
#include <GLFW/glfw3.h>

#include <chip8/GUI/TimeFrame.hpp>
#include <chip8/GUI/IO/Keyboard.hpp>
#include <chip8/GUI/Event.hpp>

namespace chip8::gui {
    struct Window {
        Window(int width, int height, const std::string& title);
        ~Window();

        Window(Window&&);
        Window& operator=(Window&&);

        auto init() -> bool;

        auto is_open() -> bool;
        auto close() -> void;
        auto poll_events() -> void;
        auto get_next_frame() -> chip8::gui::TimeFrame;
        auto get_event() -> std::optional<chip8::gui::Event>;
        auto display() -> void;

        using MutableHandle = GLFWwindow;
        using HandleDeleter = void(*)(GLFWwindow*);
		using HandlePtr = std::unique_ptr<MutableHandle, HandleDeleter>;

        HandlePtr handle;

        int width;
        int height;
        std::string title;

        chip8::gui::Time previous_time;
        std::set<chip8::gui::io::Key> input_buffer;
        std::queue<chip8::gui::Event> event_queue;

        bool init_success;
        bool focus;
    };
}