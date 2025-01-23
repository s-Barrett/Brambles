
#include "../Resource.h"
#include "rend/rend.h"

#include <iostream>
#include <memory>

namespace Brambles
{
    struct Renderer;

	/**
	 * @brief Represents a 3D model resource for rendering.
	 */
    struct Model : Resource
    {
        /** Loads the model resource. */
        void onLoad();

    private:
        friend struct Brambles::Renderer; ///< Grants access to m_model.
        std::shared_ptr<rend::Model> m_model; ///< 3D model data.
    };
}
