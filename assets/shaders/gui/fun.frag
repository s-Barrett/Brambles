uniform sampler2D u_Texture;
varying vec2 v_TexCoord;
varying vec3 v_Normal;
varying vec3 v_FragPos;

uniform vec3 u_ViewPos;

void main()
{
    vec4 tex = texture2D(u_Texture, v_TexCoord);
    
    vec3 lightDir = normalize(vec3(0.5, 1.0, 0.5));
    float diff = max(dot(v_Normal, lightDir), 0.0);
    
    vec3 color = tex.rgb * (0.8 + diff * 0.2); // Apply light intensity
    float pulse = sin(v_FragPos.x * 0.3 + u_ViewPos.y * 0.5) * 0.1 + 0.5;
    color *= pulse;

    gl_FragColor = vec4(color, tex.a);
    gl_FragDepth = 0.02 + 0.01 * sin(v_FragPos.x * 0.4 + u_ViewPos.x);
}
