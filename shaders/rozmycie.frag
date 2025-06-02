#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform vec2 blurDirection;

void main() {
    vec2 tex_offset = 1.0 / textureSize(screenTexture, 0);
    float weights[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
    
    vec3 result = texture(screenTexture, TexCoords).rgb * weights[0];
    for (int i = 1; i < 5; ++i) {
        result += texture(screenTexture, TexCoords + tex_offset * blurDirection * i).rgb * weights[i];
        result += texture(screenTexture, TexCoords - tex_offset * blurDirection * i).rgb * weights[i];
    }
    FragColor = vec4(result, 1.0);
}