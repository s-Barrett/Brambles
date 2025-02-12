#include "Shader.h"

namespace Brambles
{
    void Shader::onLoad()
    {
        std::string vertPath = getPath() + ".vert";
        std::string fragPath = getPath() + ".frag";
        m_shader = std::make_shared<rend::Shader>(vertPath, fragPath);
    }

    std::shared_ptr<rend::Shader> Shader::getShader()
    {
        return m_shader;
    }
}