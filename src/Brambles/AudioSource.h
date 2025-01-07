#include <AL/al.h>
#include <AL/alc.h>


#include "Sound.h"
#include <stdexcept>
#include <vector>
#include <string>


#include "Component.h"

namespace Brambles
{
	struct AudioSource : public Component
	{
	
		AudioSource();
		~AudioSource();

		void onTick();

		void setSound(std::shared_ptr<Sound> _sound);

		bool isPlaying();

		void play();


	private:

		std::shared_ptr<Sound> m_sound = nullptr;
		std::string m_soundName;

		bool m_looping = false;

		float m_pitch = 1.0f;
		float m_gain = 1.0f;

		ALuint m_bufferId = 0;
		ALuint m_sourceId = 0;
	};
}	