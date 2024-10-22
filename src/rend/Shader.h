#pragma once

#include <vector>
#include <gl/glew.h>
#include<SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string.h>
#include "Utilities.h"

struct  Shader
{
	Shader();

	GLuint id();
	void uniform(const std::string& _name, const glm::mat4& _value);
	void uniform(const std::string& _name, const glm::vec3& _value);

private:
	GLuint m_id;
};

Shader::Shader()
	: m_id(0)
{ }

void Shader::uniform(const std::string& _name, const glm::mat4& _value)
{
	GLint loc = glGetUniformLocation(id(), _name.c_str());

	glUseProgram(id());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(_value));
	glUseProgram(0);
}

void Shader::uniform(const std::string& _name, const glm::vec3& _value)
{
	GLint loc = glGetUniformLocation(id(), _name.c_str());

	glUseProgram(id());
	glUniform3f(loc, _value.x, _value.y, _value.z);
	glUseProgram(0);
}


GLuint Shader::id() {
    if (!m_id) {
        try {
            std::string vertexShaderSrc = readFile("shaders/vertexShader.glsl");
            std::string fragmentShaderSrc = readFile("shaders/fragmentShader.glsl");

            // Create and compile vertex shader
            GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
            const char* src = vertexShaderSrc.c_str();
            glShaderSource(vertexShaderId, 1, &src, NULL);
            glCompileShader(vertexShaderId);
            checkShaderCompileErrors(vertexShaderId, "VERTEX");

            // Create and compile fragment shader
            GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
            src = fragmentShaderSrc.c_str();
            glShaderSource(fragmentShaderId, 1, &src, NULL);
            glCompileShader(fragmentShaderId);
            checkShaderCompileErrors(fragmentShaderId, "FRAGMENT");

            // Create shader program and attach shaders
            m_id = glCreateProgram();
            glAttachShader(m_id, vertexShaderId);
            glAttachShader(m_id, fragmentShaderId);
            glLinkProgram(m_id);
            checkProgramLinkErrors(m_id);

            // Detach and delete shaders
            glDetachShader(m_id, vertexShaderId);
            glDetachShader(m_id, fragmentShaderId);
            glDeleteShader(vertexShaderId);
            glDeleteShader(fragmentShaderId);
        }
        catch (const std::exception& e) {
            std::cerr << "Shader program failed: " << e.what() << std::endl;
            throw;
        }
    }
    return m_id;
}
