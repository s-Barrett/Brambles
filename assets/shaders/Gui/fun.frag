uniform sampler2D u_Texture;
varying vec2 v_TexCoord;
varying vec3 v_Normal;
varying vec3 v_FragPos;

uniform vec3 u_ViewPos;

void main()
{
    // Sample the texture
    vec4 tex = texture2D(u_Texture, v_TexCoord);
    
    // Basic lighting effect - Diffuse lighting using normal
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.5)); // Direction of light
    float diff = max(dot(v_Normal, lightDir), 0.0);
    
    // Fun color modification: add a light effect and combine it with the texture color
    vec3 color = tex.rgb * (0.8 + diff * 0.2); // Apply light intensity
    
    // Additional fun effect: Make the color pulse based on the fragment's position
    float pulse = sin(v_FragPos.x * 0.5 + u_ViewPos.y * 0.5) * 0.5 + 0.5; // Pulsing effect based on position
    color *= pulse;

    // Final color output with some transparency for a smoother effect
    gl_FragColor = vec4(color, tex.a);

    // Optional: add some fun depth manipulation or other effects
    gl_FragDepth = 0.02 + 0.01 * sin(v_FragPos.x * 0.1 + u_ViewPos.x);
}
