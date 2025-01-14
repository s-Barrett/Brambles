out vec4 FragColor;         // Final output color
uniform vec3 u_Color;       // Color passed from the debug renderer

void main()
{
    // Set the output color to the passed color
    FragColor = vec4(u_Color, 1.0);
}
