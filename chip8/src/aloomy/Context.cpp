#include <aloomy/Context.hpp>

aloomy::Context::Context(aloomy::Device& device) {
	this->raw = alcCreateContext(&device.get(), nullptr);
}

aloomy::Context::~Context() {
	if (this->raw != nullptr) {
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(this->raw);
	}
}

void aloomy::Context::make_current() const {
	alcMakeContextCurrent(this->raw);
}

aloomy::RawContext& aloomy::Context::get() {
	return *this->raw;
}

const aloomy::RawContext& aloomy::Context::get() const {
	return *this->raw;
}
