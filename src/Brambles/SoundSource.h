#include <AL/al.h>
#include <AL/alc.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <stdexcept>
#include <vector>
#include <string>

#include "stb_vorbis.c"
#include "Component.h"

namespace Brambles
{
	class SoundSource : public Component
	{
	public:
		SoundSource();
		~SoundSource();

		void setSound(const std::string& soundName);
		void play();
		void stop();
		void pause();
		void setLooping(bool loop);
		void setVolume(float volume);


	private:
		std::string m_SoundName;
		ALuint m_Source;
	};
}	