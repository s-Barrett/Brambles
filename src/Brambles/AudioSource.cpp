#include "AudioSource.h"

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
	}

	void AudioSource::onTick()
	{
		if (!m_looping && !isPlaying())
		{
			//play();
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