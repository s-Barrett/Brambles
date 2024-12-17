#include "SoundSource.h"

namespace Brambles
{

	void load_ogg(const std::string&, std::vector<unsigned char>&, ALenum&, ALsizei&);

	SoundSource::SoundSource()
	{
		ALCdevice* device = alcOpenDevice(NULL);

		if (!device)
		{
			throw std::runtime_error("Failed to open audio device");
		}

		ALCcontext* context = alcCreateContext(device, NULL);

		if (!context)
		{
			alcCloseDevice(device);
			throw std::runtime_error("Failed to create audio context");
		}

		if (!alcMakeContextCurrent(context))
		{
			alcDestroyContext(context);
			alcCloseDevice(device);
			throw std::runtime_error("Failed to make context current");
		}

		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		//alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);


		ALuint sourceId = 0;
		alGenSources(1, &sourceId);

		//alSourcei(sourceId, AL_BUFFER, bufferId);
		//alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
		//alSourcef(sourceId, AL_PITCH, 10);
		//alSourcef(sourceId, AL_GAIN, vol);
	}

	SoundSource::~SoundSource()
	{
		alDeleteSources(1, &m_Source);
	}

	void SoundSource::setSound(const std::string& soundName)
	{

	}

	void SoundSource::play()
	{

		
	}

	void SoundSource::stop()
	{
		// Stop the sound
	}

}