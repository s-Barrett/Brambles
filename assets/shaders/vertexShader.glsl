#version 330 core
attribute vec3 a_Position;
attribute vec2 a_TexCoord;

varying vec2 v_TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform mat4 u_View;

void main() {
    v_TexCoord = a_TexCoord;
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
}
