#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 texCoord;

uniform sampler2D tex0;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec4 lightColor;
uniform int lightMode; // 0 = ambient, 1 = diffuse, 2 = specular, 3 = all

out vec4 FragColor;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor.rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor.rgb;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor.rgb;

    vec3 lighting;
    if (lightMode == 0)
        lighting = ambient;
    else if (lightMode == 1)
        lighting = diffuse;
    else if (lightMode == 2)
        lighting = specular;
    else
        lighting = ambient + diffuse + specular;

    vec3 textureColor = texture(tex0, texCoord).rgb;
    vec3 finalColor = lighting * textureColor;

    FragColor = vec4(finalColor, 1.0);
}
