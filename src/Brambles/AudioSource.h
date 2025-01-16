

#include <AL/al.h>
#include <AL/alc.h>

#include "Sound.h"
#include <stdexcept>
#include <vector>
#include <string>

#include "Component.h"

namespace Brambles
{
	/**
	 * @brief Handles audio source functionality including playback and sound management.
	 */
    struct AudioSource : public Component
    {
        AudioSource();
        ~AudioSource();

        void onTick();

        /**
         * @brief Sets the sound for this audio source.
         * @param _sound A shared pointer to the Sound to be set.
         */
        void setSound(std::shared_ptr<Sound> _sound);

        /**
         * @brief Checks if the audio source is currently playing.
         * @return True if playing, false otherwise.
         */
        bool isPlaying();

        void play();

    private:
        std::shared_ptr<Sound> m_sound = nullptr; ///< The sound associated with the audio source.
        std::string m_soundName; ///< The name of the sound.

        bool m_looping = false; ///< Indicates if the sound should loop.

        float m_distance = 100.0f; ///< Distance for 3D audio falloff.

        float m_pitch = 1.0f; ///< Pitch of the sound.

        float m_gain = 1.0f; ///< Volume of the sound.

        ALuint m_bufferId = 0; ///< OpenAL buffer ID for the sound.
        ALuint m_sourceId = 0; ///< OpenAL source ID for playback.
    };
}
