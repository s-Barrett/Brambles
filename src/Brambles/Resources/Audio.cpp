#include "Audio.h"
#include <iostream>

namespace Brambles
{
    Audio::Audio()
    {
        m_device = alcOpenDevice(NULL);
        if (!m_device)
        {
            throw std::runtime_error("Failed to open audio device");
        }

        m_context = alcCreateContext(m_device, NULL);
        if (!m_context)
        {
            alcCloseDevice(m_device);
            throw std::runtime_error("Failed to create audio context");
        }

        if (!alcMakeContextCurrent(m_context))
        {
            alcDestroyContext(m_context);
            alcCloseDevice(m_device);
            throw std::runtime_error("Failed to make context current");
        }
    }

    Audio::~Audio()
    {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(m_context);
        alcCloseDevice(m_device);
    }

    void Audio::onLoad()
    {
		std::cout << "Audio override" << std::endl;
    }
}
