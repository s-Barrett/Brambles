#pragma once

#include "../Resource.h"
#include <memory>
#include <vector>
#include "../../rend/Model.h" // Include the correct path


namespace Brambles {
    struct Renderer; // Forward declaration

    struct Model : Resource {
        void onLoad();

       
        const std::vector<rend::Model::Material>& getMaterials() const {
            return m_model->materials;
        }

        const std::vector<rend::Model::Face>& getFaces() const {
            return m_model->m_faces;
        }


    private:
        friend struct Renderer; 
        std::shared_ptr<rend::Model> m_model;
    };
}

