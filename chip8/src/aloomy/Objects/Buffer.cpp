#include <aloomy/Objects/Buffer.hpp>

aloomy::Buffer::Buffer() {
	alGenBuffers(1, &this->id);
}

aloomy::Buffer::Buffer(Buffer&& other) {
	if (this != &other) {
		this->id = other.id;
		this->audio = std::move(other.audio);

		other.id = 0;
	}
}

aloomy::Buffer& aloomy::Buffer::operator=(aloomy::Buffer&& other) {
	if (this != &other) {
		this->id = other.id;
		this->audio = std::move(other.audio);

		other.id = 0;
	}

	return *this;
}


aloomy::Buffer::~Buffer() {
	if (this->id != 0) {
		alDeleteBuffers(1, &this->id);
	}
}

aloomy::RawID aloomy::Buffer::get() const {
	return this->id;
}

aloomy::AudioData& aloomy::Buffer::get_audio() {
	return this->audio;
}

const aloomy::AudioData& aloomy::Buffer::get_audio() const {
	return this->audio;
}

void aloomy::Buffer::set_audio(AudioData&& data) {
	this->audio = std::move(data);

	auto error = 0;
	alBufferData(this->id, this->audio.format, this->audio.data.get(), this->audio.size, this->audio.frequency);
}
