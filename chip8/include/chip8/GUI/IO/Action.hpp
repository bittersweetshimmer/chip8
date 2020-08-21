#pragma once
#include <GLFW/glfw3.h>

namespace chip8::gui::io {
	enum class Action {
		PRESS = GLFW_PRESS,
		REPEAT = GLFW_REPEAT,
		RELEASE = GLFW_RELEASE,
	};

	constexpr auto to_action(int code) -> chip8::gui::io::Action {
		return static_cast<chip8::gui::io::Action>(code);
	}
}