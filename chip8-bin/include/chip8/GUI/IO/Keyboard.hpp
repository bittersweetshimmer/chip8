#pragma once
#include <gloomy/gl.hpp>
#include <GLFW/glfw3.h>
#include <array>

namespace chip8::gui::io {
    enum class Key {
        UNKNOWN,
        SPACE,
        APOSTROPHE, /* ' */
        COMMA, /* , */
        MINUS, /* - */
        PERIOD, /* . */
        SLASH, /* / */
        KEY_0,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        SEMICOLON, /* ; */
        EQUAL, /* = */
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        LEFT_BRACKET, /* [ */
        BACKSLASH, /* \ */
        RIGHT_BRACKET, /* ] */
        ACCENT, /* ` */
        N1, /* non-US #1 */
        N2, /* non-US #2 */
        ESCAPE,
        ENTER,
        TAB,
        BACKSPACE,
        INSERT,
        DEL,
        RIGHT,
        LEFT,
        DOWN,
        UP,
        PAGE_UP,
        PAGE_DOWN,
        HOME,
        END,
        CAPS_LOCK,
        SCROLL_LOCK,
        NUM_LOCK,
        PRINT_SCREEN,
        PAUSE,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        F25,
        NUM_0,
        NUM_1,
        NUM_2,
        NUM_3,
        NUM_4,
        NUM_5,
        NUM_6,
        NUM_7,
        NUM_8,
        NUM_9,
        DECIMAL,
        DIVIDE,
        MULTIPLY,
        SUBTRACT,
        ADD,
        NUM_ENTER,
        NUM_EQUAL,
        LEFT_SHIFT,
        LEFT_CONTROL,
        LEFT_ALT,
        LEFT_SUPER,
        RIGHT_SHIFT,
        RIGHT_CONTROL,
        RIGHT_ALT,
        RIGHT_SUPER,
        MENU,
    };

