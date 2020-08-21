#pragma once
#include <filesystem>
#include <vector>

namespace chip8::gui::ev {
	struct DropFileEvent {
		std::vector<std::filesystem::path> paths;
	};
};