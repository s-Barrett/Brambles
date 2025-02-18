#pragma once

#include "../Resource.h"
#include <memory>
#include <vector>
#include "../../rend/Model.h" // Include the correct path

namespace Brambles {
    struct Renderer; // Forward declaration

    struct Model : Resource {
        void onLoad();

        // Expose materials from rend::Model
        const std::vector<rend::Model::Material>& getMaterials() const {
            return m_model->materials;
        }

    private:
        friend struct Renderer; // Give Renderer access to m_model
        std::shared_ptr<rend::Model> m_model; // Now using rend::Model
    };
}

