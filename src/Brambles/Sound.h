
#pragma once

#include "Resource.h"
#include <AL/al.h>

namespace Brambles
{
    struct AudioSource;

    /**
     * @brief Represents a sound resource used by AudioSource for playback.
     */
    struct Sound : public Resource
    {
    public:
        /**
         * @brief Gets the OpenAL buffer ID.
         * @return The buffer ID.
         */
        ALuint getBufferId() const
        {
            return mBufferId;
        }

        /**
         * @brief Loads the sound resource.
         */
        void onLoad();

    private:
        friend struct AudioSource;

        ALuint mBufferId = 0;  /**< OpenAL buffer ID */
        ALenum mFormat = 0;     /**< Audio format */
        ALsizei mFrequency = 0; /**< Audio sample frequency */
    };
}
