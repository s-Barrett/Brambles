layout(location = 0) in vec3 a_Position; // Vertex position
uniform mat4 u_Model;                    // Model transformation matrix
uniform mat4 u_View;                     // View transformation matrix
uniform mat4 u_Projection;               // Projection matrix

void main()
{
    // Apply the transformation and pass to the next stage
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
}
