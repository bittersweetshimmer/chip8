#include <aloomy/Objects/Source.hpp>

aloomy::Source::Source() {
	alGenSources(1, &this->id);

	this->set_pitch(1.0f);
	this->set_gain(1.0f);
	this->set_position(std::array<float, 3>{0.0f, 0.0f, 0.0f});
	this->set_velocity(std::array<float, 3>{0.0f, 0.0f, 0.0f});
	this->set_loop(false);
}

aloomy::Source::Source(const aloomy::Buffer& buffer) {
	alGenSources(1, &this->id);

	this->set_pitch(1.0f);
	this->set_gain(1.0f);
	this->set_position(std::array<float, 3>{0.0f, 0.0f, 0.0f});
	this->set_velocity(std::array<float, 3>{0.0f, 0.0f, 0.0f});
	this->set_loop(false);

	this->set_buffer(buffer);
}

aloomy::Source::Source(Source&& other) {
	std::swap(this->id, other.id);
	std::swap(this->buffer_id, other.buffer_id);

	this->pitch = other.pitch;
	this->gain = other.gain;
	this->position = other.position;
	this->velocity = other.velocity;
	this->loop = other.loop;
}

aloomy::Source& aloomy::Source::operator=(Source&& other) {
	std::swap(this->id, other.id);
	std::swap(this->buffer_id, other.buffer_id);

	this->set_pitch(other.pitch);
	this->set_gain(other.gain);
	this->set_position(other.position);
	this->set_velocity(other.velocity);
	this->set_loop(other.loop);

	return *this;
}

aloomy::Source::~Source() {
	if (this->id != 0) {
		alDeleteSources(1, &this->id);
	}
}

void aloomy::Source::play() const {
	alSourcePlay(this->id);
}

void aloomy::Source::pause() const {
	alSourcePause(this->id);
}

void aloomy::Source::stop() const {
	alSourceStop(this->id);
}

aloomy::RawID aloomy::Source::get() const {
	return this->id;
}

void aloomy::Source::set_buffer(const aloomy::Buffer& buffer) {
	this->buffer_id = buffer.get();
	if (this->buffer_id != 0) alSourcei(this->id, AL_BUFFER, this->buffer_id);
}

void aloomy::Source::set_pitch(float pitch) {
	this->pitch = pitch;

	alSourcef(this->id, AL_PITCH, this->pitch);
}

void aloomy::Source::set_gain(float gain) {
	this->gain = gain;

	alSourcef(this->id, AL_GAIN, this->gain);
}

void aloomy::Source::set_position(std::array<float, 3> position) {
	this->position = position;

	alSource3f(this->id, AL_POSITION, position[0], position[1], position[2]);
}

void aloomy::Source::set_velocity(std::array<float, 3> velocity) {
	this->velocity = velocity;

	alSource3f(this->id, AL_POSITION, velocity[0], velocity[1], velocity[2]);
}

void aloomy::Source::set_loop(bool loop) {
	this->loop = loop;

	alSourcei(this->id, AL_LOOPING, this->loop);
}

float aloomy::Source::get_pitch() {
	return this->pitch;
}

float aloomy::Source::get_gain() {
	return this->gain;
}

std::array<float, 3> aloomy::Source::get_position() {
	return this->position;
}

std::array<float, 3> aloomy::Source::get_velocity() {
	return this->velocity;
}

bool aloomy::Source::is_looped() {
	return this->loop;
}

aloomy::SourceState aloomy::Source::get_state() {
	auto value = 0;
	alGetSourcei(this->id, AL_SOURCE_STATE, &value);
	return static_cast<aloomy::SourceState>(value);
}
