#include "Model.h"
#include <rend/rend.h>

void Brambles::Model::onLoad() {
    std::cout << "Loading model from path: " << getPath() << std::endl;
    m_model = std::make_shared<rend::Model>(getPath());
    std::cout << "Model loaded successfully." << std::endl;
}
