#pragma once

#include <aloomy/Types.hpp>
#include <aloomy/AudioData.hpp>

namespace aloomy {
	struct Buffer {
		Buffer();
		Buffer(Buffer&& other);
		Buffer& operator=(Buffer&& other);
		~Buffer();

		RawID get() const;

		AudioData& get_audio();
		const AudioData& get_audio() const;
		void set_audio(AudioData&& data);

	private:
		AudioData audio;
		RawID id;
	};
}