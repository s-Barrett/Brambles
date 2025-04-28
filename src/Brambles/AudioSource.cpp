#include "AudioSource.h"
#include "Core.h"
#include "Entity.h"
#include "Camera.h"

namespace Brambles
{
	AudioSource::AudioSource()
	{
		alGenSources(1, &m_sourceId);
	}

	AudioSource::~AudioSource()
	{
		alDeleteSources(1, &m_sourceId);
	}

	void AudioSource::setSound(std::shared_ptr<Sound> _sound)
	{
		m_sound = _sound;
		m_bufferId = m_sound->getBufferId();

		// Attach buffer and set audio properties
		alSourcei(m_sourceId, AL_BUFFER, m_bufferId);
		alSourcef(m_sourceId, AL_PITCH, m_pitch);
		alSourcef(m_sourceId, AL_MAX_DISTANCE, m_distance);
	}

	void AudioSource::onTick()
	{
		std::shared_ptr<Core> core = getEntity()->getCore();
		std::shared_ptr<Camera> camera = core->getCamera();
		glm::vec3 cameraPos = camera->getPosition();
		glm::vec3 cameraForward = camera->getForward(); // Needs to be implemented if not already
		glm::vec3 cameraUp = camera->getUp(); // Same as above

		// Update listener position
		alListener3f(AL_POSITION, cameraPos.x, cameraPos.y, cameraPos.z);

		// Update listener orientation (forward + up vectors)
		float orientation[] = {
			cameraForward.x, cameraForward.y, cameraForward.z,  // "At" vector (where listener is looking)
			cameraUp.x, cameraUp.y, cameraUp.z                  // "Up" vector (what is 'up' for the listener)
		};
		alListenerfv(AL_ORIENTATION, orientation);

		// Update source position
		glm::vec3 sourcePos = getPosition();
		alSource3f(m_sourceId, AL_POSITION, sourcePos.x, sourcePos.y, sourcePos.z);

		// Adjust volume based on distance
		if (glm::distance(sourcePos, cameraPos) > m_distance)
		{
			alSourcef(m_sourceId, AL_GAIN, 0.0f); // Mute if too far
		}
		else
		{
			alSourcef(m_sourceId, AL_GAIN, m_gain);
		}

	}


	// In AudioSource.cpp
	void AudioSource::play()
	{
		if (!m_sourceId || !m_sound)
		{
			std::cerr << "AudioSource not properly initialized!" << std::endl;
			return;
		}

		alSourcei(m_sourceId, AL_BUFFER, m_sound->getBufferId());
		ALenum error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cerr << "OpenAL error when binding buffer: " << error << std::endl;
			return;
		}

		alSourcePlay(m_sourceId);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cerr << "OpenAL error when playing sound: " << error << std::endl;
		}
	}

	void AudioSource::stop()
	{
		if (!m_sourceId)
		{
			std::cerr << "AudioSource not properly initialized!" << std::endl;
			return;
		}

		alSourceStop(m_sourceId);
	}

	bool AudioSource::isPlaying() const
	{
		if (!m_sourceId) return false;

		ALint state;
		alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);
		return (state == AL_PLAYING);
	}

	void AudioSource::setLooping(bool loop)
	{
		m_looping = loop;
		alSourcei(m_sourceId, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	}

	void AudioSource::setGain(float gain)
	{
		m_gain = gain;
		alSourcef(m_sourceId, AL_GAIN, gain);
	}

	void AudioSource::setPitch(float pitch)
	{
		m_pitch = pitch;
		alSourcef(m_sourceId, AL_PITCH, pitch);
	}

}
