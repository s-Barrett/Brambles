#version 100
// Define precision for WebGL
precision mediump float;

attribute vec3 a_Position; // Vertex position
attribute vec2 a_TexCoord; // Texture coordinates
attribute vec3 a_Normal;   // Vertex normal

varying vec2 v_TexCoord;   // Output texture coordinates to fragment shader
varying vec3 v_Normal;     // Output normal to fragment shader
varying vec3 v_FragPos;    // Output fragment position to fragment shader

uniform mat4 u_Projection; // Projection matrix
uniform mat4 u_Model;      // Model matrix
uniform mat4 u_View;       // View matrix

void main()
{
    // Calculate the transformed position
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);

    // Pass texture coordinates and normal to the fragment shader
    v_TexCoord = a_TexCoord;
    v_Normal = mat3(u_Model) * a_Normal;  // Transform normal to world space

    // Pass the fragment position to fragment shader in world space
    v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));  // Position in world space
}
