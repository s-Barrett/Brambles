#pragma once
#include <iostream>
#include <vector>
#include <gl/glew.h>
#include <string>

namespace rend
{

	std::string readFile(const std::string& filePath);

	void checkShaderCompileErrors(GLuint shaderId, const std::string& type);
	void checkProgramLinkErrors(GLuint programId);
}
#pragma once
