#pragma once
#include <iostream>
#include <vector>
#include <gl/glew.h>
#include <string>

// Function to read the entire content of a shader file into a string
std::string readFile(const std::string& filePath);

// Functions to check shader and program compilation/link errors
void checkShaderCompileErrors(GLuint shaderId, const std::string& type);
void checkProgramLinkErrors(GLuint programId);
#pragma once
