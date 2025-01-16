#include "Audio.h"
#include <iostream>

namespace Brambles
{
    // Constructor for the Audio class
    Audio::Audio()
    {
        // Open the default audio device
        m_device = alcOpenDevice(NULL);
        if (!m_device)
        {
            throw std::runtime_error("Failed to open audio device");
        }

        // Create an audio context associated with the device
        m_context = alcCreateContext(m_device, NULL);
        if (!m_context)
        {
            alcCloseDevice(m_device);
            throw std::runtime_error("Failed to create audio context");
        }

        // Set the created context as the current one
        if (!alcMakeContextCurrent(m_context))
        {
            alcDestroyContext(m_context);
            alcCloseDevice(m_device);
            throw std::runtime_error("Failed to make context current");
        }
    }

    // Destructor for the Audio class
    Audio::~Audio()
    {
        // Reset the current context before destruction
        alcMakeContextCurrent(NULL);
        // Destroy the context
        alcDestroyContext(m_context);
        // Close the audio device
        alcCloseDevice(m_device);
    }

    // Placeholder function for loading audio resources
    void Audio::onLoad()
    {
        std::cout << "Audio override" << std::endl;
    }
}
