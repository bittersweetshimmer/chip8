#pragma once

#include <aloomy/Types.hpp>
#include <aloomy/Device.hpp>

namespace aloomy {
	struct Context {
		Context(aloomy::Device&);
		~Context();

		void make_current() const;
		aloomy::RawContext& get();
		const aloomy::RawContext& get() const;
	private:
		aloomy::RawContext* raw;
	};
}