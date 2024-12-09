#version 330 core
varying vec2 v_TexCoord;

uniform sampler2D m_texture;

void main() {
    vec4 tex = texture2D(m_texture, v_TexCoord);
    gl_FragColor = tex;
}
