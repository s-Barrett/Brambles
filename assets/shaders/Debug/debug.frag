#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform mat4 debugview;
uniform vec3 debuglineColor;
uniform float debuglinewidth;

out vec4 FragColor;

void main()
{
    vec3 viewPos = vec3(inverse(debugview)[3]);

    vec3 viewDir = normalize(viewPos - FragPos);

    float intensity = dot(viewDir, normalize(Normal));

    if (intensity < debuglinewidth)
    {
        FragColor = vec4(debuglineColor, 1.0);
    }
    else
    {
        discard;
    }
}