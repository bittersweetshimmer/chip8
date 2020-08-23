#include <aloomy/Device.hpp>

aloomy::Device::Device() {
	this->raw = alcOpenDevice(nullptr);
}

aloomy::Device::~Device() {
	if (this->raw != nullptr) {
		alcCloseDevice(this->raw);
	}
}

aloomy::RawDevice& aloomy::Device::get() {
	return *this->raw;
}

const aloomy::RawDevice& aloomy::Device::get() const {
	return *this->raw;
}
