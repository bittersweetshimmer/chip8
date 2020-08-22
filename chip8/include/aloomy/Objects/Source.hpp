#pragma once

#include <array>
#include <aloomy/Types.hpp>
#include <aloomy/Objects/Buffer.hpp>

namespace aloomy {
	enum class SourceState {
		INITIAL = AL_INITIAL,     
		PLAYING = AL_PLAYING,                              
		PAUSED = AL_PAUSED,
		STOPPED = AL_STOPPED
	};

	struct Source {
		Source();
		Source(const aloomy::Buffer& buffer);
		Source(Source&& other);
		Source& operator=(Source&& other);
		~Source();

		void play() const;
		void pause() const;
		void stop() const;

		RawID get() const;

		void set_buffer(const aloomy::Buffer& buffer);
		
		void set_pitch(float pitch);
		void set_gain(float gain);
		void set_position(std::array<float, 3> position);
		void set_velocity(std::array<float, 3> velocity);
		void set_loop(bool loop);

		float get_pitch();
		float get_gain();
		std::array<float, 3> get_position();
		std::array<float, 3> get_velocity();
		bool is_looped();
		
		SourceState get_state();
	private:
		RawID buffer_id = 0u;

		float pitch = 1.0;
		float gain = 1.0;
		std::array<float, 3> position = std::array<float, 3>{0.0f, 0.0f, 0.0f};
		std::array<float, 3> velocity = std::array<float, 3>{0.0f, 0.0f, 0.0f};
		bool loop = false;

		RawID id = 0u;
	};
}