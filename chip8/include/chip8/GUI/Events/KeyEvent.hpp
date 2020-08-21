#pragma once
#include <chip8/GUI/IO/Keyboard.hpp>
#include <chip8/GUI/IO/Action.hpp>

namespace chip8::gui::ev {
	struct KeyEvent {
		chip8::gui::io::Key key;
		chip8::gui::io::Action action;
	};
};