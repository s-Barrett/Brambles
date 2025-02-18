#include "Model.h"
#include <rend/rend.h>

void Brambles::Model::onLoad() {
    // Initialize the rend::Model here
    m_model = std::make_shared<rend::Model>(getPath()); 
}