	constexpr auto to_key(int code) -> chip8::gui::io::Key {
        switch (code) {
        case GLFW_KEY_UNKNOWN: return chip8::gui::io::Key::UNKNOWN;
        case GLFW_KEY_SPACE: return chip8::gui::io::Key::SPACE;
        case GLFW_KEY_APOSTROPHE: return chip8::gui::io::Key::APOSTROPHE; /* ' */
        case GLFW_KEY_COMMA: return chip8::gui::io::Key::COMMA; /* , */
        case GLFW_KEY_MINUS: return chip8::gui::io::Key::MINUS; /* - */
        case GLFW_KEY_PERIOD: return chip8::gui::io::Key::PERIOD; /* . */
        case GLFW_KEY_SLASH: return chip8::gui::io::Key::SLASH; /* / */
        case GLFW_KEY_0: return chip8::gui::io::Key::KEY_0;
        case GLFW_KEY_1: return chip8::gui::io::Key::KEY_1;
        case GLFW_KEY_2: return chip8::gui::io::Key::KEY_2;
        case GLFW_KEY_3: return chip8::gui::io::Key::KEY_3;
        case GLFW_KEY_4: return chip8::gui::io::Key::KEY_4;
        case GLFW_KEY_5: return chip8::gui::io::Key::KEY_5;
        case GLFW_KEY_6: return chip8::gui::io::Key::KEY_6;
        case GLFW_KEY_7: return chip8::gui::io::Key::KEY_7;
        case GLFW_KEY_8: return chip8::gui::io::Key::KEY_8;
        case GLFW_KEY_9: return chip8::gui::io::Key::KEY_9;
        case GLFW_KEY_SEMICOLON: return chip8::gui::io::Key::SEMICOLON; /* ; */
        case GLFW_KEY_EQUAL: return chip8::gui::io::Key::EQUAL; /* = */
        case GLFW_KEY_A: return chip8::gui::io::Key::A;
        case GLFW_KEY_B: return chip8::gui::io::Key::B;
        case GLFW_KEY_C: return chip8::gui::io::Key::C;
        case GLFW_KEY_D: return chip8::gui::io::Key::D;
        case GLFW_KEY_E: return chip8::gui::io::Key::E;
        case GLFW_KEY_F: return chip8::gui::io::Key::F;
        case GLFW_KEY_G: return chip8::gui::io::Key::G;
        case GLFW_KEY_H: return chip8::gui::io::Key::H;
        case GLFW_KEY_I: return chip8::gui::io::Key::I;
        case GLFW_KEY_J: return chip8::gui::io::Key::J;
        case GLFW_KEY_K: return chip8::gui::io::Key::K;
        case GLFW_KEY_L: return chip8::gui::io::Key::L;
        case GLFW_KEY_M: return chip8::gui::io::Key::M;
        case GLFW_KEY_N: return chip8::gui::io::Key::N;
        case GLFW_KEY_O: return chip8::gui::io::Key::O;
        case GLFW_KEY_P: return chip8::gui::io::Key::P;
        case GLFW_KEY_Q: return chip8::gui::io::Key::Q;
        case GLFW_KEY_R: return chip8::gui::io::Key::R;
        case GLFW_KEY_S: return chip8::gui::io::Key::S;
        case GLFW_KEY_T: return chip8::gui::io::Key::T;
        case GLFW_KEY_U: return chip8::gui::io::Key::U;
        case GLFW_KEY_V: return chip8::gui::io::Key::V;
        case GLFW_KEY_W: return chip8::gui::io::Key::W;
        case GLFW_KEY_X: return chip8::gui::io::Key::X;
        case GLFW_KEY_Y: return chip8::gui::io::Key::Y;
        case GLFW_KEY_Z: return chip8::gui::io::Key::Z;
        case GLFW_KEY_LEFT_BRACKET: return chip8::gui::io::Key::LEFT_BRACKET; /* [ */
        case GLFW_KEY_BACKSLASH: return chip8::gui::io::Key::BACKSLASH; /* \ */
        case GLFW_KEY_RIGHT_BRACKET: return chip8::gui::io::Key::RIGHT_BRACKET; /* ] */
        case GLFW_KEY_GRAVE_ACCENT: return chip8::gui::io::Key::ACCENT; /* ` */
        case GLFW_KEY_WORLD_1: return chip8::gui::io::Key::N1; /* non-US #1 */
        case GLFW_KEY_WORLD_2: return chip8::gui::io::Key::N2; /* non-US #2 */
        case GLFW_KEY_ESCAPE: return chip8::gui::io::Key::ESCAPE;
        case GLFW_KEY_ENTER: return chip8::gui::io::Key::ENTER;
        case GLFW_KEY_TAB: return chip8::gui::io::Key::TAB;
        case GLFW_KEY_BACKSPACE: return chip8::gui::io::Key::BACKSPACE;
        case GLFW_KEY_INSERT: return chip8::gui::io::Key::INSERT;
        case GLFW_KEY_DELETE: return chip8::gui::io::Key::DEL;
        case GLFW_KEY_RIGHT: return chip8::gui::io::Key::RIGHT;
        case GLFW_KEY_LEFT: return chip8::gui::io::Key::LEFT;
        case GLFW_KEY_DOWN: return chip8::gui::io::Key::DOWN;
        case GLFW_KEY_UP: return chip8::gui::io::Key::UP;
        case GLFW_KEY_PAGE_UP: return chip8::gui::io::Key::PAGE_UP;
        case GLFW_KEY_PAGE_DOWN: return chip8::gui::io::Key::PAGE_DOWN;
        case GLFW_KEY_HOME: return chip8::gui::io::Key::HOME;
        case GLFW_KEY_END: return chip8::gui::io::Key::END;
        case GLFW_KEY_CAPS_LOCK: return chip8::gui::io::Key::CAPS_LOCK;
        case GLFW_KEY_SCROLL_LOCK: return chip8::gui::io::Key::SCROLL_LOCK;
        case GLFW_KEY_NUM_LOCK: return chip8::gui::io::Key::NUM_LOCK;
        case GLFW_KEY_PRINT_SCREEN: return chip8::gui::io::Key::PRINT_SCREEN;
        case GLFW_KEY_PAUSE: return chip8::gui::io::Key::PAUSE;
        case GLFW_KEY_F1: return chip8::gui::io::Key::F1;
        case GLFW_KEY_F2: return chip8::gui::io::Key::F2;
        case GLFW_KEY_F3: return chip8::gui::io::Key::F3;
        case GLFW_KEY_F4: return chip8::gui::io::Key::F4;
        case GLFW_KEY_F5: return chip8::gui::io::Key::F5;
        case GLFW_KEY_F6: return chip8::gui::io::Key::F6;
        case GLFW_KEY_F7: return chip8::gui::io::Key::F7;
        case GLFW_KEY_F8: return chip8::gui::io::Key::F8;
        case GLFW_KEY_F9: return chip8::gui::io::Key::F9;
        case GLFW_KEY_F10: return chip8::gui::io::Key::F10;
        case GLFW_KEY_F11: return chip8::gui::io::Key::F11;
        case GLFW_KEY_F12: return chip8::gui::io::Key::F12;
        case GLFW_KEY_F13: return chip8::gui::io::Key::F13;
        case GLFW_KEY_F14: return chip8::gui::io::Key::F14;
        case GLFW_KEY_F15: return chip8::gui::io::Key::F15;
        case GLFW_KEY_F16: return chip8::gui::io::Key::F16;
        case GLFW_KEY_F17: return chip8::gui::io::Key::F17;
        case GLFW_KEY_F18: return chip8::gui::io::Key::F18;
        case GLFW_KEY_F19: return chip8::gui::io::Key::F19;
        case GLFW_KEY_F20: return chip8::gui::io::Key::F20;
        case GLFW_KEY_F21: return chip8::gui::io::Key::F21;
        case GLFW_KEY_F22: return chip8::gui::io::Key::F22;
        case GLFW_KEY_F23: return chip8::gui::io::Key::F23;
        case GLFW_KEY_F24: return chip8::gui::io::Key::F24;
        case GLFW_KEY_F25: return chip8::gui::io::Key::F25;
        case GLFW_KEY_KP_0: return chip8::gui::io::Key::NUM_0;
        case GLFW_KEY_KP_1: return chip8::gui::io::Key::NUM_1;
        case GLFW_KEY_KP_2: return chip8::gui::io::Key::NUM_2;
        case GLFW_KEY_KP_3: return chip8::gui::io::Key::NUM_3;
        case GLFW_KEY_KP_4: return chip8::gui::io::Key::NUM_4;
        case GLFW_KEY_KP_5: return chip8::gui::io::Key::NUM_5;
        case GLFW_KEY_KP_6: return chip8::gui::io::Key::NUM_6;
        case GLFW_KEY_KP_7: return chip8::gui::io::Key::NUM_7;
        case GLFW_KEY_KP_8: return chip8::gui::io::Key::NUM_8;
        case GLFW_KEY_KP_9: return chip8::gui::io::Key::NUM_9;
        case GLFW_KEY_KP_DECIMAL: return chip8::gui::io::Key::DECIMAL;
        case GLFW_KEY_KP_DIVIDE: return chip8::gui::io::Key::DIVIDE;
        case GLFW_KEY_KP_MULTIPLY: return chip8::gui::io::Key::MULTIPLY;
        case GLFW_KEY_KP_SUBTRACT: return chip8::gui::io::Key::SUBTRACT;
        case GLFW_KEY_KP_ADD: return chip8::gui::io::Key::ADD;
        case GLFW_KEY_KP_ENTER: return chip8::gui::io::Key::NUM_ENTER;
        case GLFW_KEY_KP_EQUAL: return chip8::gui::io::Key::NUM_EQUAL;
        case GLFW_KEY_LEFT_SHIFT: return chip8::gui::io::Key::LEFT_SHIFT;
        case GLFW_KEY_LEFT_CONTROL: return chip8::gui::io::Key::LEFT_CONTROL;
        case GLFW_KEY_LEFT_ALT: return chip8::gui::io::Key::LEFT_ALT;
        case GLFW_KEY_LEFT_SUPER: return chip8::gui::io::Key::LEFT_SUPER;
        case GLFW_KEY_RIGHT_SHIFT: return chip8::gui::io::Key::RIGHT_SHIFT;
        case GLFW_KEY_RIGHT_CONTROL: return chip8::gui::io::Key::RIGHT_CONTROL;
        case GLFW_KEY_RIGHT_ALT: return chip8::gui::io::Key::RIGHT_ALT;
        case GLFW_KEY_RIGHT_SUPER: return chip8::gui::io::Key::RIGHT_SUPER;
        case GLFW_KEY_MENU: return chip8::gui::io::Key::MENU;
        }

        return chip8::gui::io::Key::UNKNOWN;
    }
}