#pragma once

#include <aloomy/Types.hpp>

namespace aloomy {
	struct Device {
		Device();
		~Device();

		aloomy::RawDevice& get();
		const aloomy::RawDevice& get() const;

	private:
		aloomy::RawDevice* raw;
	};
}