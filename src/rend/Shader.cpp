#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace rend
{
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        std::string vertexShaderSrc = readFile(vertexPath);
        std::string fragmentShaderSrc = readFile(fragmentPath);
        compileAndLinkShaders(vertexShaderSrc, fragmentShaderSrc);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_id);
    }

    std::string Shader::readFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
            throw std::runtime_error("Failed to open file: " + filePath);

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }

    void Shader::compileAndLinkShaders(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
    {
        GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        const char* vertexSrc = vertexShaderSrc.c_str();
        glShaderSource(vertexShaderId, 1, &vertexSrc, NULL);
        glCompileShader(vertexShaderId);
        checkShaderCompileErrors(vertexShaderId, "VERTEX");

        GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fragmentSrc = fragmentShaderSrc.c_str();
        glShaderSource(fragmentShaderId, 1, &fragmentSrc, NULL);
        glCompileShader(fragmentShaderId);
        checkShaderCompileErrors(fragmentShaderId, "FRAGMENT");

        m_id = glCreateProgram();
        glAttachShader(m_id, vertexShaderId);
        glAttachShader(m_id, fragmentShaderId);
        glLinkProgram(m_id);
        checkProgramLinkErrors(m_id);

        glBindAttribLocation(m_id, 0, "a_Position");
        glBindAttribLocation(m_id, 1, "a_TexCoord");
        glBindAttribLocation(m_id, 2, "a_Normal");

        glDetachShader(m_id, vertexShaderId);
        glDetachShader(m_id, fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }

    void Shader::checkShaderCompileErrors(GLuint shader, const std::string& type)
    {
        GLint success;
        GLchar infoLog[1024];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }

    void Shader::checkProgramLinkErrors(GLuint program)
    {
        GLint success;
        GLchar infoLog[1024];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(program, 1024, NULL, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR:\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }

    void Shader::uniform(const std::string& name, const glm::mat4& value)
    {
        GLint loc = glGetUniformLocation(m_id, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::uniform(const std::string& name, const glm::vec3& value)
    {
        GLint loc = glGetUniformLocation(m_id, name.c_str());
        glUniform3f(loc, value.x, value.y, value.z);
    }

	void Shader::uniform(const std::string& name, float value)
	{
		GLint loc = glGetUniformLocation(m_id, name.c_str());
		glUniform1f(loc, value);
	}

    void Shader::drawOutline(GLuint _vao, GLsizei _vertexCount)
    {

        glUseProgram(id());
        glBindVertexArray(_vao);
        glDrawArrays(GL_LINE_LOOP, 0, _vertexCount);
        glBindVertexArray(0);
        glUseProgram(0);
    }

    void Shader::draw(GLuint vaoId, GLsizei vertexCount)
    {
        glBindVertexArray(vaoId); 
        glDrawArrays(GL_TRIANGLES, 0, vertexCount); 
        glBindVertexArray(0);
    }


}
