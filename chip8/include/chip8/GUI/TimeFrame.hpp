#pragma once
#include <chip8/GUI/Time.hpp>

namespace chip8::gui {
	struct TimeFrame {
		chip8::gui::Time current_time;
		chip8::gui::Time delta;
	};
}