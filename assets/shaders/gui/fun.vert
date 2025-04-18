#version 460

in vec3 a_Position;
in vec2 a_TexCoord;
in vec3 a_Normal;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_Projection;
uniform mat4 u_Model;
uniform mat4 u_View;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0); 
    v_TexCoord = a_TexCoord;
    v_TexCoord.y = 1.0 - v_TexCoord.y;
    v_Normal = mat3(u_Model) * a_Normal;
    
    v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));
    float waveAmount = sin(v_FragPos.x * 0.5 + u_Model[3][0] * 0.5) * 0.03;
    v_FragPos.x += waveAmount; // Distort the y-position for a wavy effect
}
