#include "Sound.h"		
#include <stdexcept>
#include <vector>

#include "stb_vorbis.c"

namespace Brambles
{

	void Sound::onLoad()
	{
		std::vector<unsigned char> data;

		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;

		size_t samples = stb_vorbis_decode_filename((getPath() + ".ogg").c_str(),
			&channels, &sampleRate, &output);

		if (samples == -1)
		{
			throw std::runtime_error("Failed to open file '" + (getPath() + ".ogg") + "' for decoding");
		}

		if (channels < 2)
		{
			mFormat = AL_FORMAT_MONO16;
		}
		else
		{
			mFormat = AL_FORMAT_STEREO16;
		}

		data.resize(samples * channels * sizeof(short));
		memcpy(&data.at(0), output, data.size());

		mFrequency = sampleRate;

		free(output);
		alGenBuffers(1, &mBufferId);
		alBufferData(mBufferId, mFormat, &data.at(0),
			static_cast<ALsizei>(data.size()), mFrequency);
	}
}