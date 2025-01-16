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
		alSourcei(m_sourceId, AL_BUFFER, m_bufferId);
		alSourcef(m_sourceId, AL_PITCH, m_pitch);
		alSourcef(m_sourceId, AL_MAX_DISTANCE, m_distance);

	}

	void AudioSource::onTick()
	{
		std::shared_ptr<Core> core = getEntity()->getCore();
		glm::vec3 cameraPos = core->getCamera()->getPosition();

		alListener3f(AL_POSITION, cameraPos.x, cameraPos.y, cameraPos.z);
		alSource3f(m_sourceId, AL_POSITION, getPosition().x, getPosition().y, getPosition().z);

		if (glm::distance(getPosition(), cameraPos) > m_distance)
		{
			alSourcef(m_sourceId, AL_GAIN, 0.0f);
		}
		else
		{
			alSourcef(m_sourceId, AL_GAIN, m_gain);
		}

		if (!m_looping && !isPlaying())
		{
			play();
		}
	}

	void AudioSource::play()
	{
		std::cout << "playing sound" << std::endl;
		alSourcePlay(m_sourceId);	
	}

	bool AudioSource::isPlaying()
	{
		int state = 0;
		alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);

		if (state == AL_PLAYING)
			return true;

		return false;
	}

}