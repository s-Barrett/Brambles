#version 100
// Define precision for WebGL
precision mediump float;

uniform sampler2D u_Texture; // The texture sampler
varying vec2 v_TexCoord;     // Texture coordinates
varying vec3 v_Normal;       // Normal at the fragment
varying vec3 v_FragPos;      // Position of the fragment in world space

uniform vec3 u_ViewPos;      // Viewer's position (camera)
uniform vec3 u_Ambient;      // Ambient lighting color
uniform float u_SpecStrength; // Specular lighting strength

#define MAX_LIGHTS 10
uniform vec3 u_LightPositions[MAX_LIGHTS];  // Positions of light sources
uniform vec3 u_LightColors[MAX_LIGHTS];     // Colors of light sources
uniform float u_LightStrengths[MAX_LIGHTS]; // Strengths of light sources

void main()
{
    // Sample the texture at the fragment's texture coordinates
    vec4 tex = texture2D(u_Texture, v_TexCoord);

    // Normalize the normal vector
    vec3 N = normalize(v_Normal);

    // Calculate the view direction (from fragment to camera)
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);

    // Start with ambient lighting
    vec3 lighting = u_Ambient;

    // Loop through all light sources
    for (int i = 0; i < MAX_LIGHTS; ++i)
    {
        // Calculate the direction from the fragment to the light source
        vec3 lightDir = normalize(u_LightPositions[i] - v_FragPos);

        // Compute diffuse lighting (Lambertian reflection)
        float diff = max(dot(N, lightDir), 0.0);
        vec3 diffuse = u_LightColors[i] * diff * u_LightStrengths[i];

        // Compute specular reflection
        vec3 reflectDir = reflect(-lightDir, N);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16.0); // Specular exponent is a float value
        vec3 specular = spec * u_LightColors[i] * u_LightStrengths[i] * u_SpecStrength;

        // Add the diffuse and specular lighting to the total lighting
        lighting += diffuse + specular;
    }

    // Set the final color by multiplying the texture color with the lighting
    gl_FragColor = vec4(lighting, 1.0) * tex;
}
