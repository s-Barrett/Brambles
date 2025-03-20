#pragma once

#include <vector>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string.h>
#include "Utilities.h"
#include "Model.h"


namespace rend
{

    struct  Shader
    {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        GLuint id() const { return m_id; }
        void use() const { glUseProgram(m_id); }
        void stop() const { glUseProgram(0); }
        void uniform(const std::string& name, const glm::mat4& value);
        void uniform(const std::string& name, const glm::vec3& value);
		void uniform(const std::string& name, float value);
		void uniform(const std::string& name, const std::vector<glm::vec3>& values);
		void uniform(const std::string& name, const glm::vec4& value);
		void uniform(const std::string& name, const std::vector<glm::vec4>& values);
		void uniform(const std::string& name, const glm::vec2& value);
		void uniform(const std::string& name, int value);
		void uniform(const std::string& name, const glm::mat3& value);
		void uniform(const std::string& name, const std::vector<float>& values);
		void uniform(const std::string& name, const std::vector<glm::mat4>& values);
        void drawOutline(GLuint _vao, GLsizei _vertexCount);
		void drawMeshOutline(GLuint _vao, GLuint _vbo, GLsizei _lineVertices);
		void draw(GLuint vaoId, GLsizei vertexCount);
    

    private:
        GLuint m_id;
        void compileAndLinkShaders(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
        std::string readFile(const std::string& filePath);
        void checkShaderCompileErrors(GLuint shader, const std::string& type);
        void checkProgramLinkErrors(GLuint program);
	};

}
