#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 debugmodel;
uniform mat4 debugview;
uniform mat4 debugprojection;

out vec3 FragPos;
out vec3 Normal;

void main()
{
    FragPos = vec3(debugmodel * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(debugmodel))) * aNormal;  
    gl_Position = debugprojection * debugview * vec4(FragPos, 1.0);
}