#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

namespace rend
{

    std::string readFile(const std::string& filePath) {
        std::ifstream fileStream(filePath, std::ios::in);
        if (!fileStream.is_open()) {
            std::cerr << "Could not open file " << filePath << std::endl;
            throw std::runtime_error("Failed to open file.");
        }
        std::stringstream sstr;
        sstr << fileStream.rdbuf();
        fileStream.close();
        return sstr.str();
    }

    void checkShaderCompileErrors(GLuint shaderId, const std::string& type) {
        GLint success;
        GLchar infoLog[1024];
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shaderId, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }

    void checkProgramLinkErrors(GLuint programId) {
        GLint success;
        GLchar infoLog[1024];
        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programId, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR: \n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }

}
