#version 330 core
varying vec2 v_TexCoord;
varying vec3 v_Normal;
varying vec3 v_FragPos;

uniform float u_Fade;
uniform vec3 u_ViewPos;
uniform sampler2D u_Texture;

void main() {
    vec4 tex = texture2D(u_Texture, v_TexCoord);
    vec3 lightPos = vec3(10, 10, 10);
    vec3 diffuseColor = vec3(1.0, 1.0, 1.0);
    vec3 ambient = vec3(0.5, 0.5, 0.5);
    vec3 specularColor = vec3(1.0, 1.0, 1.0);

    vec3 N = normalize(v_Normal);
    vec3 lightDir = normalize(lightPos - v_FragPos);
    float diff = max(dot(N, lightDir), 0.0);
    vec3 diffuse = diffuseColor * diff;

    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, N);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * specularColor;

    vec3 lighting = ambient + diffuse + specular;
    gl_FragColor = vec4(lighting, 1) * tex;
    gl_FragColor = vec4(0, 1, 0, 1);
}
