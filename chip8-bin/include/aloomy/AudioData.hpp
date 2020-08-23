#pragma once

#include <aloomy/al.hpp>
#include <memory>

namespace aloomy {
	struct AudioData {
		std::unique_ptr<std::byte[]> data = nullptr;
		size_t size = 0;
		size_t frequency = 0;
		ALenum format = 0;
	};
}