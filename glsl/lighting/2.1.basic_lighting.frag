#version 460 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 objectColor;

uniform vec3 lightColor1;
uniform vec3 lightPos1;

uniform vec3 lightColor2;
uniform vec3 lightPos2;

void main()
{
    vec3 norm = normalize(Normal);

    float ambientStrength = 0.05;

    vec3 ambient1 = ambientStrength * lightColor1;
    vec3 lightDir1 = normalize(lightPos1 - FragPos);
    float diff1 = max(dot(norm, lightDir1), 0.0);
    vec3 diffuse1 = diff1 * lightColor1;

    vec3 ambient2 = ambientStrength * lightColor2;
    vec3 lightDir2 = normalize(lightPos2 - FragPos);
    float diff2 = max(dot(norm, lightDir2), 0.0);
    vec3 diffuse2 = diff2 * lightColor2;

    vec3 result = (ambient1 + diffuse1 + ambient2 + diffuse2) * objectColor;
    FragColor = vec4(result, 1.0);
}