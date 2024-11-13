#version 330 core
vec3 aPos;
vec2 aTexCoords;

vec2 TexCoords;

uniform mat4 u_Model;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_Model * vec4(aPos, 1.0);
    TexCoords = aTexCoords;

}
