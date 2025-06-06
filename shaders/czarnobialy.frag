#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main() {
    vec3 color = texture(screenTexture, TexCoords).rgb;
    float luminance = dot(color, vec3(0.299, 0.587, 0.114));  // Wagi dla ludzkiego oka
    FragColor = vec4(vec3(luminance), 1.0);  // RGB ustawione na luminancję
}
