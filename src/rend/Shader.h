#pragma once

#include <vector>
#include <gl/glew.h>
#include<SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string.h>
#include "Utilities.h"


namespace rend
{

    struct  Shader
    {
        Shader();

        GLuint id();
        void uniform(const std::string& _name, const glm::mat4& _value);
        void uniform(const std::string& _name, const glm::vec3& _value);

    private:
        GLuint m_id;
    };

}