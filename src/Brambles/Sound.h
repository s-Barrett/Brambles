#pragma once

#include "Resource.h"

#include <AL/al.h>

namespace Brambles
{
	struct AudioSource;

	struct Sound : public Resource
	{
	public:
		ALuint Sound::getBufferId() const
		{
			return mBufferId;
		}
		void onLoad();
	private:
		friend struct AudioSource;

		ALuint mBufferId = 0;
		ALenum mFormat = 0;
		ALsizei mFrequency = 0;
	};
}