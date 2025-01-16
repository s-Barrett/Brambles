
#include "iostream"
#include "../Resource.h"
#include "rend/rend.h"

#include <AL/al.h>
#include <AL/alc.h>

namespace Brambles
{

    /**
     * @brief Holds an Audio context and ID.
     */
    class Audio : public Resource
    {
    public:
        Audio();
        ~Audio();

        void onLoad() override;

    private:
        ALCcontext* m_context = 0;
        ALCdevice* m_device = 0;
    };
}
